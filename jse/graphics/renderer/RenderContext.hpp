#pragma once

#include <cstdint>

namespace jse {

	class RenderContext
	{
		enum ClearFlags {
			CLEAR_SURFACE = 0x1,
			CLEAR_DEPTH = 0x2,
			CLEAR_STENCIL = 0x4
		};

	public:
		void begin_state_command(uint64_t sort_key);
		void end_state_command();
		void clear(ClearFlags flags);
		/*
			struct SurfaceInfo {
				uint32_t array_index; // 0 in all cases except if binding a texture array
				uint32_t slice;       // 0 for 2D textures, 0-5 for cube maps, 0-n for volume textures
				uint32_t mip_level;   // 0-n depending on wanted mip level
			};
		*/
		//void set_render_target(uint32_t slot, RenderTarget* target, const SurfaceInfo& surface_info);
		/*
		struct Viewport {
			float x, y, width, height;
			float min_depth, max_depth;
		};		
		*/
		//void set_viewports(uint32_t n_viewports, const Viewport* viewports);

		/*
		RenderJobPackage* render(const RenderJobPackage* job,
			const ShaderTemplate::Context& shader_context, uint64_t interleave_sort_key = 0,
			uint64_t shader_pass_branch_key = 0, float job_sort_depth = 0.f,
			uint32_t gpu_affinity_mask = GPU_DEFAULT);

		*/

		/*
		void *map_write(RenderResource *resource, render_sorting::SortKey sort_key,
			const ShaderTemplate::Context* shader_context = 0,
			shader_pass_branching::Flags shader_pass_branch_key = 0,
			uint32_t gpu_affinity_mask = GPU_DEFAULT);

		*/
	private:
		bool _is_recording{ false };
	};

}