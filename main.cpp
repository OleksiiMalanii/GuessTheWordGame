#include "Game.h"
#include <iostream>

using namespace std;

// Уникаємо використання GameMode::HISTORY, створюючи окрему функцію для виведення історії
void showHistory() {
    ifstream historyFile("history.txt");
    string line;
    if (historyFile.is_open()) {
        while (getline(historyFile, line)) {
            cout << line << endl << endl;
        }
        historyFile.close();
    } else {
        cout << "No history available.\n";
    }
}

GameMode chooseGameMode() {
    int choice;
    cout << "0. Exit\n";
    cout << "1. Classic\n";
    cout << "2. With Hints\n";
    cout << "3. Adaptive\n";
    cout << "4. Show Game History\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 0: exit(0);
        case 1: return GameMode::CLASSIC;
        case 2: return GameMode::WITH_HINTS;
        case 3: return GameMode::ADAPTIVE;
        case 4: // Для показу історії
            showHistory();
        return chooseGameMode();
    }
}

bool askToContinue() {
    char choice;
    cout << "Do you want to continue? (y/n): ";
    cin >> choice;
    return choice == 'y' || choice == 'Y';
}

int main() {
    try {
        GameMode mode = chooseGameMode();

        if (mode == GameMode::CLASSIC) {  // Якщо користувач вибрав класичний режим
            Game game("words.txt", 6, mode);

            while (true) {
                game.initializeGame();

                while (!game.isGameOver() && !game.isGameWon()) {
                    game.displayCurrentState();
                    cout << "Enter a letter or word: ";
                    string input;
                    cin >> input;

                    game.processInput(input);

                    if (game.isGameWon()) {
                        cout << "You won! The word is: " << game.getTargetWord() << "\n";
                        game.saveHistory("Won! Word: " + game.getTargetWord());
                        if (mode == GameMode::ADAPTIVE) game.increaseDifficulty();
                        break;
                    }
                }

                if (game.isGameOver()) {
                    cout << "Game over. The word was: " << game.getTargetWord() << "\n";
                    game.saveHistory("Game over. Word: " + game.getTargetWord());
                }

                if (!askToContinue()) {
                    break;
                }
            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
