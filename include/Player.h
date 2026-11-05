#pragma once

#include "Entity.h"

class Player : public Entity {
    public:
        Player();

        /**
         * Update the position and bounding box of the player based on d-pad movement.
         */
        void update();
};