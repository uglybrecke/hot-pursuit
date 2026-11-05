#pragma once

#include <bn_rect.h>
#include <bn_sprite_ptr.h>

/**
 * Generate the Fire walls that will block the players path
 * Skulls (squares can move throuh these without issue)
 */

 class Fire : public Entity {
    public:   

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

        //each fire has a flicker timer in it
        int flicker = 0;
 };