#include "Audio.h"
#include <irrklang/irrKlang.h>

using irrklang::ISound, irrklang::ISoundEngine;

float Audio::bgVolume = 1.0f;
float Audio::sfxVolume = 1.0f;
irrklang::ISoundEngine* Audio::SoundEngine = irrklang::createIrrKlangDevice();

std::shared_ptr<Audio> Audio::playSound(std::string filePath) {
	SoundEngine->play2D(filePath.c_str(), true);
	return nullptr;
}

void Audio::dropEngine() {
	SoundEngine->drop();
}