#include "graphics/BufferObject.hpp"
#include "core/io/Logger.hpp"

#include "./common_GL.hpp"

namespace jse::graphics {


	ArrayBufferObject::ArrayBufferObject()
	{
		buffer = INVALID_BUFFER_ID;
		alloced = 0;
		size = 0;
		bufferUsage_ = BU_LAST_ENUM;
	}

	ArrayBufferObject::~ArrayBufferObject()
	{
		if (buffer != INVALID_BUFFER_ID)
		{
			glDeleteBuffers(1, (GLuint*)&buffer);
		}
	}

	bool ArrayBufferObject::Create(size_t size, bufferUsage_t usage_, const void* data)
	{
		if (size == 0)
			return false;

		bufferUsage_ = usage_;

		if (buffer != INVALID_BUFFER_ID)
		{
			core::io::Warning("ArrayBuffer: buffer object already created !");
			return false;
		}

		glGenBuffers(1, (GLuint*)&buffer);

		GLenum err = glGetError();

		if (err != GLEW_OK)
			return false;

		this->size = size;
		this->alloced = 0;

		GLenum usage = bufferUsage2GL(usage_);

		if (data) {
			alloced = size;
		}

		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	bool ArrayBufferObject::Alloc(size_t allocSize, const void* data)
	{
		if (allocSize + alloced > size)
		{
			core::io::Warning("ArrayBufferObject: allocation request exceeds buffer size !");
			return false;
		}

		glBufferSubData(GL_ARRAY_BUFFER, alloced, allocSize, data);
		alloced += allocSize;

		return true;
	}

	bool ArrayBufferObject::UpdateSubData(size_t offset, size_t size, const void* data)
	{
		if (offset + size > this->size || !data) {
			return false;
		}

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void ArrayBufferObject::Reset()
	{
		alloced = 0;
	}

	void ArrayBufferObject::Realloc()
	{
		GLenum usage = bufferUsage2GL(bufferUsage_);

		glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage);
	}

	void ArrayBufferObject::Bind()
	{
		if (buffer != INVALID_BUFFER_ID) {
			glBindBuffer(GL_ARRAY_BUFFER, (GLuint)buffer);
		}
	}
}
