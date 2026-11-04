#include "Fire.h"
#include "bn_sprite_items_fire.h"

Fire::Fire(int x, int y) :
    sprite(bn::sprite_items::fire.create_sprite(x, y))
{

}

//flip the sprite 
void Fire::update() {
    flicker++; //showing up as red, but code runs??

    if(flicker >= 30) {
        sprite.set_horizontal_flip(!sprite.horizontal_flip());
        flicker = 0;
    }
    
}