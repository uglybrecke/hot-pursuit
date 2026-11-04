#pragma once

#include <bn_vector.h>
#include <bn_random.h>
#include "Enemy.h"
#include "constants.h"

/**
 * A class to manage all of the skulls 
 */
class EnemyManager {
    public:
        //function to spawn enemies
        void spawn(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
                    bn::fixed frame_count);
        //function to update if the player was hit
        bool update(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
                    Player& player);

    private:
        bn::random random;
};