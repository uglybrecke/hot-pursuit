#pragma once

#include <bn_sprite_ptr.h>
#include "common.h"

/**
 * Generate the Cecil Dog block that will block the players path
 * Cecil will destroy the skull if it intersects with him
 * good dog! :)
 */

class Cecil {
    public:
        bn::rect bounding_box;

        Cecil(int x, int y);

        void update();
        bool detect_enemy();

    private:
        bn::sprite_ptr sprite;
        int idle_timer = 0;
        bool second_pose = false;
};