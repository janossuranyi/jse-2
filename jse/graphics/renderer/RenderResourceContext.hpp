#pragma once

#include "RenderResoure.hpp"

namespace jse {

	class RenderResourceContext
	{
	public:
		void alloc(RenderResource* resource);
		void dealloc(RenderResource* resource);
	};

}