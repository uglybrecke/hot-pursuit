#pragma once

#include <bn_display.h>
#include <bn_size.h>

namespace constants {

    static constexpr int MIN_Y = -bn::display::height() / 2;
    static constexpr int MAX_Y = bn::display::height() / 2;
    static constexpr int MIN_X = -bn::display::width() / 2;
    static constexpr int MAX_X = bn::display::width() / 2;

    static constexpr int MAX_ENEMIES = 15;

    namespace score {
        // Number of characters required to show two of the longest numbers possible in an int (-2147483647)
        static constexpr int MAX_SCORE_CHARS = 22;

        // Score location
        static constexpr int SCORE_X = 70;
        static constexpr int SCORE_Y = -70;

        // High score location
        static constexpr int HIGH_SCORE_X = -70;
        static constexpr int HIGH_SCORE_Y = -70;
    }

    namespace player {
        static constexpr int INITIAL_X = 44;
        static constexpr int INITIAL_Y = 22;
        static constexpr bn::fixed BASE_SPEED = 1.5;
        // Bounding box size
        static constexpr bn::size SIZE = {8, 8};
    }

    namespace enemy {
        static constexpr int INITIAL_X = -50;
        static constexpr int INITIAL_Y = 40;
        static constexpr bn::fixed BASE_SPEED = 0.7;
        static constexpr bn::size SIZE = {16, 16};
    }

}