#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>

#include "Player.h"

class Enemy {
    public:
        Enemy(int starting_x, int starting_y, bn::size starting_size, bn::fixed starting_speed);

        void update(Player& player);

        bn::sprite_ptr sprite;
        bn::size size; // The width and height of the sprite
        bn::fixed speed; // The speed of the enemy
        bn::rect bounding_box; // The rectangle around the sprite for checking collision
};