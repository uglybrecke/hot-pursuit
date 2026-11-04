#include "Cecil.h"
#include "bn_sprite_items_cecil.h"
#include "bn_sprite_items_cecil2.h"
#include "bn_sprite_items_cecil_bone_run1.h"
#include "bn_sprite_items_cecil_bone_run2.h"

//construcor
Cecil::Cecil(int x, int y) :
    sprite(bn::sprite_items::cecil.create_sprite(x, y))
{
    bounding_box = create_bounding_box(sprite, sprite.dimensions());
}

void Cecil::update()
{
    if(running) {
        return;
    }
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

void Cecil::fetch(bool hit) {
    if(hit && !running) {
        running = true;
        sprite.set_item(bn::sprite_items::cecil_bone_run1);

        bounding_box = create_bounding_box(sprite, sprite.dimensions());
        //activate run sequence
        //check distance from edges of map
        //swap sprite to cecil_bone_run1
        //sprite flip to point in the right direction (farthest wall)
        //move him off the map horizontally
        //animate between bone_run1 and 2
        //set a timer to respawn him
    }
}