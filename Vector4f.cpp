/** \file Vector4f.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */
#include "Vector4f.h"

using namespace derplot;
using namespace math;

Vector4f::Vector4f(const std::initializer_list<float> & list)
{
	int i;
	auto it = begin(list);
	for (i = 0 ; it != end(list) && i < 4 ; it++, i++ )
		v[i] = *it;
	for ( ; i < 3 ; i++)
		v[i] = 0.0f;
	if (i == 3) v[3] = 1.0f; //default w coordinate
}

Vector4f::Vector4f(const float* p_v)
: v{p_v[0], p_v[1], p_v[2], p_v[3]}
{
}

Vector4f::~Vector4f(void)
{
}

Vector4f::operator const float* (void) const
{
	return this->v;
}

Vector4f& Vector4f::operator*=(const Vector4f& other)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] *= other.v[i];
	return *this;
}

float Vector4f::dot(const Vector4f& other) const
{
	return
		this->x() * other.x() + this->y() * other.y() +
		this->z() * other.z() + this->w() * other.w();
}

Vector4f& Vector4f::operator+=(const Vector4f& other)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] += other.v[i];
	return *this;
}

const Vector4f& Vector4f::operator+(const Vector4f& other) const
{
	Vector4f vec(*this);
	return vec += other;
}

Vector4f& Vector4f::operator-=(const Vector4f& other)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] -= other.v[i];
	return *this;
}

const Vector4f& Vector4f::operator-(const Vector4f& other) const
{
	Vector4f vec(*this);
	return vec -= other;
}

Vector4f& Vector4f::operator*=(float fscalar)
{
	for (int i = 0 ; i < 4 ; i++)
		this->v[i] *= fscalar;
	return *this;
}

Vector4f& Vector4f::normalize(void)
{
	float w = this->w();
	this->v[0] /= w;
	this->v[1] /= w;
	this->v[2] /= w;
	this->v[3] = 1.f;
	return *this;
}

Vector4f& Vector4f::clamp(void)
{
	for (int i = 0 ; i < 4 ; i++)
	{
		if (v[i] < 0) v[i] = 0;
		if (v[i] > 1) v[i] = 1;
	}
	return *this;
}

float& Vector4f::x(void) { return this->v[0]; }
float Vector4f::x(void) const { return this->v[0]; }

float& Vector4f::y(void) { return this->v[1]; }
float Vector4f::y(void) const { return this->v[1]; }

float& Vector4f::z(void) { return this->v[2]; }
float Vector4f::z(void) const { return this->v[2]; }

float& Vector4f::w(void) { return this->v[3]; }
float Vector4f::w(void) const { return this->v[3]; }


