#include "graphics/BufferObject.hpp"
#include "core/io/Logger.hpp"

#include "./common_GL.hpp"

namespace jse {


	ArrayBufferObject::ArrayBufferObject()
	{
		buffer = GL_INVALID_INDEX;
		alloced = 0;
		size = 0;
		bufferUsage_ = BU_LAST_ENUM;
	}

	ArrayBufferObject::~ArrayBufferObject()
	{
		if (buffer != GL_INVALID_INDEX)
		{
			glDeleteBuffers(1, (GLuint*)&buffer);
		}
	}

	ArrayBufferObject& ArrayBufferObject::operator=(ArrayBufferObject&& other) noexcept
	{
		size = other.size;
		buffer = other.buffer;
		alloced = other.alloced;
		bufferUsage_ = other.bufferUsage_;

		other.size = 0;
		other.buffer = GL_INVALID_INDEX;
		other.alloced = 0;
		other.bufferUsage_ = BU_LAST_ENUM;

		return *this;

	}

	ArrayBufferObject::ArrayBufferObject(ArrayBufferObject&& other) noexcept
	{
		size = other.size;
		buffer = other.buffer;
		alloced = other.alloced;
		bufferUsage_ = other.bufferUsage_;

		other.size = 0;
		other.buffer = GL_INVALID_INDEX;
		other.alloced = 0;
		other.bufferUsage_ = BU_LAST_ENUM;
	}

	bool ArrayBufferObject::Create(size_t size, bufferUsage_t usage_, const void* data)
	{
		if (size == 0)
			return false;

		bufferUsage_ = usage_;

		if (buffer != GL_INVALID_INDEX)
		{
			Warning("ArrayBuffer: buffer object already created !");
			return false;
		}

		glGenBuffers(1, (GLuint*)&buffer);

		GLenum err = glGetError();

		if (err != GL_NO_ERROR)
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

		return true;
	}

	bool ArrayBufferObject::Alloc(size_t allocSize, const void* data)
	{
		if (allocSize + alloced > size)
		{
			Warning("ArrayBufferObject: allocation request exceeds buffer size !");
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

		return true;
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

	void ArrayBufferObject::Bind() const
	{
		if (buffer != GL_INVALID_INDEX) {
			glBindBuffer(GL_ARRAY_BUFFER, (GLuint)buffer);
		}
	}
	size_t ArrayBufferObject::GetAllocated() const
	{
		return alloced;
	}
}
