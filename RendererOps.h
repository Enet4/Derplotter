/** \file RendererOps.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */
#pragma once

#include "RendererProgram.h"
#include "Mat4x4f.h"
#include "Vector4f.h"
#include "Region2i.h"

/**
 * \namespace derplot::op
 * \brief contains all renderer operation classes
 */
namespace derplot
{
	namespace op
	{
		/**
		* \brief abstract class of all renderer operations
		*/
		class RendererOperation
		{
			public:
			virtual ~RendererOperation();
			/**
			 * \return 0 on success, -1 on terminator error
			 */
			virtual int onDispatch( RendererProgram& prg) = 0;
		};

		/**
		 * \brief Operation for terminating the rendererer
		 */
		class Terminate : public RendererOperation
		{
			public:
			int onDispatch( RendererProgram& prg)
			{ return -1; }
		};

		/**
		 * \brief Operation for defining the Viewport
		 */
		class ViewPort : public RendererOperation
		{
			math::Region2i viewport;
			public:
			ViewPort(math::Region2i viewport)
				:	viewport(viewport){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for clearing the display
		 */
		class Clear : public RendererOperation
		{
			public:
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for 'raw' drawing a point
		 */
		class RawPoint : public RendererOperation
		{
			std::pair<int,int> point;
			int type;
			public:
			RawPoint(std::pair<int,int> point, int type)
				:	point(point), type(type){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for 'raw' drawing a line
		 */
		class RawLine : public RendererOperation
		{
			std::pair<int,int> point1, point2;
			public:
			RawLine(std::pair<int,int> point1, std::pair<int,int> point2)
				:  point1(point1), point2(point2){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for drawing a 3D point
		 */
		class Point : public RendererOperation
		{
			math::Vector4f point;
			int type;
			public:
			Point(math::Vector4f point, int type)
				:	point(point), type(type){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for drawing a 3D line
		 */
		class Line : public RendererOperation
		{
			math::Vector4f point1, point2;
			public:
			Line(const math::Vector4f& point1, const math::Vector4f& point2)
				:  point1(point1), point2(point2){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for defining a matrix
		 */
		class MatrixSet : public RendererOperation
		{
			math::Mat4x4f mat;
			int type;
			public:
			MatrixSet(const math::Mat4x4f& mat, int matrix)
				:	mat(mat), type(matrix){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for defining an orthographic projection
		 */
		class Ortho : public RendererOperation
		{
			float left, right, top, bottom, near, far;
			public:
			Ortho(	float left, float right, float top,
					float bottom, float near, float far)
				:	left(left), right(right), top(top),
					bottom(bottom), near(near), far(far) {}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for defining a perspective projection
		 */
		class Perspective : public RendererOperation
		{
			float fovy, near, far, ratio;
			public:
			Perspective( float fovy, float near, float far, float aspect_ratio)
				:	fovy(fovy), near(near), far(far), ratio(aspect_ratio) {}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for performing a translation transformation on a matrix
		 */
		class MatrixTranslate : public RendererOperation
		{
			math::Vector4f v;
			int matrix;
			public:
			MatrixTranslate(const math::Vector4f& v, int matrix = 0)
				:	v(v), matrix(matrix){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for performing a rotation transformation on a matrix
		 */
		class MatrixRotate : public RendererOperation
		{
			float ang;
			int axis;
			int matrix;
			public:
			MatrixRotate(float angle, int axis, int matrix = 0)
				:	ang(angle), axis(axis), matrix(matrix){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for performing a scale transformation on a matrix
		 */
		class MatrixScale : public RendererOperation
		{
			math::Vector4f v; int matrix;
			public:
			MatrixScale(const math::Vector4f& v, int matrix = 0)
				:	v(v), matrix(matrix){}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for defining the clear color
		 */
		class ClearColor : public RendererOperation
		{
			unsigned int color;
			public:
			ClearColor(unsigned int color)
				:	color(color) {}
			int onDispatch( RendererProgram& prg);
		};

		/**
		 * \brief Operation for defining the front color
		 */
		class FrontColor : public RendererOperation
		{
			unsigned int color;
			public:
			FrontColor(unsigned int color)
				:	color(color) {}
			int onDispatch( RendererProgram& prg);
		};

	};
};
