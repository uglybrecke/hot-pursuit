#include "Cecil.h"
#include "bn_sprite_items_cecil.h"
#include "bn_sprite_items_cecil2.h"

//construcor
Cecil::Cecil(int x, int y) :
    sprite(bn::sprite_items::cecil.create_sprite(x, y))
{
    bounding_box = create_bounding_box(sprite, sprite.dimensions());
}

void Cecil::update()
{
    idle_timer++;

    if(idle_timer >= 30)
    {
        //alternate back and forth
        second_pose = !second_pose;

        if(second_pose)
        {
            sprite.set_item(bn::sprite_items::cecil2);
        }
        else
        {
            sprite.set_item(bn::sprite_items::cecil);
        }

        idle_timer = 0;
    }
}