#ifndef JSE_TYPES_H
#define JSE_TYPES_H

#include <string>
#include <vector>
#include <cstdint>

namespace jse {

	const float EPSILON = 1e-6f;

	using string = std::string;

	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;

	using ByteVec = std::vector<u8>;
	using IntVec = std::vector<i32>;
	using StrVec = std::vector<std::string>;

}
#endif // !JSE_SYS_TYPES_H
