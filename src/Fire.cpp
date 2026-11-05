#include "Fire.h"
#include "bn_sprite_items_fire.h"
#include "common.h"

//constructor
Fire::Fire(int x, int y) : Entity(bn::sprite_items::fire, x, y, 0)
{
    
}

//flip the sprite 
void Fire::update() {
    flicker++;

    if(flicker >= 30) {
        sprite.set_horizontal_flip(!sprite.horizontal_flip());
        flicker = 0;
    }
    
}