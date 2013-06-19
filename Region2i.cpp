/** \file Region2i.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */
#include "Region2i.h"

using namespace derplot;
using namespace math;

Region2i::Region2i()
:	x_min(0)
,	x_max(0)
,	y_min(0)
,	y_max(0)
{
}

Region2i::Region2i(int x_min, int x_max, int y_min, int y_max)
:	x_min(x_min)
,	x_max(x_max)
,	y_min(y_min)
,	y_max(y_max)
{
	fix();
}

Region2i::Region2i(int x, int y)
:	x_min(0)
,	x_max(x)
,	y_min(0)
,	y_max(y)
{
	fix();
}

Region2i::Region2i(const Region2i& other)
:	x_min(other.x_min)
,	x_max(other.x_max)
,	y_min(other.y_min)
,	y_max(other.y_max)
{
}

Region2i::Region2i(Region2i&& other)
:	x_min(other.x_min)
,	x_max(other.x_max)
,	y_min(other.y_min)
,	y_max(other.y_max)
{
}

Region2i& Region2i::operator=(const Region2i& other)
{
	if (this == &other) return *this; // handle self assignment
	this->x_min = other.x_min;
	this->x_max = other.x_max;
	this->y_min = other.y_min;
	this->y_max = other.y_max;
	return *this;
}

Region2i& Region2i::operator=(Region2i&& other)
{
	if (this == &other) return *this; // handle self assignment
	this->x_min = other.x_min;
	this->x_max = other.x_max;
	this->y_min = other.y_min;
	this->y_max = other.y_max;
	return *this;
}

bool Region2i::set(int x_min, int x_max, int y_min, int y_max)
{
	if (x_max < x_min || y_max < y_min)
		return false;
	this->x_min = x_min;
	this->x_max = x_max;
	this->y_min = y_min;
	this->y_max = y_max;
	return true;
}

bool Region2i::fitsIn(const Region2i& super_region) const
{
	return super_region.x_min <= this->x_min
		&& super_region.x_max >= this->x_max
		&& super_region.y_min <= this->y_min
		&& super_region.y_max >= this->y_max;
}

bool Region2i::fitsIn(int width, int height) const
{
	return fitsIn(Region2i(0,width,0,height));
}

bool Region2i::posOf(float x, float y, int& px, int& py) const
{
	const int xdelta = x_max-x_min;
	const int ydelta = y_max-y_min;

	px = x_min + (int)(xdelta*(x+1)*0.5);
	py = y_max - (int)(ydelta*(y+1)*0.5);
	return !(x < 0 || x >= 1 || y < 0 || y >= 1);
}

int Region2i::area(void) const
{
	return (x_max - x_min)*(y_max - y_min);
}

void Region2i::fix(void)
{
	if (x_max < x_min) x_max = x_min;
	if (y_max < y_min) y_max = y_min;
}

