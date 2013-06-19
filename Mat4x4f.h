/**
 * \file Mat4x4f.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 * \class derplot::math::Mat4x4f
 * \brief This class defines a 4x4 bidimensional matrix of single precision
 * floating point values, used throughout the library.
 */
#pragma once

#include <initializer_list>
#include <array>
#include "Vector4f.h"

namespace derplot
{

namespace math
{

class Mat4x4f
{
private:
	std::array<float, 4*4> m;
public:

	/**
	 * Builds a blank matrix (with zeros)
	 */
	Mat4x4f(void);

	/**
	 * Constructor for copying a matrix
	 */
	Mat4x4f(const Mat4x4f& other);

	/**
	 * Standard move constructor
	 * \param other the other object to move from
	 */
	Mat4x4f(Mat4x4f&& other);

	/**
	 * Copy assignment operator
	 * \param other the object to copy from
	 * \return reference to this
	 */
	Mat4x4f& operator=(const Mat4x4f& other);

	/**
	 * Move assignment operator
	 * \param other the object to move from
	 * \return reference to this
	 */
	Mat4x4f& operator=(Mat4x4f&& other);

	/**
	 * Array pointer constructor
	 *
	 * Builds the matrix by retrieving each element from the array,
	 * in standard OpenGL order (column elements are contiguous)
	 *
	 * \b Warning: unsafe. Other constructors should be preferred
	 */
	Mat4x4f(const float* p_m);

	/**
	 * Initializer list constructor
	 *
	 * Builds the matrix using the given initializer \b list (C++11 feature),
	 * in standard OpenGL order (columns first).
	 *
	 * If the list isn't large enough to set all 16 elements of the vector,
	 * the remaining elements are, by default, set to \c 0 .
	 */
	Mat4x4f(const std::initializer_list<float> & list);

	/**
	 * const float * cast operator
	 *
	 * \return a pointer to the array holding the matrix elements
	 */
	operator const float* (void) const;

	/**
	 * Applies the sum of this matrix with the \b other matrix
	 */
	Mat4x4f& operator+= (const Mat4x4f& other);

	/**
	 * \return the sum of two matrices
	 */
	const Mat4x4f& operator+ (const Mat4x4f& other) const;

	/**
	 * Applies the subtraction of this matrix with the \b other matrix
	 * \return the matrix itself
	 */
	Mat4x4f& operator-= (const Mat4x4f& other);

	/**
	 * \return the result of subtracting two matrices
	 */
	const Mat4x4f& operator- (const Mat4x4f& other) const;

	/**
	 * Applies the product of this matrix with the \b other matrix
	 * \return the matrix itself
	 */
	Mat4x4f& operator*= (const Mat4x4f& other);

	/**
	 * \return the product of two matrices
	 */
	const Mat4x4f& operator* (const Mat4x4f& other) const;

	/**
	 * Applies the product of this matrix with a scalar value
	 * \return the matrix itself
	 */
	Mat4x4f& operator*= (float fscalar);

	/**
	 * Gets the value at the given index. \c 0 is returned when out of bounds.
	 * \param the index of the matrix's element. 0 < index < 16
	 */
	float get(unsigned int index) const;

	/**
	 * Gets the value at row \b row and column \b col.
	 * \c 0 is returned when out of bounds.
	 * \param the row of the matrix's element. 0 < row < 4
	 * \param the column of the matrix's element. 0 < col < 4
	 */
	float get(unsigned int row, unsigned int col) const;

	/**
	 * Takes the values of the last column of the matrix and writes them
	 * to the given vector in order.
	 * \param vector the vector to write to
	 * \return the vector itself
	 */
	Vector4f& takeVector(Vector4f& vector) const;

	/**
	 * Identity matrix
	 */
	static const Mat4x4f IDENTITY;
};

};

};
