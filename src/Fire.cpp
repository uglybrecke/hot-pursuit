#include "Fire.h"
#include "bn_sprite_items_fire.h"
#include "common.h"

//construcor
Fire::Fire(int x, int y) :
    sprite(bn::sprite_items::fire.create_sprite(x, y))
{
    bounding_box = create_bounding_box(sprite, sprite.dimensions());
}

//flip the sprite 
void Fire::update() {
    flicker++;

    if(flicker >= 30) {
        sprite.set_horizontal_flip(!sprite.horizontal_flip());
        flicker = 0;
    }
    
}