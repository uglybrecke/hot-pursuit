#include <bn_core.h>

#include "bn_sprite_items_square.h"

#include "bn_random.h"

#include "common.h"

#include "Player.h"
#include "ScoreDisplay.h"

static constexpr bn::size ENEMY_SIZE = {16, 16};

// Player / enemy constants

static constexpr int ENEMY_INITIAL_X = -50;
static constexpr int ENEMY_INITIAL_Y = 40;
static constexpr bn::fixed BASE_ENEMY_SPEED = 0.7;

static constexpr int MAX_ENEMIES = 15;

//random
static bn::random random;
static bn::fixed frame_count = 0;

class Enemy {
    public:
        //this order matter apparently!
        bn::sprite_ptr sprite;
        bn::size size; // The width and height of the sprite
        bn::fixed speed; // The speed of the enemy
        bn::rect bounding_box; // The rectangle around the sprite for checking collision

        //Constructor with initialization logic
        Enemy(int starting_x, int starting_y, bn::size starting_size, bn::fixed starting_speed) : sprite(bn::sprite_items::square.create_sprite(starting_x, starting_y))  {
            size = starting_size;
            speed = starting_speed;
            bounding_box = create_bounding_box(sprite, size);
        }

        void update(Player& player) {
            bn::fixed player_x = player.sprite.x();
            bn::fixed player_y = player.sprite.y();
            bn::fixed current_x = sprite.x();
            bn::fixed current_y = sprite.y();
            if (player_x < current_x) {
                sprite.set_x(current_x - speed);
            }
            if (player_x > current_x) {
                sprite.set_x(current_x + speed);
            }
            if (player_y < current_y) {
                sprite.set_y(current_y - speed);
            }
            if (player_y > current_y) {
                sprite.set_y(current_y + speed);
            }
            bounding_box = create_bounding_box(sprite, size);
        }
};

int main() {
    bn::core::init();

    bn::vector<Enemy, MAX_ENEMIES> enemies = bn::vector<Enemy, MAX_ENEMIES>();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player
    Player player = Player();

    while(true) {
        player.update();

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
            if (enemies.size() < MAX_ENEMIES) {
                Enemy new_enemy = Enemy(random.get_unbiased_int(constants::MIN_X, constants::MAX_X), random.get_unbiased_int(constants::MIN_Y, constants::MAX_Y), ENEMY_SIZE, BASE_ENEMY_SPEED);
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