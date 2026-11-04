#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>

class Player {
    public:
        Player();

        /**
         * Update the position and bounding box of the player based on d-pad movement.
         */
        void update();

        bn::sprite_ptr sprite; // Player sprite
        bn::size size; // The width and height of the sprite
        bn::fixed speed; // The speed of the player
        bn::rect bounding_box; // The rectangle around the sprite for checking collision
};