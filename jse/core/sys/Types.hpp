#ifndef JSE_SYS_TYPES_H
#define JSE_SYS_TYPES_H

#include <string>
#include <vector>
#include <cstdint>

namespace jse {

	using String = std::string;
	using string = std::string;
	using byte_vector = std::vector<uint8_t>;
	using int_vector = std::vector<int>;
	using string_vector = std::vector<String>;

}
#endif // !JSE_SYS_TYPES_H
