#include "Game.h"
#include <iostream>

using namespace std;

GameMode chooseGameMode() {
    int choice;
    cout << "Choose game mode:\n";
    cout << "1. Classic\n";
    cout << "2. With Hints\n";
    cout << "3. Adaptive\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: return GameMode::CLASSIC;
        case 2: return GameMode::WITH_HINTS;
        case 3: return GameMode::ADAPTIVE;
        default: return GameMode::CLASSIC;
    }
}

int main() {
    try {
        GameMode mode = chooseGameMode();
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
                    if (mode == GameMode::ADAPTIVE) game.increaseDifficulty();
                    break;
                }
            }

            if (game.isGameOver()) {
                cout << "Game over. The word was: " << game.getTargetWord() << "\n";
                break;
            }
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}