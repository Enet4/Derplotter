/** \file MathUtils.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */
#include "MathUtils.h"

#include <math.h>

using namespace derplot;
using namespace math;

Vector4f& math::multiply(Vector4f& vec, const Mat4x4f& mat)
{
	float t[4];
	for (int row = 0; row < 4; row++)
	{
	    t[row] = mat.get(row, 0) * vec.x() +
				 mat.get(row, 1) * vec.y() +
				 mat.get(row, 2) * vec.z() +
				 mat.get(row, 3) * vec.w();
	}
	vec = Vector4f(t[0], t[1], t[2], t[3]);
	return vec;
}

Mat4x4f& math::translate(Mat4x4f& mat, const Vector4f& v)
{
	Mat4x4f translate = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			v.x(), v.y(), v.z(), v.w()
		};
	return mat *= translate;
}

Mat4x4f& math::translate(Mat4x4f& mat, float x, float y, float z, float w)
{
	Mat4x4f translate = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, w
		};
	return mat *= translate;
}

Mat4x4f& math::scale(Mat4x4f& mat, float x, float y, float z, float w)
{
	Mat4x4f scale = {
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, w
		};
	return mat *= scale;
}

Mat4x4f& math::scale(Mat4x4f& mat, const Vector4f& v)
{
	return scale(mat, v[0], v[1], v[2], v[3]);
}

Mat4x4f& math::rotateAroundX(Mat4x4f& mat, float ang)
{
	float sine = (float)sin(ang);
	float cosine = (float)cos(ang);
	Mat4x4f rotation = {
		1,      0,      0,    0,
		0, cosine,   sine,    0,
		0,  -sine, cosine,    0,
		0,      0,      0,    1
		};

	return mat *= rotation;
}

Mat4x4f& math::rotateAroundY(Mat4x4f& mat, float ang)
{
	float sine = (float)sin(ang);
	float cosine = (float)cos(ang);
	Mat4x4f rotation = {
		cosine,      0,  -sine,    0,
			 0,      1,      0,    0,
		  sine,      0, cosine,    0,
		     0,      0,      0,    1
		};

	return mat *= rotation;
}

Mat4x4f& math::rotateAroundZ(Mat4x4f& mat, float ang)
{
	float sine = (float)sin(ang);
	float cosine = (float)cos(ang);
	Mat4x4f rotation = {
		cosine,   sine,     0,    0,
		 -sine, cosine,     0,    0,
		     0,      0,     1,    0,
		     0,      0,     0,    1
		};

	return mat *= rotation;
}

Mat4x4f& math::rotate(Mat4x4f& mat, const Vector4f& ang)
{
	return 	rotateAroundZ(
				rotateAroundY(
					rotateAroundX( mat, ang.x()),
				ang.y()),
			ang.z());
}

Mat4x4f& math::rotate(Mat4x4f& mat, float pitch, float yaw, float roll)
{
	return 	rotateAroundZ(
				rotateAroundY(
					rotateAroundX( mat, pitch),
				yaw),
			roll);
}

std::ostream& math::operator<< (std::ostream& stream, const Mat4x4f& mat)
{
	for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 0 ; j < 4 ; j++)
		{
			stream << mat.get(i,j);
			if (j < 3) stream << " ";
		}
		stream << std::endl;
	}
	return stream;
}

std::ostream& math::operator<< (std::ostream& stream, const Vector4f& vec)
{
	return stream << "("
			<< vec.x() << ", " << vec.y() << ", "
			<< vec.z() << ", " << vec.w() << ")";
}
