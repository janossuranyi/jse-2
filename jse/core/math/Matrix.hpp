#ifndef JSE_CORE_MATH_MATRIX
#define JSE_CORE_MATH_MATRIX

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "core/math/Vector.hpp"

namespace jse::math {

	using mat3 = glm::mat3;
	using mat4 = glm::mat4;

	inline void matrix_decompose(const mat4& mtx, vec3& scale, quat& rotatation, vec3& position)
	{
		vec3 tmp1;
		vec4 tmp2;

		glm::decompose(mtx, scale, rotatation, position, tmp1, tmp2);
	}
	inline mat4 cast_mat4(const float* ptr)
	{
		return glm::make_mat4(ptr);
	}
	inline mat3 cast_mat3(const float* ptr)
	{
		return glm::make_mat3(ptr);
	}
	inline mat4 translate(const mat4& mtx, const vec3& pos)
	{
		return glm::translate(mtx, pos);
	}
	inline mat4 scale(const mat4& mtx, const vec3& vec)
	{
		return glm::scale(mtx, vec);
	}
	inline mat4 lookAt(const vec3& origin, const vec3& target, const vec3& up)
	{
		return glm::lookAt(origin, target, up);
	}
	inline mat4 mat4_cast(const quat& quaternion)
	{
		return glm::mat4_cast(quaternion);
	}
	inline mat4 transpose(const mat4& m)
	{
		return glm::transpose(m);
	}
	inline mat4 inverse(const mat4& m)
	{
		return glm::inverse(m);
	}
	inline mat3 transpose_inverse(const mat4& m)
	{
		return mat3(transpose(inverse(m)));
	}

}
#endif // !JSE_CORE_MATH_MATRIX
