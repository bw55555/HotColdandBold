#include "Settings.h"
#include "GameWindow.h"

Difficulty Settings::getGameDifficulty() {
	return GameWindow::Instance->settings.difficulty;
}