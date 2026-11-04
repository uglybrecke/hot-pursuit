#include <bn_core.h>
#include <bn_random.h>

#include "Enemy.h"
#include "Player.h"
#include "ScoreDisplay.h"
#include "Fire.h"
#include "Cecil.h"

//random
static bn::random random;
static bn::fixed frame_count = 0;

int main() {
    bn::core::init();

    bn::vector<Enemy, constants::MAX_ENEMIES> enemies = bn::vector<Enemy, constants::MAX_ENEMIES>();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player
    Player player = Player();

    //create fire
    Fire fire(0,0);

    //create Cecil
    Cecil cecil(-64, 0);

    while(true) {
        //get the last safe player spot before moving
        bn::fixed p_x = player.sprite.x();
        bn::fixed p_y = player.sprite.y();        

        player.update();
        fire.update();
        cecil.update();

        //make player not walk into fire
        if(fire.bounding_box.intersects(player.bounding_box)) {
            player.sprite.set_x(p_x);
            player.sprite.set_y(p_y);
        }

        for (Enemy enemy : enemies) {
            enemy.update(player);
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
        if ((frame_count % 600) == 0) {
            if (enemies.size() < constants::MAX_ENEMIES) {
                Enemy new_enemy = Enemy(random.get_unbiased_int(constants::MIN_X, constants::MAX_X), random.get_unbiased_int(constants::MIN_Y, constants::MAX_Y), constants::enemy::SIZE, constants::enemy::BASE_SPEED);
                enemies.push_back(new_enemy);
            }
        }
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