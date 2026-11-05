#pragma once

#include <bn_sprite_ptr.h>
#include <bn_vector.h>

/**
 * Generate the Fire walls that will block the players path
 * Skulls (squares can move throuh these without issue)
 */

 class Fire {
    public:
        bn::rect bounding_box;      

        /**
         * Fire constructor
        */
        Fire(int x, int y);

        /**
         * makes the fire flip back and forth
         */
        void update();

        bool fireBox();

        void collision();

    private:
        bn::sprite_ptr sprite;

        //each fire has a flicker timer in it
        int flicker = 0;
 };