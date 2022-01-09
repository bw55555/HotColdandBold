#pragma once
enum class Difficulty {Easy, Normal, Hard};
enum class GameMode {All, Prac1, Prac2, Prac3};

struct Settings {
	Difficulty difficulty;
	GameMode mode;
	static Difficulty getGameDifficulty();
};

template<typename T> 
inline T dchoice(T easyval, T normalval, T hardval) {
	switch (Settings::getGameDifficulty()) {
	case Difficulty::Easy:
		return easyval;
	case Difficulty::Normal:
		return normalval;
	case Difficulty::Hard:
		return hardval;
	default:
		return easyval;
	}
}
