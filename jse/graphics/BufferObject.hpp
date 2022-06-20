#ifndef JSE_GRAPHICS_BUFFER_OBJECT_H
#define JSE_GRAPHICS_BUFFER_OBJECT_H

namespace jse::graphics {

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
		bool Create(size_t size, bufferUsage_t usage, const void* data = nullptr);
		bool Alloc(size_t size, const void* data);
		bool UpdateSubData(size_t offset, size_t size, const void* data);
		void Reset();
		void Realloc();
		void Bind();
		size_t GetAlloced() const;
	private:
		size_t alloced;
		size_t size;
		unsigned int buffer;

		bufferUsage_t bufferUsage_;
	};	

}
#endif // !JSE_GRAPHICS_BUFFER_OBJECT_H
