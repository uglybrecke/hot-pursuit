#include "common.h"

bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size) {
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
};

//a helper function to stop the player from walking into a wall
void block_player(Player& player, const bn::rect& wall, bn::fixed p_x, bn::fixed p_y) {
        //make player not walk into a wall
        if(wall.intersects(player.bounding_box)) {
            player.sprite.set_x(p_x);
            player.sprite.set_y(p_y);

            player.bounding_box = create_bounding_box(player.sprite, player.size);
        }
}