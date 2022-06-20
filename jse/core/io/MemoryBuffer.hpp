#ifndef JSE_IO_MEMORYBUFFER_H
#define JSE_IO_MEMORYBUFFER_H

#include <memory>
#include <cstdint>
namespace jse::core::io {

    template<class T>
	class MemoryBuffer
	{
	public:
		MemoryBuffer(const MemoryBuffer& other);
		MemoryBuffer(MemoryBuffer&& other) noexcept;
		MemoryBuffer() : data(nullptr), size(0), stride(0), offset(0) {}
		MemoryBuffer(size_t size_, const void* data_ = nullptr, size_t stride_ = 0)
		{
			size = size_;
			data = new char[size];
            stride = stride_ > 0 ? stride_ : sizeof(T);
			offset = 0;

			if (data_)
			{
				memcpy(data, data_, size);
			}
		}
		~MemoryBuffer()
		{
			if (data)
			{
				delete[] data;
			}
		}
		MemoryBuffer& operator=(const MemoryBuffer& other);
		MemoryBuffer& operator=(MemoryBuffer&& other) noexcept;
		T& operator[](size_t index);
		bool IsAllocated() const { return size > 0; }
		size_t GetAllocated() const { return size; }
        size_t GetStride() const { return stride; }
		size_t GetSize() const { return size / stride; }
		void Reset() { offset = 0; }
		unsigned char* BytePtr() { return static_cast<unsigned char*>(data); }
		bool HasNext() const { return offset + sizeof(T) <= size; }
		T* NextPtr();
	private:
		char* data;
		size_t size;
        size_t stride;
		size_t offset;
	};


	template<class T>
	MemoryBuffer<T>& MemoryBuffer<T>::operator=(MemoryBuffer<T>&& other) noexcept
	{
		data = other.data;
		size = other.size;
		offset = other.offset;
		stride = other.stride;

		other.data = nullptr;
		other.size = 0;
		other.offset = 0;
		other.stride = 0;

		return *this;
	}

	template<class T>
	T& MemoryBuffer<T>::operator[](size_t index)
	{
		return *reinterpret_cast<T*>(data + index * stride);
	}

	template<class T>
	T* MemoryBuffer<T>::NextPtr()
	{
		if (!HasNext())
			return nullptr;

		T* ptr = static_cast<T*>(data + offset);

		offset += stride;

		return ptr;
	}

	template<class T>
	MemoryBuffer<T>& MemoryBuffer<T>::operator=(const MemoryBuffer<T>& other)
	{
		data = new char[other.size];
		size = other.size;
		stride = other.stride;
		offset = other.offset;

		std::memcpy(data, other.data, size);

		return *this;
	}
	template<class T>
	MemoryBuffer<T>::MemoryBuffer(const MemoryBuffer<T>& other)
	{
		// copy ctor
		data = new char[other.size];
		size = other.size;
		stride = other.stride;
		offset = other.offset;

		std::memcpy(data, other.data, size);
	}
	template<class T>
	MemoryBuffer<T>::MemoryBuffer(MemoryBuffer<T>&& other) noexcept
	{
		// move ctor
		data = other.data;
		size = other.size;
		stride = other.stride;
		offset = other.offset;

		other.data = nullptr;
		other.size = 0;
		other.offset = 0;
		other.stride = 0;
	}

}
#endif // !JSE_IO_MEMORYBUFFER_H
