#include "Audio.h"
#include <irrklang/irrKlang.h>

using irrklang::ISound, irrklang::ISoundEngine;

float Audio::bgVolume = 0.5f;
float Audio::sfxVolume = 0.5f;

std::shared_ptr<Audio> Audio::playSound(std::string filePath, bool loop, bool shouldReturn, float volumeMult) {
	ISound* sound = SoundEngine->play2D((PATH_START + filePath).c_str(), loop, true);
	sound->setVolume(static_cast<double>(volumeMult * bgVolume));
	sound->setIsPaused(false);
	if (!shouldReturn) { return nullptr; }
	return std::make_shared<Audio>(sound);
}

void Audio::setVolume(float volume) {
	sound->setIsPaused(true);
	sound->setVolume(volume);
	sound->setIsPaused(false);
}

void Audio::dropEngine() {
	SoundEngine->drop();
}

Audio::~Audio() {
	sound->drop();
}