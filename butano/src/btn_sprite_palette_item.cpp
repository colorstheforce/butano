#include "btn_sprite_palette_item.h"

#include "btn_optional.h"
#include "btn_sprite_palette_ptr.h"

namespace btn
{

sprite_palette_ptr sprite_palette_item::create_palette(create_mode create_mode) const
{
    switch(create_mode)
    {

    case create_mode::FIND_OR_CREATE:
        return sprite_palette_ptr::find_or_create(_palette_ref, _bpp_mode);

    case create_mode::FORCE_CREATE:
        return sprite_palette_ptr::create(_palette_ref, _bpp_mode);
    }

    BTN_ERROR("Invalid create mode: ", int(create_mode));
}

optional<sprite_palette_ptr> sprite_palette_item::optional_create_palette(create_mode create_mode) const
{
    optional<sprite_palette_ptr> result;

    switch(create_mode)
    {

    case create_mode::FIND_OR_CREATE:
        result = sprite_palette_ptr::optional_find_or_create(_palette_ref, _bpp_mode);
        break;

    case create_mode::FORCE_CREATE:
        result = sprite_palette_ptr::optional_create(_palette_ref, _bpp_mode);
        break;
    }

    return result;
}

}
