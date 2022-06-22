#ifndef JSE_MATH_PLANE_H
#define JSE_MATH_PLANE_H

#include "core/math/Vector.hpp"

namespace jse {
	struct plane_t
	{
		vec3 N;
		vec3 p0;
		float D;

		plane_t(const vec3& normal_, float distance_) : N(normal_), D(distance_), p0(normal_ * distance_) {}
		plane_t(float x_, float y_, float z_, float distance_) : N(vec3(x_,y_,z_)), D(distance_)
		{
			p0 = N * D;
		}
		plane_t(const vec3& p_)
		{
			p0 = p_;
			D = length(p_);
			N = p_ / D;
		}
		plane_t(const vec3& p1, const vec3& p2, const vec3& p3)
		{
			vec3 p12	= p2 - p1;
			vec3 p13	= p3 - p1;
			vec3 n		= cross(p12, p13);

			p0 = n;
			D = length(n);
			N = normalize(n);
		}

		const vec3& Normal() const { return N; }
		const float Distance() const { return D; }
		float PointDistance(const vec3& V) { return dot(V, N) - D; }
		bool RayIntersect(const vec3& l0, const vec3& l, vec3& intersect, float& t);
		bool LineIntersect(const vec3& p1, const vec3& p2, vec3& intersect, float& t);
	};

	inline bool plane_t::LineIntersect(const vec3& p1, const vec3& p2, vec3& intersect, float& t)
	{
		float d1 = PointDistance(p1);
		float d2 = PointDistance(p2);
		
		if (d1 > 0 && d2 > 0)
		{
			t = 1.0f;
			return false;
		}
			
		if (d1 < 0 && d2 < 0)
		{
			t = -1.0f;
			return false;
		}

		return RayIntersect(p1, normalize(p2 - p1), intersect, t);
	}

	inline bool plane_t::RayIntersect(const vec3& l0, const vec3& l, vec3& intersect, float& t)
	{
		float denom	= dot(l, N);
		float p0l0	= dot(p0 - l0, N);
		
		const float EPSILON = 1e-6;

		if (fabs(denom) < EPSILON)
		{
			// line paralell to the plane
			if (fabs(p0l0) < EPSILON)
			{
				t = 0.0f;
				return true;
			}
			return false;
		}

		t = p0l0 / denom;
		intersect = l0 + l * t;

		return true;

	}
}
#endif // !JSE_MATH_PLANE_H
