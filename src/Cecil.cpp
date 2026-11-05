#include "Cecil.h"
#include "constants.h"
#include "common.h"
#include "bn_sprite_items_cecil.h"
#include "bn_sprite_items_cecil2.h"
#include "bn_sprite_items_cecil_bone_run1.h"
#include "bn_sprite_items_cecil_bone_run2.h"
#include "constants.h"

//constructor
Cecil::Cecil(int x, int y) : Entity(bn::sprite_items::cecil, x, y, constants::player::BASE_SPEED)
{

}

void Cecil::update()
{
    if(!active)
    {
        respawn++;
        if(respawn >= 600) {
            sprite.set_position(spawn_x, spawn_y);
            sprite.set_item(bn::sprite_items::cecil);
            sprite.set_horizontal_flip(false);
            sprite.set_visible(true);

            idle_timer = 0;
            second_pose = false;
            running = false;
            active = true;

            bounding_box = create_bounding_box(sprite, sprite.dimensions());
        }
        return;
    }

    if(running) {
        sprite.set_x(sprite.x() + run_direction * 2);

        idle_timer++;

        if(idle_timer >= 8) {
            second_pose = !second_pose;

            if(second_pose) {
                sprite.set_item(bn::sprite_items::cecil_bone_run2);
            } else {
                sprite.set_item(bn::sprite_items::cecil_bone_run1);
            }

            idle_timer = 0;
        }

        bounding_box = create_bounding_box(sprite, sprite.dimensions());

        //2.125 gives a little buffer off the screen
        bool right_edge = sprite.x() / 2.125 > constants::MAX_X;
        bool left_edge = sprite.x() / 2.125 < constants::MIN_X;

        if(left_edge || right_edge) {
            active = false;
            respawn = 0;
            sprite.set_visible(false);
        }
        
        return;
    }

    idle_timer++;

    if(idle_timer >= 32)
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
        if(sprite.x() < 0) {
            run_direction = 1; //right
        } else {
            run_direction = -1; //left
        }

        //if running right flip sprite
        sprite.set_horizontal_flip(run_direction == 1);

        running = true;
        idle_timer = 0;
        second_pose = false;

        sprite.set_item(bn::sprite_items::cecil_bone_run1);
    }
}

//is cecil active and NOT running
bool Cecil::blocks_player() {

    if (active && !running) {
        return true;
    }

    return false;
}