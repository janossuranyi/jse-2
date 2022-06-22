#include "graphics/BufferObject.hpp"
#include "core/io/Logger.hpp"

#include "./common_GL.hpp"

namespace jse {


	UniformBufferObject::UniformBufferObject()
	{
		buffer = GL_INVALID_INDEX;
		alloced = 0;
		size = 0;
		bufferUsage_ = BU_LAST_ENUM;
		bindingIndex = GL_INVALID_INDEX;
	}

	UniformBufferObject::~UniformBufferObject()
	{
		if (buffer != GL_INVALID_INDEX)
		{
			glDeleteBuffers(1, (GLuint*)&buffer);
		}
	}

	UniformBufferObject::UniformBufferObject(UniformBufferObject&& other) noexcept
	{
		size = other.size;
		buffer = other.buffer;
		alloced = other.alloced;
		bufferUsage_ = other.bufferUsage_;
		bindingIndex = other.bindingIndex;

		other.size = 0;
		other.buffer = GL_INVALID_INDEX;
		other.alloced = 0;
		other.bufferUsage_ = BU_LAST_ENUM;
		other.bindingIndex = GL_INVALID_INDEX;
	}

	UniformBufferObject& UniformBufferObject::operator=(UniformBufferObject&& other) noexcept
	{
		size = other.size;
		buffer = other.buffer;
		alloced = other.alloced;
		bufferUsage_ = other.bufferUsage_;
		bindingIndex = other.bindingIndex;

		other.size = 0;
		other.buffer = GL_INVALID_INDEX;
		other.alloced = 0;
		other.bufferUsage_ = BU_LAST_ENUM;
		other.bindingIndex = GL_INVALID_INDEX;

		return *this;
	}

	bool UniformBufferObject::Create(size_t size, bufferUsage_t usage_, const void* data)
	{
		if (size == 0)
			return false;

		bufferUsage_ = usage_;

		if (buffer != GL_INVALID_INDEX)
		{
			Warning("UniformBufferObject: buffer object already created !");
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

		glBindBuffer(GL_UNIFORM_BUFFER, buffer);
		glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	bool UniformBufferObject::Alloc(size_t allocSize, const void* data)
	{
		if (allocSize + alloced > size)
		{
			Warning("UniformBufferObject: allocation request exceeds buffer size !");
			return false;
		}

		glBufferSubData(GL_UNIFORM_BUFFER, alloced, allocSize, data);
		alloced += allocSize;

		return true;
	}

	bool UniformBufferObject::UpdateSubData(size_t offset, size_t size, const void* data)
	{
		if (offset + size > this->size || !data) {
			return false;
		}

		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	}

	void UniformBufferObject::Reset()
	{
		alloced = 0;
	}

	void UniformBufferObject::Realloc()
	{
		GLenum usage = bufferUsage2GL(bufferUsage_);

		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, usage);
	}

	void UniformBufferObject::BindToShader(unsigned progId, unsigned bindigPoint)
	{
		if (buffer != GL_INVALID_INDEX && bindingIndex != GL_INVALID_INDEX) {
			glUniformBlockBinding((GLuint)progId, (GLuint)bindingIndex, (GLuint)bindigPoint);
		}
	}
	void UniformBufferObject::BindToIndex(const unsigned blockIndex)
	{
		if (buffer != GL_INVALID_INDEX)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, (GLuint)blockIndex, buffer);
			bindingIndex = blockIndex;
		}
	}
	void UniformBufferObject::BindToIndexRange(const unsigned blockIndex, const unsigned offset, const size_t size)
	{
		if (buffer != GL_INVALID_INDEX)
		{
			glBindBufferRange(GL_UNIFORM_BUFFER, (GLuint)blockIndex, buffer, offset, size);
			bindingIndex = blockIndex;
		}
	}

	size_t UniformBufferObject::GetAlloced() const
	{
		return alloced;
	}
}
