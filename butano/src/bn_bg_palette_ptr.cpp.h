/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_bg_palette_ptr.h"

#include "bn_bg_palette_item.h"
#include "bn_palettes_bank.h"
#include "bn_palettes_manager.h"

namespace bn
{

optional<bg_palette_ptr> bg_palette_ptr::find(const bg_palette_item& palette_item)
{
    const span<const color>& colors = palette_item.colors_ref();
    palettes_bank& bg_palettes_bank = palettes_manager::bg_palettes_bank();
    int id;

    if(palette_item.bpp() == bpp_mode::BPP_4)
    {
        id = bg_palettes_bank.find_bpp_4(colors, palettes_bank::colors_hash(colors));
    }
    else
    {
        id = bg_palettes_bank.find_bpp_8(colors);
    }

    optional<bg_palette_ptr> result;

    if(id >= 0)
    {
        result = bg_palette_ptr(id);
    }

    return result;
}

bg_palette_ptr bg_palette_ptr::create(const bg_palette_item& palette_item)
{
    const span<const color>& colors = palette_item.colors_ref();
    palettes_bank& bg_palettes_bank = palettes_manager::bg_palettes_bank();
    int id;

    if(palette_item.bpp() == bpp_mode::BPP_4)
    {
        uint16_t hash = palettes_bank::colors_hash(colors);
        id = bg_palettes_bank.find_bpp_4(colors, hash);

        if(id < 0)
        {
            id = bg_palettes_bank.create_bpp_4(colors, hash, true);
        }
    }
    else
    {
        id = bg_palettes_bank.find_bpp_8(colors);

        if(id < 0)
        {
            id = bg_palettes_bank.create_bpp_8(colors, true);
        }
    }

    return bg_palette_ptr(id);
}

bg_palette_ptr bg_palette_ptr::create_new(const bg_palette_item& palette_item)
{
    const span<const color>& colors = palette_item.colors_ref();
    palettes_bank& bg_palettes_bank = palettes_manager::bg_palettes_bank();
    int id;

    if(palette_item.bpp() == bpp_mode::BPP_4)
    {
        id = bg_palettes_bank.create_bpp_4(colors, palettes_bank::colors_hash(colors), true);
    }
    else
    {
        id = bg_palettes_bank.create_bpp_8(colors, true);
    }

    return bg_palette_ptr(id);
}

optional<bg_palette_ptr> bg_palette_ptr::create_optional(const bg_palette_item& palette_item)
{
    const span<const color>& colors = palette_item.colors_ref();
    palettes_bank& bg_palettes_bank = palettes_manager::bg_palettes_bank();
    int id;

    if(palette_item.bpp() == bpp_mode::BPP_4)
    {
        uint16_t hash = palettes_bank::colors_hash(colors);
        id = bg_palettes_bank.find_bpp_4(colors, hash);

        if(id < 0)
        {
            id = bg_palettes_bank.create_bpp_4(colors, hash, false);
        }
    }
    else
    {
        id = bg_palettes_bank.find_bpp_8(colors);

        if(id < 0)
        {
            id = bg_palettes_bank.create_bpp_8(colors, false);
        }
    }

    optional<bg_palette_ptr> result;

    if(id >= 0)
    {
        result = bg_palette_ptr(id);
    }

    return result;
}

optional<bg_palette_ptr> bg_palette_ptr::create_new_optional(const bg_palette_item& palette_item)
{
    const span<const color>& colors = palette_item.colors_ref();
    palettes_bank& bg_palettes_bank = palettes_manager::bg_palettes_bank();
    int id;

    if(palette_item.bpp() == bpp_mode::BPP_4)
    {
        id = bg_palettes_bank.create_bpp_4(colors, palettes_bank::colors_hash(colors), false);
    }
    else
    {
        id = bg_palettes_bank.create_bpp_8(colors, false);
    }

    optional<bg_palette_ptr> result;

    if(id >= 0)
    {
        result = bg_palette_ptr(id);
    }

    return result;
}

bg_palette_ptr::bg_palette_ptr(const bg_palette_ptr& other) :
    _id(other._id)
{
    palettes_manager::bg_palettes_bank().increase_usages(_id);
}

bg_palette_ptr& bg_palette_ptr::operator=(const bg_palette_ptr& other)
{
    if(_id != other._id)
    {
        if(_id >= 0)
        {
            palettes_manager::bg_palettes_bank().decrease_usages(_id);
        }

        _id = other._id;
        palettes_manager::bg_palettes_bank().increase_usages(_id);
    }

    return *this;
}

int bg_palette_ptr::colors_count() const
{
    return palettes_manager::bg_palettes_bank().colors_count(_id);
}

span<const color> bg_palette_ptr::colors() const
{
    return palettes_manager::bg_palettes_bank().colors(_id);
}

void bg_palette_ptr::set_colors(const bg_palette_item& palette_item)
{
    palettes_manager::bg_palettes_bank().set_colors(_id, palette_item.colors_ref());
}

bpp_mode bg_palette_ptr::bpp() const
{
    return palettes_manager::bg_palettes_bank().bpp(_id);
}

bool bg_palette_ptr::inverted() const
{
    return palettes_manager::bg_palettes_bank().inverted(_id);
}

void bg_palette_ptr::set_inverted(bool inverted)
{
    palettes_manager::bg_palettes_bank().set_inverted(_id, inverted);
}

fixed bg_palette_ptr::grayscale_intensity() const
{
    return palettes_manager::bg_palettes_bank().grayscale_intensity(_id);
}

void bg_palette_ptr::set_grayscale_intensity(fixed intensity)
{
    palettes_manager::bg_palettes_bank().set_grayscale_intensity(_id, intensity);
}

color bg_palette_ptr::fade_color() const
{
    return palettes_manager::bg_palettes_bank().fade_color(_id);
}

fixed bg_palette_ptr::fade_intensity() const
{
    return palettes_manager::bg_palettes_bank().fade_intensity(_id);
}

void bg_palette_ptr::set_fade_color(color color)
{
    palettes_manager::bg_palettes_bank().set_fade_color(_id, color);
}

void bg_palette_ptr::set_fade_intensity(fixed intensity)
{
    palettes_manager::bg_palettes_bank().set_fade_intensity(_id, intensity);
}

void bg_palette_ptr::set_fade(color color, fixed intensity)
{
    palettes_manager::bg_palettes_bank().set_fade(_id, color, intensity);
}

int bg_palette_ptr::rotate_count() const
{
    return palettes_manager::bg_palettes_bank().rotate_count(_id);
}

void bg_palette_ptr::set_rotate_count(int count)
{
    palettes_manager::bg_palettes_bank().set_rotate_count(_id, count);
}

void bg_palette_ptr::_destroy()
{
    palettes_manager::bg_palettes_bank().decrease_usages(_id);
}

}
