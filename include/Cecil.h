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
        bool active = true;

        Cecil(int x, int y);

        void update();
        
        //caught a skull
        void fetch(bool hit);

        bool blocks_player();

    private:
        bn::sprite_ptr sprite;
        int idle_timer = 0;
        bool second_pose = false;
        bool running = false;
        int run_direction = 1;
        int respawn = 0;
        int spawn_x;
        int spawn_y;
};