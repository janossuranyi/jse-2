#pragma once

#include <cstdint>

namespace jse {

    struct RenderResource
    {
        using Handle = uint32_t;

        enum {
            TEXTURE, RENDER_TARGET, DEPENDENT_RENDER_TARGET, BACK_BUFFER_WRAPPER,
            UNIFORM_BUFFER, VERTEX_STREAM, INDEX_STREAM, RAW_BUFFER,
            BATCH_INFO, VERTEX_DECLARATION, SHADER,
            NOT_INITIALIZED = 0xFFFFFFFF
        };

        /*
        The most significant 8 bits of render_resource_handle holds the type enum, 
        the lower 24 bits is simply an index into an array for that specific resource type inside the RenderDevice.
        */
        Handle render_resource_handle;

        RenderResource() : render_resource_handle(NOT_INITIALIZED) {}
        RenderResource(const uint32_t type) : render_resource_handle((type << 24) & 0xFF000000) {}

        bool is_initialized() const { return render_resource_handle != NOT_INITIALIZED; }
        uint32_t get_type() const { return (render_resource_handle & 0xFF000000) >> 24; }
    };

}