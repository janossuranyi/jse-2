#ifndef JSE_GRAPHICS_DRAWVERT_H
#define JSE_GRAPHICS_DRAWVERT_H

#include "core/math/Vector.hpp"
#define DRAWVERT_POSITION_INDEX (0)
#define DRAWVERT_TEXCOORD_INDEX (1)
#define DRAWVERT_NORMAL_INDEX (2)
#define DRAWVERT_TANGENT_INDEX (3)
#define DRAWVERT_COLOR_INDEX (4)
#define DRAWVERT_COLOR2_INDEX (5)

#define DRAWVERT_POSITION_OFFSET (0*4)
#define DRAWVERT_TEXCOORD_OFFSET (3*4)
#define DRAWVERT_NORMAL_OFFSET (4*4)
#define DRAWVERT_TANGENT_OFFSET (5*4)
#define DRAWVERT_COLOR_OFFSET (6*4)
#define DRAWVERT_COLOR2_OFFSET (7*4)

#define SHADOWVERT_POSITION_OFFSET (0*4)
#define SHADOWVERT_NORMAL_OFFSET (4*4)

// The hardware converts a byte to a float by division with 255 and in the
// vertex programs we convert the floating-point value in the range [0, 1]
// to the range [-1, 1] by multiplying with 2 and subtracting 1.
#define VERTEX_BYTE_TO_FLOAT( x )		( (x) * ( 2.0f / 255.0f ) - 1.0f )
#define VERTEX_FLOAT_TO_BYTE( x )		static_cast<uint8_t>( ( (x) + 1.0f ) * ( 255.0f / 2.0f ) + 0.5f )

// The hardware converts a byte to a float by division with 255 and in the
// fragment programs we convert the floating-point value in the range [0, 1]
// to the range [-1, 1] by multiplying with 2 and subtracting 1.
// This is the conventional OpenGL mapping which specifies an exact
// representation for -1 and +1 but not 0. The DirectX 10 mapping is
// in the comments which specifies a non-linear mapping with an exact
// representation of -1, 0 and +1 but -1 is represented twice.
#define NORMALMAP_BYTE_TO_FLOAT( x )	VERTEX_BYTE_TO_FLOAT( x )	//( (x) - 128.0f ) * ( 1.0f / 127.0f )
#define NORMALMAP_FLOAT_TO_BYTE( x )	VERTEX_FLOAT_TO_BYTE( x )	//byte( 128.0f + 127.0f * (x) + 0.5f )

// GPU half-float bit patterns
#define HF_MANTISSA(x)	(x&1023)
#define HF_EXP(x)		((x&32767)>>10)
#define HF_SIGN(x)		((x&32768)?-1:1)


namespace jse {

	enum VertexLayout
	{
		DRAW_LAYOUT,
		SHADOW_LAYOUT
	};


	/*
	================================================
	halfFloat_t
	================================================
	*/
	typedef unsigned short halfFloat_t;


	/*
	========================
	F16toF32
	========================
	*/
	inline float F16toF32(halfFloat_t x)
	{
		int e = HF_EXP(x);
		int m = HF_MANTISSA(x);
		int s = HF_SIGN(x);

		if (0 < e && e < 31)
		{
			return s * powf(2.0f, (e - 15.0f)) * (1 + m / 1024.0f);
		}
		else if (m == 0)
		{
			return s * 0.0f;
		}
		return s * powf(2.0f, -14.0f) * (m / 1024.0f);
	}

	/*
	========================
	F32toF16
	========================
	*/
	inline halfFloat_t F32toF16(float a)
	{
		unsigned int f = *(unsigned*)(&a);
		unsigned int signbit = (f & 0x80000000) >> 16;
		int exponent = ((f & 0x7F800000) >> 23) - 112;
		unsigned int mantissa = (f & 0x007FFFFF);

		if (exponent <= 0)
		{
			return 0;
		}
		if (exponent > 30)
		{
			return (halfFloat_t)(signbit | 0x7BFF);
		}

		return (halfFloat_t)(signbit | (exponent << 10) | (mantissa >> 13));
	}

	class DrawVert
	{
	public:
		vec3 position;	// 12
		halfFloat_t texcoord[2];	//  4
		uint8_t normal[4];			//  4
		uint8_t tangent[4];			//  4
		uint8_t color[4];			//  4
		uint8_t color2[4];			//  4

		DrawVert();
		DrawVert(const vec3& position);
		void Clear();
		void SetTextCoord(float s, float t);
		void SetTextCoord(const vec2& v);
		void SetPosition(float x, float y, float z);
		void SetPosition(const vec3& v);
		void SetNormal(float x, float y, float z);
		void SetNormal(const vec3& v);
		void SetTangent(float x, float y, float z, float w);
		void SetTangent(const vec4& v);
		void SetColor(float r, float g, float b, float a);
		void SetColor(const vec4& v);
		void SetColor2(float r, float g, float b, float a);
		void SetColor2(const vec4& v);
		const vec3& GetPosition() const;
		const vec2 GetTexCoords() const;
		const vec3 GetNormal() const;
		const vec4 GetTangent() const;
		const vec4 GetColor() const;
		const vec4 GetColor2() const;

	}; // 32

