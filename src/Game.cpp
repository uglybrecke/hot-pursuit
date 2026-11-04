#include "Game.h"
#include "Player.h"
#include "ScoreDisplay.h"
#include "constants.h"
#include "common.h"

void reset_game(Player& player, ScoreDisplay& scoreDisplay)
{
    scoreDisplay.resetScore();

    player.sprite.set_x(constants::player::INITIAL_X);
    player.sprite.set_y(constants::player::INITIAL_Y);

    player.bounding_box = create_bounding_box(player.sprite, player.size);
}