/** \file RendererOps.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */
#include "RendererOps.h"

#include "MathUtils.h"
#include <math.h>

using namespace derplot;
using namespace math;
using namespace op;

RendererOperation::~RendererOperation()
{
}

int ViewPort::onDispatch( RendererProgram& prg)
{
	prg.viewport = this->viewport;
	return 0;
}

int Ortho::onDispatch( RendererProgram& prg)
{
	if ( this->near >= this->far ||
		 this->top == this->bottom ||
		 this->right == this->left)
		return 1;

		prg.proj = Mat4x4f::IDENTITY;
		math::scale( prg.proj,
					2 / (right - left),
					2 / (top - bottom),
					-2 / (far - near));
		math::translate(prg.proj,
						-(right + left) / (right - left),
						-(top + bottom) / (top - bottom),
						 (near + far) / (far - near));
	return 0;
}

int Perspective::onDispatch( RendererProgram& prg)
{
	if ( near >= far || fovy == 0.f || ratio <= 0.f)
		return false;

	const float ang = math::degrees2radians(this->fovy * 0.5f);
	const float f_len = this->far - this->near;
	const float y = 1.0f / tan(ang);
	const float x = y / this->ratio;
	const float l = -(this->far + this->near) / f_len;
	const float z = -2.0f * this->near * this->far / f_len;

	prg.proj = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, l,-1,
		0, 0, z, 0 };

	return 0;
}

int MatrixSet::onDispatch( RendererProgram& prg)
{
	if (this->type == 1)
		prg.proj = this->mat;
	else
		prg.modelview = this->mat;
	return 0;
}

int MatrixTranslate::onDispatch( RendererProgram& prg)
{
	math::Mat4x4f& mat = (this->matrix == 1) ? prg.proj : prg.modelview;
	math::translate(mat, this->v);
	return 0;
}

int MatrixScale::onDispatch( RendererProgram& prg)
{
	math::Mat4x4f& mat = (this->matrix == 1) ? prg.proj : prg.modelview;
	math::scale(mat, this->v);
	return 0;
}

int MatrixRotate::onDispatch( RendererProgram& prg)
{
	math::Mat4x4f& mat = (this->matrix == 1) ? prg.proj : prg.modelview;
	switch (this->axis)
	{
		case 0:
			math::rotateAroundX(mat, this->ang);
			break;
		case 1:
			math::rotateAroundY(mat, this->ang);
			break;
		case 2:
			math::rotateAroundZ(mat, this->ang);
			break;
		default: ;
	}
	return 0;
}

int Clear::onDispatch( RendererProgram& prg)
{
	return prg.raw_clear();
}

int RawPoint::onDispatch( RendererProgram& prg)
{
	if (type == 1)
		return prg.raw_drawBigPoint(this->point);
	return prg.raw_drawPoint(this->point);
}

int RawLine::onDispatch( RendererProgram& prg)
{
	return prg.raw_drawLine(this->point1, this->point2);
}

int Line::onDispatch( RendererProgram& prg)
{
	return prg.drawLine(this->point1, this->point2);
}

int Point::onDispatch( RendererProgram& prg)
{
	if (type == 1)
		return prg.drawBigPoint(this->point);
	return prg.drawPoint(this->point);
}

int ClearColor::onDispatch( RendererProgram& prg)
{
	prg.clear_color = this->color;
	return 0;
}

int FrontColor::onDispatch( RendererProgram& prg)
{
	prg.front_color = this->color;
	return 0;
}