	constexpr size_t DRAW_VERT_SIZE = sizeof(DrawVert);

	static const int VERTEX_ATTRIB_POSITION_INDEX = 0;
	static const int VERTEX_ATTRIB_TEXCOORD_INDEX = 1;
	static const int VERTEX_ATTRIB_NORMAL_INDEX = 2;
	static const int VERTEX_ATTRIB_TANGENT_INDEX = 3;
	static const int VERTEX_ATTRIB_COLOR_INDEX = 4;

	inline DrawVert::DrawVert()
	{
		Clear();
	}
	inline DrawVert::DrawVert(const vec3& position) : DrawVert()
	{
		this->position = position;
	}
	inline void DrawVert::Clear()
	{
		memset(this, 0, sizeof(DrawVert));
	}
	inline void DrawVert::SetTextCoord(const vec2& v)
	{
		SetTextCoord(v.s, v.t);
	}
	inline void DrawVert::SetTextCoord(float s, float t)
	{
		texcoord[0] = F32toF16(s);
		texcoord[1] = F32toF16(t);
	}
	inline void DrawVert::SetNormal(float x, float y, float z)
	{
		normal[0] = VERTEX_FLOAT_TO_BYTE(x);
		normal[1] = VERTEX_FLOAT_TO_BYTE(y);
		normal[2] = VERTEX_FLOAT_TO_BYTE(z);
		normal[3] = VERTEX_FLOAT_TO_BYTE(0);
	}
	inline void DrawVert::SetNormal(const vec3& v)
	{
		SetNormal(v.x, v.y, v.z);
	}
	inline void DrawVert::SetPosition(float x, float y, float z)
	{
		position[0] = (x);
		position[1] = (y);
		position[2] = (z);
	}
	inline void DrawVert::SetPosition(const vec3& v)
	{
		position = v;
	}
	inline void DrawVert::SetTangent(float x, float y, float z, float w)
	{
		tangent[0] = VERTEX_FLOAT_TO_BYTE(x);
		tangent[1] = VERTEX_FLOAT_TO_BYTE(y);
		tangent[2] = VERTEX_FLOAT_TO_BYTE(z);
		tangent[3] = VERTEX_FLOAT_TO_BYTE(w);
	}
	inline void DrawVert::SetTangent(const vec4& v)
	{
		SetTangent(v.x, v.y, v.z, v.w);
	}
	inline void DrawVert::SetColor(float r, float g, float b, float a)
	{
		color[0] = static_cast<uint8_t>(255.0f * r);
		color[1] = static_cast<uint8_t>(255.0f * g);
		color[2] = static_cast<uint8_t>(255.0f * b);
		color[3] = static_cast<uint8_t>(255.0f * a);
	}
	inline void DrawVert::SetColor(const vec4& v)
	{
		SetColor(v.r, v.g, v.b, v.a);
	}
	inline void DrawVert::SetColor2(const vec4& v)
	{
		SetColor2(v.r, v.g, v.b, v.a);
	}
	inline void DrawVert::SetColor2(float r, float g, float b, float a)
	{
		color2[0] = static_cast<uint8_t>(255.0f * r);
		color2[1] = static_cast<uint8_t>(255.0f * g);
		color2[2] = static_cast<uint8_t>(255.0f * b);
		color2[3] = static_cast<uint8_t>(255.0f * a);
	}
	inline const vec3& DrawVert::GetPosition() const
	{
		return position;
	}
	inline const vec2 DrawVert::GetTexCoords() const
	{
		return vec2(F16toF32(texcoord[0]), F16toF32(texcoord[1]));
	}
	inline const vec3 DrawVert::GetNormal() const
	{
		return vec3(
			VERTEX_BYTE_TO_FLOAT(normal[0]),
			VERTEX_BYTE_TO_FLOAT(normal[1]),
			VERTEX_BYTE_TO_FLOAT(normal[2])
		);
	}
	inline const vec4 DrawVert::GetTangent() const
	{
		return vec4(
			VERTEX_BYTE_TO_FLOAT(tangent[0]),
			VERTEX_BYTE_TO_FLOAT(tangent[1]),
			VERTEX_BYTE_TO_FLOAT(tangent[2]),
			VERTEX_BYTE_TO_FLOAT(tangent[3])
		);
	}
	inline const vec4 DrawVert::GetColor() const
	{
		const float inv = 1.0f / 255.0f;
		return vec4(
			color[0] * inv,
			color[1] * inv,
			color[2] * inv,
			color[3] * inv
		);
	}
	inline const vec4 DrawVert::GetColor2() const
	{
		const float inv = 1.0f / 255.0f;
		return vec4(
			color2[0] * inv,
			color2[1] * inv,
			color2[2] * inv,
			color2[3] * inv
		);
	}

}

#endif // !JSE_GRAPHICS_DRAWVERT_H
