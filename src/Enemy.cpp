#include "bn_sprite_items_square.h"
#include "common.h"

#include "Enemy.h"

Enemy::Enemy(int starting_x, int starting_y, bn::size starting_size, bn::fixed starting_speed) : sprite(bn::sprite_items::square.create_sprite(starting_x, starting_y)) {
    size = starting_size;
    speed = starting_speed;
    bounding_box = create_bounding_box(sprite, size);
}

void Enemy::update(Player& player) {
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