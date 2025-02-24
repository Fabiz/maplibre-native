#pragma once

#include <mbgl/gfx/cull_face_mode.hpp>
#include <mbgl/gfx/drawable_impl.hpp>
#include <mbgl/gfx/index_buffer.hpp>
#include <mbgl/gfx/program.hpp>
#include <mbgl/gfx/uniform.hpp>
#include <mbgl/gfx/uniform_buffer.hpp>
#include <mbgl/gfx/vertex_attribute.hpp>
#include <mbgl/mtl/mtl_fwd.hpp>
#include <mbgl/mtl/render_pass.hpp>
#include <mbgl/mtl/uniform_buffer.hpp>
#include <mbgl/mtl/upload_pass.hpp>
#include <mbgl/mtl/vertex_buffer_resource.hpp>
#include <mbgl/programs/segment.hpp>
#include <mbgl/renderer/paint_parameters.hpp>
#include <mbgl/util/mat4.hpp>
#include <mbgl/util/string_indexer.hpp>

#include <Foundation/NSSharedPtr.hpp>
#include <Metal/MTLVertexDescriptor.hpp>

#include <cstdint>
#include <memory>
#include <vector>

namespace mbgl {
namespace mtl {

using namespace platform;

class Drawable::Impl final {
public:
    Impl() = default;
    ~Impl() = default;

    std::vector<UniqueDrawSegment> segments;

    MTLVertexDescriptorPtr vertexDesc;

    /*
        std::vector<TextureID> textures;
    */
    gfx::IndexVectorBasePtr indexes;
    std::size_t vertexCount = 0;
    gfx::AttributeDataType vertexType = gfx::AttributeDataType::Invalid;
    gfx::VertexAttributeArray vertexAttributes;

    std::vector<gfx::UniqueVertexBufferResource> attributeBuffers;

    UniformBufferArray uniformBuffers;

    gfx::DepthMode depthMode = gfx::DepthMode::disabled();
    gfx::StencilMode stencilMode;
    gfx::CullFaceMode cullFaceMode;
    // GLfloat pointSize = 0.0f;
    StringIdentity idVertexAttrName = stringIndexer().get("a_pos");

    VertexBufferResource* noBindingBuffer = nullptr;

    gfx::AttributeBindingArray attributeBindings;

    MTLRenderPipelineStatePtr pipelineState;

    std::optional<gfx::RenderPassDescriptor> renderPassDescriptor;

    MTLDepthStencilStatePtr depthStencilState;
    gfx::StencilMode previousStencilMode;
};

struct Drawable::DrawSegment final : public gfx::Drawable::DrawSegment {
    DrawSegment(gfx::DrawMode mode_, SegmentBase&& segment_)
        : gfx::Drawable::DrawSegment(mode_, std::move(segment_)) {}
    ~DrawSegment() override = default;

protected:
};

} // namespace mtl
} // namespace mbgl
