#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>

#include "common_fixed_8x16_font.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_square.h"

#include "bn_random.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

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

// Number of characters required to show two of the longest numer possible in an int (-2147483647)
static constexpr int MAX_SCORE_CHARS = 22;
static constexpr int MAX_ENEMIES = 15;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

//random
static bn::random random;
static bn::fixed frame_count = 0;

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size) {
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
};

/**
 * Displays a score and high score.
 * 
 * Score starts a 0 and is increased each time update is called, and reset to 0 when resetScore is
 * called. High score tracks the highest score ever reached.
*/
class ScoreDisplay {
    public:
        ScoreDisplay() :
            score(0), // Start score at 0
            high_score(0), // Start high score at 0
            score_sprites(bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS>()), // Start with empty vector for score sprites
            text_generator(bn::sprite_text_generator(common::fixed_8x16_sprite_font)) // Use a new text generator
        {}

        /**
         * Increases score by 1 and updates high score if needed. Displays score and high score.
         */
        void update() {
            // increase score and update high score if this is the new highest
            score++;
            if(score > high_score) {
                high_score = score;
            }

            // Stop displaying previous scores
            score_sprites.clear();

            // Display new scores
            show_number(SCORE_X, SCORE_Y, score);
            show_number(HIGH_SCORE_X, HIGH_SCORE_Y, high_score);
        }

        /**
         * Displays a number at the given position
         */
        void show_number(int x, int y, int number) {
            // Convert number to a string and then display it
            bn::string<MAX_SCORE_CHARS> number_string = bn::to_string<MAX_SCORE_CHARS>(number);
            text_generator.generate(x, y, number_string, score_sprites);
        }

        /**
         * Sets score back to 0. Does NOT reset high score.
         */
        void resetScore() {
            score = 0;
        }

        int score; // current score
        int high_score; // best core
        bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites; // Sprites to display scores
        bn::sprite_text_generator text_generator; // Text generator for scores
};

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

    // Create a player and initial enemy
    Player player = Player();
    Enemy initial_enemy = Enemy(random.get_unbiased_int(MIN_X, MAX_X), random.get_unbiased_int(MIN_Y, MAX_Y), ENEMY_SIZE, BASE_ENEMY_SPEED);
    enemies.push_back(initial_enemy);

    while(true) {
        player.update();

        for (Enemy enemy : enemies) {
            enemy.update(player);
            // Reset the current score and player position if the player collides with enemy
            if(enemy.bounding_box.intersects(player.bounding_box)) {
                scoreDisplay.resetScore();
                player.sprite.set_x(PLAYER_INITIAL_X);
                player.sprite.set_y(PLAYER_INITIAL_Y);
                enemy.sprite.set_x(random.get_unbiased_int(MIN_X,MAX_X));
                enemy.sprite.set_y(random.get_unbiased_int(MIN_Y,MAX_Y));
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