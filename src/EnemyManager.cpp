#include "EnemyManager.h"

/**
 * A class to manage all of the skulls 
 */
void EnemyManager::spawn(bn::vector<Enemy,
                         constants::MAX_ENEMIES>& enemies,
                         bn::fixed frame_count)
{
        // Spawn an enemy every 10 seconds if there's room
        if ((frame_count % 600) == 0) {
            if (enemies.size() < constants::MAX_ENEMIES) {
                Enemy new_enemy = Enemy(
                    random.get_unbiased_int(
                        constants::MIN_X,
                        constants::MAX_X),
                    random.get_unbiased_int(
                        constants::MIN_Y, 
                        constants::MAX_Y), 
                    constants::enemy::SIZE, 
                    constants::enemy::BASE_SPEED);

                enemies.push_back(new_enemy);
            }
        }
}