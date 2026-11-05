#include "FireManager.h"
#include "common.h"

void FireManager::spawn(int x, int y) {
    if(!fires.full()) {
        fires.push_back(Fire(x, y));
    }
}

void FireManager::update(Player& player, Cecil& cecil, bn::fixed previous_x, bn::fixed previous_y) {
    for(int i = 0; i < fires.size(); ) {
        fires[i].update();

        if(cecil.is_running() &&
           cecil.bounding_box.intersects(fires[i].bounding_box)) {
            fires.erase(fires.begin() + i);
        } else {
            block_player(player, fires[i].bounding_box, previous_x, previous_y);
            i++;
        }
    }
}