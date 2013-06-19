/** \file DisplayBuffer.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */
#include "DisplayBuffer.h"

#include <string.h>

using namespace derplot;

DisplayBuffer::DisplayBuffer()
:	width(0)
,	height(0)
,	buff(nullptr)
,	inner_buff(nullptr)
{}

DisplayBuffer::DisplayBuffer(int width, int height, void* extern_buffer)
:	width(width)
,	height(height)
,	buff((unsigned int*)extern_buffer)
,	inner_buff(nullptr)
{
	if (extern_buffer == nullptr)
		this->inner_buff = new unsigned int[width*height];
}

DisplayBuffer::~DisplayBuffer()
{
	if (inner_buff)
		delete inner_buff;
}

DisplayBuffer::DisplayBuffer(DisplayBuffer&& other)
:	width(other.width)
,	height(other.height)
,	buff(other.buff)
,	inner_buff(other.inner_buff)
{
	other.width = other.height = 0;
	other.inner_buff = other.buff = nullptr;
}

DisplayBuffer& DisplayBuffer::operator=(DisplayBuffer&& other)
{
	if (this == &other) return *this;
	this->width = other.width;
	this->height = other.height;
	this->buff = other.buff;
	this->inner_buff = other.inner_buff;
	other.width = other.height = 0;
	other.buff = other.inner_buff = nullptr;
	return *this;
}

bool DisplayBuffer::operator!(void) const
{
	return this->buff == nullptr && this->inner_buff == nullptr;
}

int DisplayBuffer::getWidth(void) const
{ return this->width; }

int DisplayBuffer::getHeight(void) const
{ return this->height; }

const unsigned int* DisplayBuffer::data(void) const
{
	return (this->buff != nullptr) ? buff : inner_buff;
}

bool DisplayBuffer::indexOf(unsigned int x, unsigned int y, unsigned int& ind) const
{
	if ((int)x >= width || (int)y >= height) return false;
	ind = this->width*y+x;
	return true;
}

bool DisplayBuffer::clear(unsigned int color)
{
	if (!(*this)) return false;
	for (int i = 0 ; i < width*height ; i++)
		this->usedbuffer()[i] = color;
	return true;
}


bool DisplayBuffer::plot(int x, int y, unsigned int color)
{
	if (!(*this)) return false;
	if (x < 0 || y < 0) return false;
	unsigned int ind = 0;
	if (!this->indexOf(x,y,ind))
		return false;
	this->usedbuffer()[ind] = color;
	return true;
}

unsigned int* DisplayBuffer::usedbuffer(void)
{
	return (this->buff != nullptr) ? buff : inner_buff;
}
