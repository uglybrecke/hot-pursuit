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
        void spawn(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
                        bn::fixed frame_count);

    private:
        bn::random random;
};