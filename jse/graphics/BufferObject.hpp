#ifndef JSE_GRAPHICS_BUFFER_OBJECT_H
#define JSE_GRAPHICS_BUFFER_OBJECT_H

#include <cstdio>

namespace jse {

	enum bufferUsage_t
	{
		BU_STATIC,
		BU_DYNAMIC,
		BU_LAST_ENUM
	};
	
	class ArrayBufferObject
	{
	public:
		ArrayBufferObject();
		~ArrayBufferObject();

		ArrayBufferObject(const ArrayBufferObject&) = delete;
		ArrayBufferObject(ArrayBufferObject&&) noexcept;
		ArrayBufferObject& operator=(ArrayBufferObject&) = delete;
		ArrayBufferObject& operator=(ArrayBufferObject&&) noexcept;

		bool Create(size_t size, bufferUsage_t usage, const void* data = nullptr);
		bool Alloc(size_t size, const void* data);
		bool UpdateSubData(size_t offset, size_t size, const void* data);
		void Reset();
		void Realloc();
		void Bind() const;
		size_t GetAlloced() const;
	private:
		size_t alloced;
		size_t size;
		unsigned int buffer;

		bufferUsage_t bufferUsage_;
	};	

	class ElementBufferObject
	{
	public:
		ElementBufferObject();
		~ElementBufferObject();

		ElementBufferObject(ElementBufferObject&) = delete;
		ElementBufferObject(ElementBufferObject&&) noexcept;

		ElementBufferObject& operator=(ElementBufferObject&) = delete;
		ElementBufferObject& operator=(ElementBufferObject&&) noexcept;

		bool Create(size_t size, bufferUsage_t usage, const void* data = nullptr);
		bool Alloc(size_t size, const void* data);
		bool UpdateSubData(size_t offset, size_t size, const void* data);
		void Reset();
		void Realloc();
		void Bind() const;
		size_t GetAlloced() const;
	private:
		size_t alloced;
		size_t size;
		unsigned int buffer;

		bufferUsage_t bufferUsage_;
	};

	class UniformBufferObject
	{
	public:
		UniformBufferObject();
		~UniformBufferObject();

		UniformBufferObject(const UniformBufferObject&) = delete;
		UniformBufferObject(UniformBufferObject&&) noexcept;
		UniformBufferObject& operator=(const UniformBufferObject&) = delete;
		UniformBufferObject& operator=(UniformBufferObject&&) noexcept;

		bool Create(size_t size, bufferUsage_t usage, const void* data = nullptr);
		bool Alloc(size_t size, const void* data);
		bool UpdateSubData(size_t offset, size_t size, const void* data);
		void Reset();
		void Realloc();
		void BindToShader(unsigned progId, unsigned bindigPoint);
		void BindToIndex(const unsigned blockIndex);
		void BindToIndexRange(const unsigned blockIndex, const unsigned offset, const size_t size);
		size_t GetAlloced() const;
	private:
		size_t alloced;
		size_t size;
		unsigned int bindingIndex;
		unsigned int buffer;

		bufferUsage_t bufferUsage_;
	};

}
#endif // !JSE_GRAPHICS_BUFFER_OBJECT_H
