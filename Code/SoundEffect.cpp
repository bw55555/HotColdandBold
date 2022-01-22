#include "SoundEffect.h"
#include <irrklang/irrKlang.h>
#include "KeyInput.h"

using namespace irrklang;

SoundEffect::SFXPlayMap SoundEffect::lastPlayed;//{ {SFXType::Shot, false}, {SFXType::EnemyDeath, false}, {SFXType::PlayerDeath, false} };

std::shared_ptr<SoundEffect> SoundEffect::play(std::string filePath, bool shouldReturn, float volumeMult) {
	ISound* sound = SoundEngine->play2D((PATH_START + filePath).c_str(), false, true);
	sound->setVolume(volumeMult * sfxVolume);
	sound->setIsPaused(false);
	if (!shouldReturn) { return nullptr; }
	return std::make_shared<SoundEffect>(sound);
}

std::shared_ptr<SoundEffect> SoundEffect::play(SFXType t, bool shouldReturn, float volumeMult) {
	switch (t) {
	case SFXType::Shot:
		if (lastPlayed[t] + 6 <= KeyInput::currFrame) {
			lastPlayed[t] = KeyInput::currFrame;
			return play("resources/audio/shot.wav", shouldReturn, volumeMult);
		}
		break;
	case SFXType::EnemyDeath:
		if (lastPlayed[t] < KeyInput::currFrame) {
			lastPlayed[t] = KeyInput::currFrame;
			return play("resources/audio/enemydead.wav", shouldReturn, volumeMult);
		}
		break;
	}
	
	
	return nullptr;
}

SoundEffect::~SoundEffect() {
	sound->drop();
}