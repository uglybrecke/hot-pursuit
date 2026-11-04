#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>

#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"

#include "bn_random.h"

#include "common.h"

#include "ScoreDisplay.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {16, 16};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Player / enemy constants
static constexpr int PLAYER_INITIAL_X = 44;
static constexpr int PLAYER_INITIAL_Y = 22;
static constexpr int ENEMY_INITIAL_X = -50;
static constexpr int ENEMY_INITIAL_Y = 40;
static constexpr bn::fixed BASE_PLAYER_SPEED = 1.5;
static constexpr bn::fixed BASE_ENEMY_SPEED = 0.7;

static constexpr int MAX_ENEMIES = 15;

//random
static bn::random random;
static bn::fixed frame_count = 0;

class Player {
    public:
    //this order matter apparently!
        bn::sprite_ptr sprite;
        bn::size size; // The width and height of the sprite
        bn::fixed speed; // The speed of the player
        bn::rect bounding_box; // The rectangle around the sprite for checking collision

        //Constructor with initialization logic
        Player() : sprite(bn::sprite_items::dot.create_sprite(PLAYER_INITIAL_X, PLAYER_INITIAL_Y)), size(PLAYER_SIZE), speed(BASE_PLAYER_SPEED) {
            bounding_box = create_bounding_box(sprite, size);
        }

        /**
         * Update the position and bounding box of the player based on d-pad movement.
         */

        void update() {
            if(bn::keypad::right_held()) {
                sprite.set_x(sprite.x() + speed);
            }
            if(bn::keypad::left_held()) {
                sprite.set_x(sprite.x() - speed);
            }
            if(bn::keypad::up_held()) {
                sprite.set_y(sprite.y() - speed);
            }
            if(bn::keypad::down_held()) {
                sprite.set_y(sprite.y() + speed);
            }

            bounding_box = create_bounding_box(sprite, size);

            //make sure player doesn't go off the map
            if(sprite.x() >= MAX_X) {
                sprite.set_x(MAX_X);
            }
            if(sprite.x() <= MIN_X) {
                sprite.set_x(MIN_X);
            }
            if(sprite.y() >= MAX_Y) {
                sprite.set_y(MAX_Y);
            }
            if(sprite.y() <= MIN_Y) {
                sprite.set_y(MIN_Y);
            }
        }
};

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
                player.sprite.set_x(PLAYER_INITIAL_X);
                player.sprite.set_y(PLAYER_INITIAL_Y);
                // Remove all enemies
                enemies.clear();
                frame_count = 0;
                break;
            }
        }

        // Spawn an enemy every 10 seconds if there's room
        if ((frame_count % 600) == 0) {
            if (enemies.size() < MAX_ENEMIES) {
                Enemy new_enemy = Enemy(random.get_unbiased_int(MIN_X, MAX_X), random.get_unbiased_int(MIN_Y, MAX_Y), ENEMY_SIZE, BASE_ENEMY_SPEED);
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