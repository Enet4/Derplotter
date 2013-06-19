/** \file Mat4x4f.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */

#include "Mat4x4f.h"

using namespace derplot::math;

const Mat4x4f Mat4x4f::IDENTITY =
{	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 };

Mat4x4f::Mat4x4f(void)
{
	this->m.fill(0.0f);
}

Mat4x4f::Mat4x4f(const Mat4x4f& other)
:	m(other.m)
{}

Mat4x4f::Mat4x4f(Mat4x4f&& other)
:	m(other.m)
{}

Mat4x4f& Mat4x4f::operator=(const Mat4x4f& other)
{ this->m = other.m; return *this; }

Mat4x4f& Mat4x4f::operator=(Mat4x4f&& other)
{ this->m = other.m; return *this; }

Mat4x4f::Mat4x4f(const float* p_m)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] = p_m[i];
}

Mat4x4f::Mat4x4f(const std::initializer_list<float> & list)
{
	int i;
	auto it = begin(list);
	for (i = 0 ; it != end(list) && i < 4*4 ; it++, i++ )
		m[i] = *it;
	for ( ; i < 4*4 ; i++)
		m[i] = 0.0f;
}

Mat4x4f::operator const float* (void) const
{
	return this->m.data();
}

Mat4x4f& Mat4x4f::operator+= (const Mat4x4f& other)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] += other.m[i];
	return *this;
}

const Mat4x4f& Mat4x4f::operator+ (const Mat4x4f& other) const
{
	Mat4x4f out(*this);
	return out+=other;
}

Mat4x4f& Mat4x4f::operator-= (const Mat4x4f& other)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] -= other.m[i];
	return *this;
}

const Mat4x4f& Mat4x4f::operator- (const Mat4x4f& other) const
{
	Mat4x4f out(*this);
	return out-=other;
}

Mat4x4f& Mat4x4f::operator*= (const Mat4x4f& other)
{
	unsigned int r, c;

	Mat4x4f m1(*this);

	for (r = 0; r < 4; r++)
		for (c = 0; c < 4; c++)
			this->m[c * 4 + r] =
				(m1.m[r +  0] * other.m[c * 4 + 0]) +
				(m1.m[r +  4] * other.m[c * 4 + 1]) +
				(m1.m[r +  8] * other.m[c * 4 + 2]) +
				(m1.m[r + 12] * other.m[c * 4 + 3]);

	return *this;
}

const Mat4x4f& Mat4x4f::operator* (const Mat4x4f& other) const
{
	Mat4x4f out(*this);
	return out *= other;
}

Mat4x4f& Mat4x4f::operator*= (float fscalar)
{
	for (int i = 0 ; i < 4*4 ; i++)
		this->m[i] *= fscalar;
	return *this;
}

float Mat4x4f::get(unsigned int index) const
{
	if (index >= 4*4) return 0.0f;
	return this->m[index];
}

float Mat4x4f::get(unsigned int row, unsigned int col) const
{
	if (row >= 4 || col >= 4) return 0.0f;
	return this->m[row + (col << 2)];
}

Vector4f& Mat4x4f::takeVector(Vector4f& vector) const
{
	vector.x() = m[12]; vector.y() = m[13];
	vector.z() = m[14]; vector.w() = m[15];
	return vector;
}
