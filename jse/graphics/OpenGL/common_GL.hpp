#ifndef JSE_COMMON_GL_H
#define JSE_COMMON_GL_H

#include <GL/glew.h>
#include "graphics/BufferObject.hpp"

namespace jse {

	inline GLenum bufferUsage2GL(bufferUsage_t _x)
	{
		GLenum usage;

		switch (_x)
		{
		case BU_DYNAMIC:
			usage = GL_DYNAMIC_DRAW;
			break;
		case BU_STATIC:
			usage = GL_STATIC_DRAW;
			break;
		default:
			usage = GL_STATIC_DRAW;
		}

		return usage;
	}

}

#endif // !JSE_COMMON_GL_H

