#include "EnemyManager.h"
#include "Cecil.h"

/**
 * A class to manage all of the skulls 
 */

//the spawning function
void EnemyManager::spawn(bn::vector<Enemy, constants::MAX_ENEMIES>& enemies, Player& player)
{
    if (enemies.size() < constants::MAX_ENEMIES) {
        int player_x = player.sprite.x().round_integer();
        int player_y = player.sprite.y().round_integer();
        int new_x = 0;
        int new_y = 0;
        // Find a suitable spawn location
        for (int i = 0; i < 10; i++) {
            new_x = random.get_unbiased_int(constants::MIN_X, constants::MAX_X);
            new_y = random.get_unbiased_int(constants::MIN_Y, constants::MAX_Y);
            int dx = bn::abs(player_x - new_x);
            int dy = bn::abs(player_y - new_y);

            if (dx > constants::enemy::SAFE_SPAWN_DISTANCE || dy > constants::enemy::SAFE_SPAWN_DISTANCE) {
                break;
            } else {
                if (i == 9) {
                    return; // No safe spawn location found
                }
            }
        }

        // Once one is found, spawn an enemy
        Enemy new_enemy = Enemy(
            new_x, new_y, 
            constants::enemy::SIZE, 
            constants::enemy::BASE_SPEED);

        enemies.push_back(new_enemy);
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