#include "Game.h"
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

Game::Game(const std::string& filename, int maxAttempts, GameMode mode)
    : attemptsLeft(maxAttempts), gameMode(mode), difficultyLevel(0) {
    ifstream file(filename);
    string word;
    if (file.is_open()) {
        while (file >> word) {
            wordsList.push_back(word);
        }
        file.close();
    } else {
        throw runtime_error("Failed to open words file.");
    }
}

vector<string> Game::getWordsByDifficulty() const {
    vector<string> filteredWords;

    for (const auto& word : wordsList) {
        if (difficultyLevel == 0 && word.size() <= 4) {
            filteredWords.push_back(word);
        } else if (difficultyLevel == 1 && word.size() > 4 && word.size() <= 6) {
            filteredWords.push_back(word);
        } else if (difficultyLevel >= 2 && word.size() > 6) {
            filteredWords.push_back(word);
        }
    }

    return filteredWords.empty() ? wordsList : filteredWords;
}

void Game::initializeGame() {
    if (wordsList.empty()) {
        throw runtime_error("Words list is empty!");
    }

    vector<string> possibleWords = wordsList;

    if (gameMode == GameMode::ADAPTIVE) {
        possibleWords = getWordsByDifficulty();
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, possibleWords.size() - 1);
    targetWord = possibleWords[dist(gen)];

    currentState = string(targetWord.size(), '*');
    guessedLetters.clear();

    cout << "Game started! Mode: ";
    if (gameMode == GameMode::CLASSIC) cout << "Classic Mode\n";
    if (gameMode == GameMode::WITH_HINTS) cout << "Mode with Hints (type 'hint' for help)\n";
    if (gameMode == GameMode::ADAPTIVE) cout << "Adaptive Mode\n";
}

void Game::increaseDifficulty() {
    if (gameMode == GameMode::ADAPTIVE) {
        ++difficultyLevel;
        attemptsLeft = max(2, attemptsLeft - 1);
        cout << "Difficulty increased! Level: " << difficultyLevel
             << ". Remaining attempts: " << attemptsLeft << "\n";
    }
}

string Game::provideHint() const {
    return "Hint: The first letter of the word is '" + string(1, targetWord[0]) + "'.\n";
}

bool Game::processInput(const string& input) {
    if (input == "hint" && gameMode == GameMode::WITH_HINTS) {
        cout << provideHint();
        return false;
    }

    if (input.size() > 1) {
        if (input == targetWord) {
            currentState = targetWord;
            return true;
        } else {
            --attemptsLeft;
            cout << "Wrong word!\n";
            return false;
        }
    }

    char letter = input[0];

    if (guessedLetters.count(letter)) {
        cout << "You have already entered this letter!\n";
        return false;
    }

    guessedLetters.insert(letter);

    bool isCorrect = false;
    for (size_t i = 0; i < targetWord.size(); ++i) {
        if (targetWord[i] == letter) {
            currentState[i] = letter;
            isCorrect = true;
        }
    }

    if (!isCorrect) {
        --attemptsLeft;
        cout << "No such letter!\n";
    }

    return isCorrect;
}

bool Game::isGameWon() const {
    return currentState == targetWord;
}

bool Game::isGameOver() const {
    return attemptsLeft <= 0;
}

string Game::getTargetWord() const {
    return targetWord;
}

void Game::displayCurrentState() const {
    cout << "Current state: " << currentState << "\n";
    cout << "Attempts left: " << attemptsLeft << "\n";
}

// Функція для збереження історії гри, включаючи дату, час та режим гри
void Game::saveHistory(const string& result) {
    // Отримуємо поточний час
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());

    // Перетворюємо час у рядок
    char buffer[80];
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);  // Формат: 2024-12-23 14:30:00

    string timeStr(buffer);

    // Визначаємо режим гри для збереження
    string modeStr;
    switch (gameMode) {
        case GameMode::CLASSIC: modeStr = "Classic"; break;
        case GameMode::WITH_HINTS: modeStr = "With Hints"; break;
        case GameMode::ADAPTIVE: modeStr = "Adaptive"; break;
        default: modeStr = "Unknown"; break;
    }

    // Відкриваємо файл для запису
    ofstream historyFile("history.txt", ios::app);
    if (historyFile.is_open()) {
        // Записуємо дату, час, режим гри і результат гри
        historyFile << "[" << timeStr << "] " << "Mode: " << modeStr << " - " << result << endl;
        historyFile.close();
    } else {
        cerr << "Error opening history file!" << endl;
    }
}

