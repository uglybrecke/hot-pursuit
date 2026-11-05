#include <bn_keypad.h>

#include "bn_sprite_items_dot.h"
#include "constants.h"
#include "common.h"

#include "Player.h"

Player::Player() : Entity(bn::sprite_items::dot, constants::player::INITIAL_X, constants::player::INITIAL_Y, constants::player::SIZE, constants::player::BASE_SPEED) {
    
}

void Player::update() {
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

    //make sure player doesn't go off the map
    if(sprite.x() >= constants::MAX_X) {
        sprite.set_x(constants::MAX_X);
    }
    if(sprite.x() <= constants::MIN_X) {
        sprite.set_x(constants::MIN_X);
    }
    if(sprite.y() >= constants::MAX_Y) {
        sprite.set_y(constants::MAX_Y);
    }
    if(sprite.y() <= constants::MIN_Y) {
        sprite.set_y(constants::MIN_Y);
    }

    Entity::update();
}