#pragma once

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity{
    public:
        Enemy(int starting_x, int starting_y, bn::size starting_size, bn::fixed starting_speed);

        void update(Player& player);
};