#include <bn_sprite_item.h>

#include "common.h"

#include "Entity.h"

Entity::Entity(bn::sprite_item sprite_item, int starting_x, int starting_y, bn::size starting_size, bn::fixed starting_speed) : sprite(sprite_item.create_sprite(starting_x, starting_y)), size(starting_size), speed(starting_speed) {
    bounding_box = create_bounding_box(sprite, size);
}

Entity::Entity(bn::sprite_item sprite_item, int starting_x, int starting_y, bn::fixed starting_speed) : sprite(sprite_item.create_sprite(starting_x, starting_y)), speed(starting_speed) {
    size = sprite.dimensions();
    bounding_box = create_bounding_box(sprite, size);
}

void Entity::update() {
    bounding_box = create_bounding_box(sprite, size);
}