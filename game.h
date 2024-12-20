#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <random>
#include <stdexcept>

using namespace std;

enum class GameMode { CLASSIC, WITH_HINTS, ADAPTIVE };

class Game {
private:
    vector<string> wordsList;
    string targetWord;
    string currentState;
    set<char> guessedLetters;
    int attemptsLeft;
    int difficultyLevel;
    GameMode gameMode;

    string provideHint() const;
    vector<string> getWordsByDifficulty() const;

public:
    Game(const string& filename, int maxAttempts, GameMode mode);
    void initializeGame();
    void increaseDifficulty();
    bool isGameWon() const;
    bool isGameOver() const;
    bool processInput(const string& input);
    void displayCurrentState() const;
    string getTargetWord() const;
};

#endif // GAME_H