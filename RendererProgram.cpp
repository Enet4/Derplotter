/** \file RendererProgram.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */
#include "RendererProgram.h"

#include "MathUtils.h"

using namespace derplot;
using namespace math;

RendererProgram::RendererProgram(void)
:	p_buffer(nullptr)
{}

RendererProgram::RendererProgram(DisplayBuffer& buffer)
:	p_buffer(&buffer)
,	modelview(Mat4x4f::IDENTITY)
,	proj(Mat4x4f::IDENTITY)
,	viewport(0, buffer.getWidth(), 0, buffer.getHeight())
,	front_color(DEFAULT_FRONT_COLOR)
,	clear_color(DEFAULT_CLEAR_COLOR)
{
}

RendererProgram::~RendererProgram()
{
}

bool RendererProgram::operator!(void) const
{
	return !p_buffer;
}

int RendererProgram::raw_clear(void)
{
	if (this->p_buffer->clear(this->clear_color))
		return 0;
	return 1;
}

int RendererProgram::raw_drawPoint(const std::pair<int,int>& p)
{
	const int& x = p.first, &y = p.second;
	if (x < 0 || y < 0 )
		return 1;

	return p_buffer->plot(x, y, this->front_color) ? 0 : 1; // plot it!
}

int RendererProgram::raw_drawBigPoint(const std::pair<int,int>& p)
{
	const int& x = p.first, &y = p.second;
	if (x < 0 || y < 0 )
		return 1;

	if (!p_buffer->plot(x, y, this->front_color)) return 1;

	p_buffer->plot(x-1, y, this->front_color);
	p_buffer->plot(x+1, y, this->front_color);
	p_buffer->plot(x, y-1, this->front_color);
	p_buffer->plot(x, y+1, this->front_color);
	return 0;
}

int RendererProgram::raw_drawLine(std::pair<int,int>& p1, std::pair<int,int>& p2)
{
	if (p1 == p2) return raw_drawPoint(p1);

	float m, b;
	const int dx = p2.first - p1.first;
	const int dy = p2.second - p1.second;
	const int abs_dx = (dx >= 0) ? dx : -dx;
	const int abs_dy = (dy >= 0) ? dy : -dy;
	if (abs_dx > abs_dy) // X range greater than Y range
	{
		if (p1.first > p2.first)
			p1.swap(p2);

		// m = dy / dx ; y = x*m + b <=> b = y1-x1*m;
		m = (float)dy / (float)dx;
		b = p1.second - p1.first*m;
		int x = (p1.first < 0) ? 0 : p1.first;
		const int xmax = (p2.first > p_buffer->getWidth())
			? p_buffer->getWidth()-1 : p2.first;
		for (; x <= xmax ; x++)
		{
			int y = (int)(x*m + b);
			p_buffer->plot(x, y, this->front_color);
		}
	}
	else // Y range greater than X range
	{
		if (p1.second > p2.second)
			p1.swap(p2);

		// m = dx / dy ; x = y*m + b <=> b = x1-y1*m;
		m = (float)dx / (float) dy;
		b = p1.first - p1.second*m;
		int y = (p1.second < 0) ? 0 : p1.second;
		const int ymax = (p2.second > p_buffer->getHeight())
			? p_buffer->getHeight()-1 : p2.second;
		for ( ; y <= ymax ; y++)
		{
			int x = (int)(y*m + b);
			p_buffer->plot(x, y, this->front_color);
		}
	}

	return 0;
}

int RendererProgram::drawPoint(const Vector4f& point)
{
	Vector4f p = point;
	std::pair<int,int> rp(-1,-1);
	int r = this->transformPoint(p, rp);
	if (r != 0) return 0;
	this->raw_drawPoint(rp);
	return 0;
}

int RendererProgram::drawBigPoint(const Vector4f& point)
{
	Vector4f p = point;
	std::pair<int,int> rp(-1,-1);
	int r = this->transformPoint(p, rp);
	if (r != 0) return 0;
	this->raw_drawBigPoint(rp);
	return 0;
}

int RendererProgram::drawLine(const Vector4f& point1, const Vector4f& point2)
{
	std::pair<int,int> rp1(-1,-1), rp2(-1,-1);
	// transform both points
	Vector4f p = point1;
	int r;
	r = this->transformPoint(p, rp1);
	if (r == 2) return 0;
	p = point2;
	r = this->transformPoint(p, rp2);
	if (r == 2) return 0;

	// draw a raw line with them
	return this->raw_drawLine(rp1, rp2);
}

int RendererProgram::transformPoint(Vector4f& p, std::pair<int,int>& rp)
{
	// modelview transformation
	math::multiply(p, this->modelview);

	// projection transformation
	math::multiply(p, this->proj);

	// normalization transformation
	if (p.w() == 0) return 1;
	p.normalize();

	// simple clipping
	if (p.z() < -1 || p.z() > 1)
	{
		viewport.posOf(p.x(), p.y(), rp.first, rp.second);
		return 2;
	}

	// viewport transformation
	return this->viewport.posOf(p.x(), p.y(), rp.first, rp.second) ? 0 : 1;
}
