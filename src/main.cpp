#include <bn_core.h>
#include <bn_random.h>

#include "Enemy.h"
#include "Player.h"
#include "ScoreDisplay.h"
#include "Fire.h"
#include "Cecil.h"
#include "common.h"
#include "EnemyManager.h"

//random
static bn::random random;
static bn::fixed frame_count = 0;

int main() {
    bn::core::init();

    bn::vector<Enemy, constants::MAX_ENEMIES> enemies = bn::vector<Enemy, constants::MAX_ENEMIES>();

    // Create a new Score Display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a Player
    Player player = Player();

    //create Fire
    Fire fire(0,0);

    //create Cecil
    Cecil cecil(-64, 0);

    //create an enemyManager
    EnemyManager enemyManager;

    while(true) {

        //get the last safe player spot before moving
        bn::fixed p_x = player.sprite.x();
        bn::fixed p_y = player.sprite.y();        

        player.update();
        fire.update();
        cecil.update();

        //make player not walk into fire
        block_player(player, fire.bounding_box, p_x, p_y);

        //make player not walk into cecil
        block_player(player, cecil.bounding_box, p_x, p_y);

        for (Enemy enemy : enemies) {
            enemy.update(player);
            //detect if an enemy bumps into Cecil
            if(enemy.bounding_box.intersects(cecil.bounding_box)) {
                //remove skull
                //switch cecil to run
                //break out of the enemy loop
            }

            // Reset the current score and player position if the player collides with enemy
            if(enemy.bounding_box.intersects(player.bounding_box)) {
                scoreDisplay.resetScore();
                player.sprite.set_x(constants::player::INITIAL_X);
                player.sprite.set_y(constants::player::INITIAL_Y);
                // Remove all enemies
                enemies.clear();
                frame_count = 0;
                break;
            }
        }

        // Spawn an enemy every 10 seconds if there's room
        enemyManager.spawn(enemies, frame_count);

        // Reset the frame counter after 4 minutes
        if (frame_count == 14400) {
            frame_count = 0;
        }

        // Update the scores and display them
        scoreDisplay.update();

        frame_count += 1;

        bn::core::update();
    }
}