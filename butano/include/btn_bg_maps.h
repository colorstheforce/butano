#ifndef BTN_BG_MAPS_H
#define BTN_BG_MAPS_H

#include "btn_common.h"

namespace btn::bg_maps
{
    [[nodiscard]] int used_cells_count();

    [[nodiscard]] int available_cells_count();

    [[nodiscard]] int used_blocks_count();

    [[nodiscard]] int available_blocks_count();
}

#endif