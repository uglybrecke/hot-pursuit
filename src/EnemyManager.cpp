#include "EnemyManager.h"
#include "Cecil.h"

/**
 * A class to manage all of the skulls 
 */

//the spawning function
void EnemyManager::spawn(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
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

//return true or false to main to reset the game
bool EnemyManager::update(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
                          Player& player)
{
    for(Enemy& enemy : enemies) {
        enemy.update(player);

        if(enemy.bounding_box.intersects(player.bounding_box)) {
            return true;
        }
    }
    return false;
}

//return true of false to indicate if a skull hit cecil
bool EnemyManager::hit_cecil(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies,
                             const Cecil& cecil)
{
    for(int i = 0; i < enemies.size(); i++) {
        if(enemies[i].bounding_box.intersects(cecil.bounding_box)) {
            enemies.erase(enemies.begin() + i);
            return true;
        }
    }
    return false;
}