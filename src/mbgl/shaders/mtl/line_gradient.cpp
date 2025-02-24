#include <mbgl/shaders/mtl/line_gradient.hpp>

namespace mbgl {
namespace shaders {

const std::array<AttributeInfo, 7> ShaderSource<BuiltIn::LineGradientShader, gfx::Backend::Type::Metal>::attributes = {
    AttributeInfo{0, gfx::AttributeDataType::Short2, 1, "a_pos_normal"},
    AttributeInfo{1, gfx::AttributeDataType::UByte4, 1, "a_data"},
    AttributeInfo{2, gfx::AttributeDataType::Float2, 1, "a_blur"},
    AttributeInfo{3, gfx::AttributeDataType::Float2, 1, "a_opacity"},
    AttributeInfo{4, gfx::AttributeDataType::Float2, 1, "a_gapwidth"},
    AttributeInfo{5, gfx::AttributeDataType::Float2, 1, "a_offset"},
    AttributeInfo{6, gfx::AttributeDataType::Float2, 1, "a_width"},
};
const std::array<UniformBlockInfo, 5> ShaderSource<BuiltIn::LineGradientShader, gfx::Backend::Type::Metal>::uniforms = {
    UniformBlockInfo{7, true, true, sizeof(LineGradientUBO), "LineGradientUBO"},
    UniformBlockInfo{8, true, false, sizeof(LineGradientPropertiesUBO), "LineGradientPropertiesUBO"},
    UniformBlockInfo{9, true, false, sizeof(LineGradientInterpolationUBO), "LineGradientInterpolationUBO"},
    UniformBlockInfo{10, true, true, sizeof(LinePermutationUBO), "LinePermutationUBO"},
    UniformBlockInfo{11, true, false, sizeof(ExpressionInputsUBO), "ExpressionInputsUBO"},
};
const std::array<TextureInfo, 1> ShaderSource<BuiltIn::LineGradientShader, gfx::Backend::Type::Metal>::textures = {
    TextureInfo{0, "u_image"},
};

} // namespace shaders
} // namespace mbgl
