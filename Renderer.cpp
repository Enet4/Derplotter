/** \file Renderer.cpp
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 */

#include "Renderer.h"

#include <string.h>

#ifdef Derplotter_DEBUG
#include <stdio.h>
static void DEBUG(const char* s)
	{ printf("RENDERER: %s\n", s); fflush(stdout);}
#else
static void DEBUG(const char* s){}
#endif

using namespace derplot;
using namespace op;
using namespace math;

Renderer::Renderer()
:	ok(false)
{}

Renderer::Renderer(int width, int height, void* extern_buffer)
:	buffer(width, height, extern_buffer)
,	program(buffer)
,	ok(true)
,	thread(run, this)
{}

Renderer::~Renderer()
{}

bool Renderer::operator!(void) const
{
	return !buffer || !ok;
}

int Renderer::bufferCopy(void* dest) const
{
	if (!(*this) || dest == nullptr) return 0;
	memcpy(dest, this->buffer.data(),
			buffer.getWidth()*buffer.getHeight()*sizeof(unsigned int));
	return 1;
}

Renderer& Renderer::operator>>(op::RendererOperation* op)
{
	if (!(*this)) return *this;
	std::unique_lock<std::mutex> q_lock(this->q_mutex);
	this->q.emplace(op);
	this->q_hasOp.notify_all();
	q_lock.unlock();
	return *this;
}

void Renderer::flush(void)
{
	if (!(*this)) return;
	std::unique_lock<std::mutex> q_lock(this->q_mutex);
	if (!q.empty())
		q_empty.wait(q_lock);
}

void Renderer::terminate(void)
{
	if (!(*this)) return;
	*this >> new Terminate;
	thread.join();
}

void Renderer::clear(void)
{	*this >> new Clear(); }

void Renderer::drawRawPoint(std::pair<int,int> p)
{	*this >> new RawPoint(p, 0); }

void Renderer::drawRawBigPoint(std::pair<int,int> p)
{	*this >> new RawPoint(p, 1); }

void Renderer::drawRawLine(std::pair<int,int> point1, std::pair<int,int> point2)
{	*this >> new RawLine(point1, point2); }

void Renderer::drawPoint(const Vector4f& p)
{	*this >> new Point(p, 0); }

void Renderer::drawBigPoint(const Vector4f& p)
{	*this >> new Point(p, 1); }

void Renderer::drawLine(const math::Vector4f& point1, const math::Vector4f& point2)
{	*this >> new Line(point1, point2); }

void Renderer::orthoProjection(float left, float right, float bottom, float top,
					float near, float far)
{ *this >> new Ortho(left, right, top, bottom, near, far); }

void Renderer::perspectiveProjection(float fovy, float near,
					float far, float aspect_ratio)
{ *this >> new Perspective(fovy, near, far, aspect_ratio); }

void Renderer::setProjectionMatrix(const math::Mat4x4f& mat)
{ *this >> new MatrixSet(mat, 1); }

void Renderer::setModelViewMatrix(const math::Mat4x4f& mat)
{ *this >> new MatrixSet(mat, 0); }

void Renderer::translate(const math::Vector4f& v, int matrix)
{ *this >> new MatrixTranslate(v, matrix); }

void Renderer::rotateX(float x_angle, int matrix)
{ *this >> new MatrixRotate(x_angle, 0, matrix); }

void Renderer::rotateY(float y_angle, int matrix)
{ *this >> new MatrixRotate(y_angle, 1, matrix); }

void Renderer::rotateZ(float z_angle, int matrix)
{ *this >> new MatrixRotate(z_angle, 2, matrix); }

void Renderer::scale(const math::Vector4f& v, int matrix)
{ *this >> new MatrixScale(v, matrix); }

void Renderer::front_color(unsigned int color)
{ *this >> new FrontColor(color); }

void Renderer::clear_color(unsigned int color)
{ *this >> new ClearColor(color); }

void Renderer::setViewPort(const math::Region2i& viewport)
{ *this >> new ViewPort(viewport); }

void Renderer::run(Renderer* renderer)
{
	DEBUG("I live!");
	bool running = true;
	RendererOperation* op = nullptr;
	do
	{
		std::unique_lock<std::mutex> q_lock(renderer->q_mutex);

		// wait for operation
		if (renderer->q.empty())
		{
			DEBUG("Waiting for operation...");
			renderer->q_hasOp.wait(q_lock);
			DEBUG("Woken up by \"hasOp\"\n");
		}

		// retrieve operation from operation queue
		op = (RendererOperation*) renderer->q.front().release();
		renderer->q.pop();

		q_lock.unlock();

		if (op == nullptr) continue;

		DEBUG("Executing...");
		int r = op->onDispatch(renderer->program); // dispatch operation
		DEBUG("Done Executing.");

		delete op;

		if (r == -1) // termination code
		{
			DEBUG("Terminating...");
			q_lock.lock();
			while (!renderer->q.empty()) renderer->q.pop(); // clear queue
			running = false;
			renderer->ok = false;
			q_lock.unlock();
		}

		q_lock.lock();
		if (renderer->q.empty())
		{
			DEBUG("Operation queue is empty. Signalling now.");
			renderer->q_empty.notify_all();
		}
		q_lock.unlock();
	}
	while(running);
	DEBUG("Reached end of thread function.");
}
