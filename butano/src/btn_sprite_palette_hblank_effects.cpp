#include "btn_sprite_palette_hblank_effects.h"

#include "btn_span.h"
#include "btn_color.h"
#include "btn_optional.h"
#include "btn_hblank_effect_handler.h"
#include "btn_hblank_effects_manager.h"
#include "../hw/include/btn_hw_palettes.h"

namespace btn
{

namespace
{
    class color_hblank_effect_handler : public hblank_effect_handler
    {

    public:
        color_hblank_effect_handler() = default;

        void setup_target(int, iany&) final
        {
        }

        [[nodiscard]] bool target_visible(int) final
        {
            return true;
        }

        [[nodiscard]] bool target_updated(int, iany&) final
        {
            return false;
        }

        [[nodiscard]] uint16_t* output_register(int target_id, const iany&) final
        {
            return hw::palettes::sprite_color_register(target_id);
        }

        void write_output_values(int, const iany&, int values_count, const void* input_values_ptr,
                                 uint16_t* output_values_ptr) final
        {
            memory::copy(*static_cast<const uint16_t*>(input_values_ptr), values_count, *output_values_ptr);
        }
    };


    class static_data
    {

    public:
        color_hblank_effect_handler color_handler;
    };

    BTN_DATA_EWRAM static_data data;
}

sprite_palette_color_hblank_effect_ptr sprite_palette_color_hblank_effect_ptr::create(
        sprite_palette_ptr palette_ptr, int color_index, const span<const color>& colors_ref)
{
    BTN_ASSERT(color_index >= 0 && color_index < palette_ptr.colors_count(),
               "Invalid color index: ", color_index, " - ", palette_ptr.colors_count());

    int final_color_index = (palette_ptr.id() * 16) + color_index;
    int id = hblank_effects_manager::create(colors_ref.data(), colors_ref.size(), final_color_index,
                                            data.color_handler);
    return sprite_palette_color_hblank_effect_ptr(id, color_index, move(palette_ptr));
}

optional<sprite_palette_color_hblank_effect_ptr> sprite_palette_color_hblank_effect_ptr::optional_create(
        sprite_palette_ptr palette_ptr, int color_index, const span<const color>& colors_ref)
{
    BTN_ASSERT(color_index >= 0 && color_index < palette_ptr.colors_count(),
               "Invalid color index: ", color_index, " - ", palette_ptr.colors_count());

    int final_color_index = (palette_ptr.id() * 16) + color_index;
    int id = hblank_effects_manager::optional_create(colors_ref.data(), colors_ref.size(), final_color_index,
                                                     data.color_handler);
    optional<sprite_palette_color_hblank_effect_ptr> result;

    if(id >= 0)
    {
        result = sprite_palette_color_hblank_effect_ptr(id, color_index, move(palette_ptr));
    }

    return result;
}

sprite_palette_color_hblank_effect_ptr::sprite_palette_color_hblank_effect_ptr(
        const sprite_palette_color_hblank_effect_ptr& other) :
    hblank_effect_ptr(other),
    _palette_ptr(other._palette_ptr),
    _color_index(other._color_index)
{
}

sprite_palette_color_hblank_effect_ptr& sprite_palette_color_hblank_effect_ptr::operator=(
        const sprite_palette_color_hblank_effect_ptr& other)
{
    hblank_effect_ptr::operator=(other);
    _palette_ptr = other._palette_ptr;
    _color_index = other._color_index;
    return *this;
}

sprite_palette_color_hblank_effect_ptr::sprite_palette_color_hblank_effect_ptr(
        sprite_palette_color_hblank_effect_ptr&& other) :
    hblank_effect_ptr(move(other)),
    _palette_ptr(move(other._palette_ptr)),
    _color_index(other._color_index)
{
}

sprite_palette_color_hblank_effect_ptr& sprite_palette_color_hblank_effect_ptr::operator=(
        sprite_palette_color_hblank_effect_ptr&& other)
{
    hblank_effect_ptr::operator=(move(other));
    _palette_ptr = move(other._palette_ptr);
    _color_index = other._color_index;
    return *this;
}

span<const color> sprite_palette_color_hblank_effect_ptr::colors_ref() const
{
    auto values_ptr = reinterpret_cast<const color*>(hblank_effects_manager::values_ref(id()));
    return span<const color>(values_ptr, hblank_effects_manager::values_count(id()));
}

void sprite_palette_color_hblank_effect_ptr::set_colors_ref(
        const span<const color>& colors_ref)
{
    hblank_effects_manager::set_values_ref(id(), colors_ref.data(), colors_ref.size());
}

void sprite_palette_color_hblank_effect_ptr::reload_colors_ref()
{
    hblank_effects_manager::reload_values_ref(id());
}

void sprite_palette_color_hblank_effect_ptr::swap(sprite_palette_color_hblank_effect_ptr& other)
{
    hblank_effect_ptr::swap(other);
}

sprite_palette_color_hblank_effect_ptr::sprite_palette_color_hblank_effect_ptr(
        int id, int color_index, sprite_palette_ptr&& palette_ptr) :
    hblank_effect_ptr(id),
    _palette_ptr(move(palette_ptr)),
    _color_index(color_index)
{
}

}
