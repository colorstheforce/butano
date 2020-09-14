#ifndef BF_GAME_ENEMY_BULLET_TYPE_H
#define BF_GAME_ENEMY_BULLET_TYPE_H

#include "btn_common.h"

namespace bf::game
{

enum class enemy_bullet_type : int8_t
{
    SMALL,
    BIG,
    HUGE,
    ROBOT_SMALL,
    CAVEMAN_SMALL,
    CAVEMAN_BIG,
    CAVEMAN_FLIPPED_SMALL,
    CAVEMAN_FLIPPED_BIG,
    ASTRONAUT_SMALL,
    ASTRONAUT_BIG,
    YELLOW_SPACESHIP_SMALL,
    GREEN_SPACESHIP_SMALL,
};

}

#endif
