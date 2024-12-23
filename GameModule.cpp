#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Game.h"

namespace py = pybind11;

PYBIND11_MODULE(game_module, m) {
    py::enum_<GameMode>(m, "GameMode")
        .value("CLASSIC", GameMode::CLASSIC)
        .value("WITH_HINTS", GameMode::WITH_HINTS)
        .value("ADAPTIVE", GameMode::ADAPTIVE);

    py::class_<Game>(m, "Game")
        .def(py::init<const std::string&, int, GameMode>())
        .def("initialize_game", &Game::initializeGame)
        .def("increase_difficulty", &Game::increaseDifficulty)
        .def("is_game_won", &Game::isGameWon)
        .def("is_game_over", &Game::isGameOver)
        .def("process_input", &Game::processInput)
        .def("display_current_state", &Game::displayCurrentState)
        .def("get_target_word", &Game::getTargetWord)
        .def("save_history", &Game::saveHistory);  // Використовуємо правильний метод
}
