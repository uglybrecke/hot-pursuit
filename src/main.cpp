#include <bn_core.h>
#include <bn_random.h>

#include "Enemy.h"
#include "Player.h"
#include "ScoreDisplay.h"
#include "Fire.h"
#include "Cecil.h"
#include "common.h"
#include "EnemyManager.h"
#include "Game.h"
#include "FireManager.h"

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

    //create Fires
    FireManager fireManager;
    fireManager.spawn(-32, 0);
    fireManager.spawn(0, 0);
    fireManager.spawn(32, 0);
    fireManager.spawn(64, 0);

    //create Cecil
    Cecil cecil(-64, 0);

    //create an enemyManager
    EnemyManager enemyManager;

    while(true) {

        //get the last safe player spot before moving
        bn::fixed p_x = player.sprite.x();
        bn::fixed p_y = player.sprite.y();        

        player.update();
        cecil.update();
        fireManager.update(player, cecil, p_x, p_y);

        //make player not walk into cecil
        if(cecil.blocks_player()) {
            block_player(player, cecil.bounding_box, p_x, p_y);
        }

        //check if the enemy hits cecil
        if(cecil.blocks_player()) {
            cecil.fetch(enemyManager.hit_cecil(enemies, cecil));
        }

        //reset game
        if(enemyManager.update(enemies, player)) {
            reset_game(player, scoreDisplay);
            enemies.clear();
            frame_count = 0;
        }

        // Spawn an enemy every 10 seconds if there's room
        if ((frame_count % 600) == 0) {
            enemyManager.spawn(enemies, player);
        }

        // Reset the frame counter after 4 minutes
        if (frame_count == 14400) {
            frame_count = 0;
        }

        //if framecount is divisble by  1200 add a fire make a bunch of fire randomly
        if ((frame_count % 1200) == 0 && frame_count >= 1200) {
            fireManager.spawn(random.get_unbiased_int(constants::MIN_X + 16, constants::MAX_X - 16), random.get_unbiased_int(constants::MIN_Y + 16, constants::MAX_Y - 16));
            fireManager.spawn(random.get_unbiased_int(constants::MIN_X + 16, constants::MAX_X - 16), random.get_unbiased_int(constants::MIN_Y + 16, constants::MAX_Y - 16));
            fireManager.spawn(random.get_unbiased_int(constants::MIN_X + 16, constants::MAX_X - 16), random.get_unbiased_int(constants::MIN_Y + 16, constants::MAX_Y - 16));
            fireManager.spawn(random.get_unbiased_int(constants::MIN_X + 16, constants::MAX_X - 16), random.get_unbiased_int(constants::MIN_Y + 16, constants::MAX_Y - 16));
            fireManager.spawn(random.get_unbiased_int(constants::MIN_X + 16, constants::MAX_X - 16), random.get_unbiased_int(constants::MIN_Y + 16, constants::MAX_Y - 16));
        }

        // Update the scores and display them
        scoreDisplay.update();

        frame_count += 1;

        bn::core::update();
    }
}