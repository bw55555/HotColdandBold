#include "SoundEffect.h"
#include <irrklang/irrKlang.h>
#include "KeyInput.h"

using namespace irrklang;

SoundEffect::SFXPlayMap SoundEffect::lastPlayed;//{ {SFXType::Shot, false}, {SFXType::EnemyDeath, false}, {SFXType::PlayerDeath, false} };

std::shared_ptr<SoundEffect> SoundEffect::play(std::string filePath, bool shouldReturn) {
	ISound* sound = SoundEngine->play2D((PATH_START + filePath).c_str(), false, true);
	sound->setVolume(0.2f * sfxVolume);
	sound->setIsPaused(false);
	if (!shouldReturn) { return nullptr; }
	return std::make_shared<SoundEffect>(sound);
}

std::shared_ptr<SoundEffect> SoundEffect::play(SFXType t, bool shouldReturn) {
	if (lastPlayed[t] + 6 <= KeyInput::currFrame) {
		lastPlayed[t] = KeyInput::currFrame;
		switch (t) {
		case SFXType::Shot:
			return play("resources/audio/shot.wav", shouldReturn);
		}
	}
	return nullptr;
}

SoundEffect::~SoundEffect() {
	sound->drop();
}