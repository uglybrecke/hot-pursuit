#pragma once

#include "Entity.h"
#include <bn_random.h>

/**
 * Generate the Cecil Dog block that will block the players path
 * Cecil will destroy the skull if it intersects with him
 * good dog! :)
 */

class Cecil : public Entity {
    public:
        Cecil(int x, int y);

        void update();
        
        //caught a skull
        void fetch(bool hit);

        bool blocks_player();

        bool active = true;

        //if cecil is running return true
        bool is_running() const {
            return active && running;
        }

    private:
        int pose_timer = 0;
        bool second_pose = false;
        bool running = false;
        int run_direction = 1;
        int respawn = 0;
        bn::random random;
};