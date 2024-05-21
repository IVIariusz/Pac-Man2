#ifndef PACMAN_H
#define PACMAN_H

#include "Entity.h"

class Pacman : public Entity {
public:
    Pacman();
    void setPredefinedAnimation() override;
};

#endif // PACMAN_H
