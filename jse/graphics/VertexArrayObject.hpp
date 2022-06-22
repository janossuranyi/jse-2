#ifndef JSE_GRAPHICS_VERTEX_ARRAY_OBJECT
#define JSE_GRAPHICS_VERTEX_ARRAY_OBJECT

#include "graphics/BufferObject.hpp"

namespace jse {
	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();
		bool CreateInterleaved(const ArrayBufferObject& arrayBuf, const ElementBufferObject& elementBuf);
		bool CreateSeparate(
			const ArrayBufferObject& positionBuf,
			const ArrayBufferObject& normalBuf,
			const ArrayBufferObject& texcoordBuf,
			const ArrayBufferObject& tangentBuf,
			const ElementBufferObject& elementBuf);
		bool IsCreated() const;
		void Bind() const;
	private:
		unsigned int vao;
		bool created{ false };
	};
}
#endif // !JSE_GRAPHICS_VERTEX_ARRAY_OBJECT
