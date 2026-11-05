#pragma once

#include <bn_vector.h>
#include "Fire.h"
#include "Cecil.h"
#include "Player.h"

class FireManager {
public:
    void spawn(int x, int y);
    void update(Player& player, Cecil& cecil,
                bn::fixed previous_x, bn::fixed previous_y);

private:
    bn::vector<Fire, 12> fires;
};