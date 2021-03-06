/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_HDMA_H
#define BN_HDMA_H

/**
 * @file
 * bn::hdma header file.
 *
 * @ingroup hdma
 */

#include "bn_common.h"

/**
 * @brief H-Blank direct memory access related functions.
 *
 * @ingroup hdma
 */
namespace bn::hdma
{
    /**
     * @brief Start copying each frame the given amount of elements from the memory location referenced by source_ref
     * to the memory location referenced to by destination_ref.
     *
     * The elements are not copied but referenced,
     * so they should be alive while HDMA is running to avoid dangling references.
     *
     * If the elements overlap, the behavior is undefined.
     *
     * @param source_ref Const reference to the memory location to copy from.
     * @param elements Number of elements to copy (not bytes).
     * @param destination_ref Reference to the memory location to copy to.
     */
    void start(const uint16_t& source_ref, int elements, uint16_t& destination_ref);

    /**
     * @brief Stops copying elements each frame.
     */
    void stop();
}

#endif
