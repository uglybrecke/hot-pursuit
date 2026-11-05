#pragma once

#include <bn_sprite_ptr.h>
#include <bn_rect.h>

// Base class for entities (sprite_ptr w/ speed, bounding box, etc)
class Entity {
    public:
        Entity(bn::sprite_item sprite_item, int starting_x, int starting_y, bn::fixed starting_speed);
        Entity(bn::sprite_item sprite_item, int starting_x, int starting_y, bn::size starting_size, bn::fixed starting_speed);

        void update();

        bn::sprite_ptr sprite;
        bn::size size; // Sprite dimensions
        bn::fixed speed; // Movement speed
        bn::rect bounding_box; // Rectangle drawn around sprite for collision
};