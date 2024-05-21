#include "../include/Pacman.h"

Pacman::Pacman() : Entity() {
    setPredefinedAnimation();
}

void Pacman::setPredefinedAnimation() {
    animationFrames.clear();
    for (int i = 0; i < 5; ++i) {
        animationFrames.emplace_back(i * 32, 0, 32, 32);
    }
    entitySprite.setTextureRect(animationFrames[0]);
    entitySprite.setOrigin(animationFrames[0].width / 2.0f, animationFrames[0].height / 2.0f);
}
