#pragma once

#include "Entity.h"

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

    private:
        int idle_timer = 0;
        bool second_pose = false;
        bool running = false;
};