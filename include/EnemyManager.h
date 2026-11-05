#pragma once

#include <bn_vector.h>
#include <bn_random.h>
#include "Enemy.h"
#include "constants.h"
#include "Cecil.h"

/**
 * A class to manage all of the skulls 
 */
class EnemyManager {
    public:
        //function to spawn enemies
        void spawn(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies, 
                   Player& player);
        //function to update if the player was hit
        bool update(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
                    Player& player);
        //function to see if an enemy is hit by cecil
        bool hit_cecil(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
                        const Cecil& cecil);

    private:
        bn::random random;
};