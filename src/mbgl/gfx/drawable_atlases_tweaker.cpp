#include <mbgl/gfx/drawable_atlases_tweaker.hpp>

#include <mbgl/gfx/drawable.hpp>
#include <mbgl/renderer/tile_render_data.hpp>
#include <mbgl/shaders/shader_program_base.hpp>
#include <mbgl/renderer/paint_parameters.hpp>

namespace mbgl {
namespace gfx {

void DrawableAtlasesTweaker::setupTextures(gfx::Drawable& drawable, const bool linearFilterForIcons) {
    if (const auto& shader = drawable.getShader()) {
        if (const auto samplerLocation = shader->getSamplerLocation(glyphNameId)) {
            if (atlases) {
                atlases->glyph->setSamplerConfiguration(
                    {TextureFilterType::Linear, TextureWrapType::Clamp, TextureWrapType::Clamp});
                atlases->icon->setSamplerConfiguration(
                    {linearFilterForIcons ? TextureFilterType::Linear : TextureFilterType::Nearest,
                     TextureWrapType::Clamp,
                     TextureWrapType::Clamp});
            }
            if (const auto iconSamplerLocation = shader->getSamplerLocation(iconNameId)) {
                assert(*samplerLocation != *iconSamplerLocation);
                drawable.setTexture(atlases ? atlases->glyph : nullptr, *samplerLocation);
                drawable.setTexture(atlases ? atlases->icon : nullptr, *iconSamplerLocation);
            } else {
                drawable.setTexture(atlases ? (isText ? atlases->glyph : atlases->icon) : nullptr, *samplerLocation);
            }
        }
    }
}

void DrawableAtlasesTweaker::init(gfx::Drawable& drawable) {
    setupTextures(drawable, true);
}

void DrawableAtlasesTweaker::execute(gfx::Drawable& drawable, const PaintParameters& parameters) {
    const bool transformed = rotationAlignment == style::AlignmentType::Map || parameters.state.getPitch() != 0;
    const bool linearFilterForIcons = isText ? (parameters.state.isChanging() || transformed || !textSizeIsZoomConstant)
                                             : (sdfIcons || parameters.state.isChanging() || iconScaled || transformed);

    setupTextures(drawable, linearFilterForIcons);
}

} // namespace gfx
} // namespace mbgl
