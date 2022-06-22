#include "graphics/VertexArrayObject.hpp"
#include "graphics/DrawVert.hpp"

#include <GL/glew.h>

namespace jse {

	VertexArrayObject::VertexArrayObject()
	{
		vao = GL_INVALID_INDEX;
		created = false;
	}

	VertexArrayObject::~VertexArrayObject()
	{
		if (vao != GL_INVALID_INDEX)
		{
			glDeleteVertexArrays(1, (GLuint*)&vao);
		}
	}

	bool VertexArrayObject::CreateInterleaved(const ArrayBufferObject& arrayBuf, const ElementBufferObject& elementBuf)
	{
		if (vao == GL_INVALID_INDEX)
		{
			glCreateVertexArrays(1, (GLuint*)&vao);
			GLenum err = glGetError();
			if (err != GL_NO_ERROR) return false;
		}

		glBindVertexArray(vao);
		arrayBuf.Bind();
		elementBuf.Bind();

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);

		glVertexAttribPointer(DRAWVERT_POSITION_INDEX,	3, GL_FLOAT,			GL_FALSE,	DRAW_VERT_SIZE, (void*)DRAWVERT_POSITION_OFFSET);
		glVertexAttribPointer(DRAWVERT_TEXCOORD_INDEX,	2, GL_HALF_FLOAT,		GL_FALSE,	DRAW_VERT_SIZE, (void*)DRAWVERT_TEXCOORD_OFFSET);
		glVertexAttribPointer(DRAWVERT_NORMAL_INDEX,	4, GL_UNSIGNED_BYTE,	GL_TRUE,	DRAW_VERT_SIZE, (void*)DRAWVERT_NORMAL_OFFSET);
		glVertexAttribPointer(DRAWVERT_TANGENT_INDEX,	4, GL_UNSIGNED_BYTE,	GL_TRUE,	DRAW_VERT_SIZE, (void*)DRAWVERT_TANGENT_OFFSET);
		glVertexAttribPointer(DRAWVERT_COLOR_INDEX,		4, GL_UNSIGNED_BYTE,	GL_TRUE,	DRAW_VERT_SIZE, (void*)DRAWVERT_COLOR_OFFSET);
		glVertexAttribPointer(DRAWVERT_COLOR2_INDEX,	4, GL_UNSIGNED_BYTE,	GL_TRUE,	DRAW_VERT_SIZE, (void*)DRAWVERT_COLOR2_OFFSET);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		created = true;

		return true;
	}

	bool VertexArrayObject::CreateSeparate(
		const ArrayBufferObject& positionBuf,
		const ArrayBufferObject& normalBuf,
		const ArrayBufferObject& texcoordBuf,
		const ArrayBufferObject& tangentBuf,
		const ElementBufferObject& elementBuf)
	{
		return false;
	}
	bool VertexArrayObject::IsCreated() const { return created; }
	
	void VertexArrayObject::Bind() const
	{
		if (vao != GL_INVALID_INDEX && created)
		{
			glBindVertexArray(vao);
		}
	}
	
}
