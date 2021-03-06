/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_AFFINE_BG_MAP_ITEM_H
#define BN_AFFINE_BG_MAP_ITEM_H

/**
 * @file
 * bn::affine_bg_map_item header file.
 *
 * @ingroup affine_bg
 * @ingroup bg_map
 * @ingroup tool
 */

#include "bn_size.h"
#include "bn_optional_fwd.h"
#include "bn_affine_bg_map_cell.h"

namespace bn
{

class bg_palette_ptr;
class affine_bg_map_ptr;
class affine_bg_tiles_ptr;

/**
 * @brief Contains the required information to generate affine background maps.
 *
 * The assets conversion tools generate an object of this type in the build folder for each *.bmp file
 * with `affine_bg` type.
 *
 * The map cells are not copied but referenced, so they should outlive the affine_bg_map_item
 * to avoid dangling references.
 *
 * @ingroup affine_bg
 * @ingroup bg_map
 * @ingroup tool
 */
class affine_bg_map_item
{

public:
    /**
     * @brief Constructor.
     * @param cells_ref Reference to one or more affine background map cells.
     *
     * The map cells are not copied but referenced, so they should outlive the affine_bg_map_item
     * to avoid dangling references.
     *
     * @param dimensions Size in map cells of the referenced map cells.
     */
    constexpr affine_bg_map_item(const affine_bg_map_cell& cells_ref, const size& dimensions) :
        _cells_ptr(&cells_ref),
        _dimensions(dimensions)
    {
        BN_ASSERT(dimensions.width() == 16 || (dimensions.width() >= 32 && dimensions.width() % 32 == 0),
                  "Invalid width: ", dimensions.width());
        BN_ASSERT(dimensions.height() == 16 || (dimensions.height() >= 32 && dimensions.height() % 32 == 0),
                  "Invalid height: ", dimensions.height());
    }

    /**
     * @brief Returns the referenced map cells.
     */
    [[nodiscard]] constexpr const affine_bg_map_cell& cells_ref() const
    {
        return *_cells_ptr;
    }

    /**
     * @brief Returns the size in map cells of the referenced map cells.
     */
    [[nodiscard]] constexpr const size& dimensions() const
    {
        return _dimensions;
    }

    /**
     * @brief Searches for an affine_bg_map_ptr which references the information provided by this item.
     * @param tiles Referenced tiles of the map to search.
     * @param palette Referenced color palette of the map to search.
     * @return affine_bg_map_ptr which references the information provided by this item if it has been found;
     * bn::nullopt otherwise.
     */
    [[nodiscard]] optional<affine_bg_map_ptr> find_map(
            const affine_bg_tiles_ptr& tiles, const bg_palette_ptr& palette) const;

    /**
     * @brief Searches for an affine_bg_map_ptr which references the information provided by this item.
     * If it is not found, it creates an affine_bg_map_ptr which references it.
     *
     * The map cells are not copied but referenced,
     * so they should outlive the affine_bg_map_ptr to avoid dangling references.
     *
     * @param tiles Referenced tiles of the map to search or handle.
     * @param palette Referenced color palette of the map to search or handle.
     * @return affine_bg_map_ptr which references the information provided by this item if it has been found;
     * otherwise it returns an affine_bg_map_ptr which references it.
     */
    [[nodiscard]] affine_bg_map_ptr create_map(affine_bg_tiles_ptr tiles, bg_palette_ptr palette) const;

    /**
     * @brief Creates an affine_bg_map_ptr which references the information provided by this item.
     *
     * The map system does not support multiple affine_bg_map_ptr items referencing to the same map cells.
     * If you are not sure if the information provided by this item is already referenced or not,
     * you should use the create_map method instead.
     *
     * The map cells are not copied but referenced,
     * so they should outlive the affine_bg_map_ptr to avoid dangling references.
     *
     * @param tiles Referenced tiles of the map to handle.
     * @param palette Referenced color palette of the map to handle.
     * @return affine_bg_map_ptr which references the information provided by this item.
     */
    [[nodiscard]] affine_bg_map_ptr create_new_map(affine_bg_tiles_ptr tiles, bg_palette_ptr palette) const;

    /**
     * @brief Searches for an affine_bg_map_ptr which references the information provided by this item.
     * If it is not found, it creates an affine_bg_map_ptr which references it.
     *
     * The map cells are not copied but referenced,
     * so they should outlive the affine_bg_map_ptr to avoid dangling references.
     *
     * @param tiles Referenced tiles of the map to search or handle.
     * @param palette Referenced color palette of the map to search or handle.
     * @return affine_bg_map_ptr which references the information provided by this item if it has been found;
     * otherwise it returns an affine_bg_map_ptr which references it if it could be allocated;
     * bn::nullopt otherwise.
     */
    [[nodiscard]] optional<affine_bg_map_ptr> create_map_optional(
            affine_bg_tiles_ptr tiles, bg_palette_ptr palette) const;

    /**
     * @brief Creates an affine_bg_map_ptr which references the information provided by this item.
     *
     * The map system does not support multiple affine_bg_map_ptr items referencing to the same map cells.
     * If you are not sure if the information provided by this item is already referenced or not,
     * you should use the create_map_optional method instead.
     *
     * The map cells are not copied but referenced,
     * so they should outlive the affine_bg_map_ptr to avoid dangling references.
     *
     * @param tiles Referenced tiles of the map to handle.
     * @param palette Referenced color palette of the map to handle.
     * @return affine_bg_map_ptr which references the information provided by this item
     * if the affine_bg_map_ptr can be allocated; bn::nullopt otherwise.
     */
    [[nodiscard]] optional<affine_bg_map_ptr> create_new_map_optional(
            affine_bg_tiles_ptr tiles, bg_palette_ptr palette) const;

    /**
     * @brief Default equal operator.
     */
    [[nodiscard]] constexpr friend bool operator==(const affine_bg_map_item& a,
                                                   const affine_bg_map_item& b) = default;

private:
    const affine_bg_map_cell* _cells_ptr;
    size _dimensions;
};

}

#endif
