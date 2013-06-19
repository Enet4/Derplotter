/**
 * \file Vector4f.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 * \class derplot::math::Vector4f
 * \brief This class defines a 4-dimensional vector of single precision
 * floating point values, used throughout the library.
 */

#pragma once

#include <initializer_list>
#include <array>

namespace derplot
{

namespace math
{

class Vector4f
{
private:
	float v[4];
public:
	/**
	 * Default Constructor
	 * Builds a blank homogeneous vector (0,0,0,1)
	 */
	constexpr Vector4f(): v{0,0,0,1}{}

	/**
	 * Copy Constructor
	 */
	constexpr Vector4f(const Vector4f& other):
		v{other.v[0],other.v[1],other.v[2],other.v[3]}{}

	/**
	 * Move Constructor
	 */
	constexpr Vector4f(Vector4f&& other):
		v{other.v[0],other.v[1],other.v[2],other.v[3]}{}

	/**
	 * Initializer List constructor
	 *
	 * The constructor will use the first 4 values of the list to produce the vector.
	 * If the size of the list is too short, the remaining unset components will be
	 * automatically set to 1 for the W component and 0 for the X, Y and Z components.
	 * \param list the initializer list
	 */
	Vector4f(const std::initializer_list<float> & list);
	/**
	 * Array pointer constructor
	 *
	 * \b Warning: unsafe. Other constructors should be preferred
	 */
	Vector4f(const float* p_v);

	/**
	 * Builds the vector using the given values of each dimension
	 *
	 * Only the x and y dimensions are required
	 */
	constexpr Vector4f(float x, float y, float z = 0.0f, float w = 1.0f)
	: v{x,y,z,w} {}

	/**
	 * Destructor
	 */
	~Vector4f(void);

	/**
	 * const float * cast operator
	 *
	 * \return a const float pointer to the vector
	 */
	operator const float* (void) const;

	/**
	 * normalizes the vector
	 * \return the vector itself
	 */
	Vector4f& normalize(void);

	/**
	 * clamps each component of the vector to [0,1]
	 * \return the vector itself
	 */
	Vector4f& clamp(void);

	/**
	 * performs a component-wise sum of the vectors, including
	 * the W component!
	 *
	 * \param other
	 * \return the vector itself
	 */
	Vector4f& operator+=(const Vector4f& other);
	/**
	 * performs a component-wise sum of the vectors,
	 * including the W component!
	 * \param other
	 * \return a temporary vector object containing the result
	 */
	const Vector4f& operator+(const Vector4f& other) const;
	/**
	 * performs a component-wise subtraction of the vectors,
	 * including the W component!
	 * \param other
	 * \return the vector itself
	 */
	Vector4f& operator-=(const Vector4f& other);
	/**
	 * performs a component-wise subtraction of the vectors,
	 * including the W component!
	 * \param other
	 * \return a temporary vector object containing the result
	 */
	const Vector4f& operator-(const Vector4f& other) const;
	/**
	 * Multiplies the vector with a scalar
	 * \param fscalar
	 * \return the vector itself
	 */
	Vector4f& operator*=(float fscalar);

	/**
	 * Performs a component-wise multiplication with another vector
	 * \param other
	 * \return the vector itself
	 */
	Vector4f& operator*=(const Vector4f& other);

	/**
	 * Performs the dot product with another vector
	 * \param other
	 * \return the dot product of the two vectors
	 */
	float dot(const Vector4f& other) const;

	/**
	 * Getter for the X component
	 * \return the X component of the vector
	 */
	float& x(void);
	/**
	 * Const getter for the X component
	 * \return the X component of the vector
	 */
	float x(void) const;

	/**
	 * Getter for the Y component
	 * \return the Y component of the vector
	 */
	float& y(void);
	/**
	 * Const getter for the Y component
	 * \return the Y component of the vector
	 */
	float y(void) const;

	/**
	 * Getter for the Z component
	 * \return the Z component of the vector
	 */
	float& z(void);
	/**
	 * Const getter for the Z component
	 * \return the Z component of the vector
	 */
	float z(void) const;

	/**
	 * Getter for the W component
	 * \return the W component of the vector
	 */
	float& w(void);
	/**
	 * Const getter for the W component
	 * \return the W component of the vector
	 */
	float w(void) const;

};

};

};
