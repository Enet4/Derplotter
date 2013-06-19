/** \file Renderer.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 * \class derplot::Renderer
 * \brief Describes the renderer of <b>Derplotter</b>.
 *
 * When constructing a renderer, the display dimensions and a buffer large enough for
 * containing the whole pixels of the buffer are passed. If no buffer is specified,
 * an internal buffer is created. All buffers have a color depth of 32 bits and have
 * no additional padding bytes.
 *
 * Once the renderer is created, the operation invocation functions are used to send
 * the data blocks describing the full operation to perform in an internal operation
 * queue. One by one, the internal rendering thread will retrieve these blocks and
 * execute them. These operations can either change the status of the renderer (such as
 * defining the viewport) and/or write to the buffer (such as drawing a line). These
 * status changes are therefore performed in the same order of invocation, and proceeding
 * operations are guaranteed to be affected by previous changes.
 *
 * These invocations are non-blocking, and an operation is not guaranteed to be
 * completely performed after leaving the function in the operation invocation caller's
 * thread. The \c flush() function makes the caller thread wait until there are no more
 * operations left on the operation queue.
 *
 * The \c terminate() function can be called to nicely terminate the renderer's process,
 * making it no longer usable. Invocation operations on the renderer will not be passed
 * to the operation queue, but the buffer can still be read for as long as it remains on
 * scope.
 *
 * No concurrent protection is guaranteed on the buffer. Reading from it is safe after
 * a <tt>flush()</tt>, which means the operation queue is empty and no operations being
 * executed in the renderer thread. If an internal buffer is used, the result data
 * can be copied to a buffer using <tt>bufferCopy(void*)</tt>, under the same conditions
 * of reading access to an external buffer.
 */

#pragma once

#include "DisplayBuffer.h"
#include "Mat4x4f.h"
#include "Vector4f.h"
#include "RendererProgram.h"
#include "RendererOps.h"
#include <memory>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace derplot
{

class Renderer
{
	private:
		DisplayBuffer buffer;
		RendererProgram program;

		std::queue<std::unique_ptr<op::RendererOperation>> q;
		std::mutex q_mutex;
		std::condition_variable q_empty, q_hasOp;

		volatile bool ok;
		std::thread thread;

	public:
		/** Default constructor */
		Renderer();

		/** Main Constructor */
		Renderer(int width, int height, void* extern_buffer = nullptr);

		/** Default destructor */
		~Renderer();
		/** No Copy Constructor */
		Renderer(const Renderer& other) = delete;
		/** No Copy Assignment operator */
		Renderer& operator=(const Renderer& other) = delete;

		/** Checks whether the renderer is
		 * ready or not for rendering
		 *  \return \b true iif the renderer is not ready
		 */
		bool operator!(void) const;

		/** Makes the caller thread wait until the renderer
		 * has finished all operations in queue.
		 */
		void flush(void);

		/** Copies the current buffer content to the given destination buffer
		 * \warning A buffer overflow will occur if the destination buffer isn't large
		 * enough for the renderer's buffer contents (it must be at least 4*width*height
		 * large, in bytes).
		 * \param dest destination buffer
		 */
		int bufferCopy(void* dest) const;

		/** Renderer program invocation
		 *
		 * Passes a termination operation and waits
		 * until the renderer stops
		 */
		void terminate(void);

		/** Renderer program invocation
		 *
		 * Clears the whole display buffer using the current clear color
		 */
		void clear(void);

		/** Renderer program invocation
		 *
		 * Draws a point at the specified pixel coordinates, with the current
		 * front color. No transformations are applied. The pixel coordinates
		 * are relative to the top-left corner.
		 * \param point
		 */
		void drawRawPoint(std::pair<int,int> point);

		/** Renderer program invocation
		 *
		 * Like in \c drawRawPoint() , this function draws a slightly bigger point
		 * at the specified pixel coordinates, with the current front color. Adjacent up,
		 * down, left and right pixels are also plotted.
		 * \param point
		 */
		void drawRawBigPoint(std::pair<int,int> point);

		/** Renderer program invocation
		 *
		 * Draws a line from \b point1 to \b point2 , with no transformations, using the
		 * current front color. Point order is irrelevant.
		 * \param point1
		 * \param point2
		 */
		void drawRawLine(std::pair<int,int> point1, std::pair<int,int> point2);

		/** Renderer program invocation
		 *
		 * Draws a 3D point. Modelview, projection and normalization transformations are
		 * applied before drawing the result using the current front color.
		 * \param point
		 */
		void drawPoint(const math::Vector4f& point);

		/** Renderer program invocation
		 *
		 * Behaves like \c drawPoint() , but draws a slightly bigger point.
		 * \param point
		 */
		void drawBigPoint(const math::Vector4f& point);

		/** Renderer program invocation
		 *
		 * Draws a line from two 3D points, using the current front color.
		 * Modelview, projection and normalization transformations are applied before
		 * drawing. Point order is irrelevant.
		 * \param point1
		 * \param point2
		 */
		void drawLine(const math::Vector4f& point1, const math::Vector4f& point2);

		/** Renderer program invocation
		 *
		 * Passes the projection matrix being used to the renderer
		 * \param mat the projection matrix
		 */
		void setProjectionMatrix(const math::Mat4x4f& mat);


		/** Renderer program invocation
		 *
		 * Applies an orthographic projection transformation in the projection matrix
		 * according to the given parameters. The matrix is not modified if either one
		 * of the parameters is invalid.
		 * \param left the X minimum plane
		 * \param right the X maximum plane
		 * \param bottom the Y minimum plane
		 * \param top the Y maximum plane
		 * \param near the z near plane
		 * \param far the z far plane
		 * \param aspect_ratio the screen aspect ration
		 */
		void orthoProjection(float left, float right, float bottom, float top,
							float near, float far);

		/** Renderer program invocation
		 *
		 * Applies a perspective projection transformation in the projection matrix
		 * according to the given parameters. The matrix is not modified if either one
		 * of the parameters is invalid.
		 * \param fovy the Y Field of View angle in degrees
		 * \param near the z near plane
		 * \param far the z far plane
		 * \param aspect_ratio the screen aspect ration
		 */
		void perspectiveProjection(float fovy, float near, float far, float aspect_ratio);

		/** Renderer program invocation
		 *
		 * Passes the modelview matrix being used to the renderer
		 * \param mat the modelview matrix
		 */
		void setModelViewMatrix(const math::Mat4x4f& mat);

		/** Renderer program invocation
		 *
		 * Performs a translation transformation on the selected matrix
		 * used by the renderer. The transformation is ignored if the given matrix
		 * identification number is invalid.
		 * \param v the transformation vector
		 * \param matrix the identification matrix
		 * ( \c MATRIX_MODELVIEW or \c MATRIX_PROJECTION )
		 */
		void translate(const math::Vector4f& v, int matrix = MATRIX_MODELVIEW);

		/** Renderer program invocation
		 *
		 * Performs a rotation transformation, around the X axis, on the selected matrix
		 * used by the renderer. The transformation is ignored if the given matrix
		 * identification number is invalid.
		 * \param x_angle the angle of the counterclockwise rotation, in radians
		 * \param matrix the identification matrix
		 * ( \c MATRIX_MODELVIEW or \c MATRIX_PROJECTION )
		 */
		void rotateX(float x_angle, int matrix = MATRIX_MODELVIEW);

		/** Renderer program invocation
		 *
		 * Performs a rotation transformation, around the Y axis, on the selected matrix
		 * used by the renderer. The transformation is ignored if the given matrix
		 * identification number is invalid.
		 * \param y_angle the angle of the counterclockwise rotation, in radians
		 * \param matrix the identification matrix
		 * ( \c MATRIX_MODELVIEW or \c MATRIX_PROJECTION )
		 */
		void rotateY(float y_angle, int matrix = MATRIX_MODELVIEW);

		/** Renderer program invocation
		 *
		 * Performs a rotation transformation, around the Z axis, on the selected matrix
		 * used by the renderer. The transformation is ignored if the given matrix
		 * identification number is invalid.
		 * \param z_angle the angle of the counterclockwise rotation, in radians
		 * \param matrix the identification matrix
		 * ( \c MATRIX_MODELVIEW or \c MATRIX_PROJECTION )
		 */
		void rotateZ(float z_angle, int matrix = MATRIX_MODELVIEW);

		/** Renderer program invocation
		 *
		 * Performs a scale transformation on the selected matrix
		 * used by the renderer. The transformation is ignored if the given matrix
		 * identification number is invalid.
		 * \param v the transformation vector
		 * \param matrix the identification matrix
		 * ( \c MATRIX_MODELVIEW or \c MATRIX_PROJECTION )
		 */
		void scale(const math::Vector4f& v_scale, int matrix = MATRIX_MODELVIEW);

		/** Renderer program invocation
		 *
		 * Sets the front color for the succeding drawing operations.
		 * \param color the desired front color in ARGB format
		 */
		void front_color(unsigned int color);

		/** Renderer program invocation
		 *
		 * Sets the clear color for the succeding drawing operations.
		 * \param color the desired clear color in ARGB format
		 */
		void clear_color(unsigned int color);

		/** Renderer program invocation
		 *
		 * Passes the viewport region being used to the renderer
		 * \param viewport the viewport region
		 */
		void setViewPort(const math::Region2i& viewport);

		static constexpr unsigned int DEFAULT_FRONT_COLOR = 0xFFFFFFFF;
		static constexpr unsigned int DEFAULT_CLEAR_COLOR = 0xFF000000;
		static constexpr int MATRIX_MODELVIEW = 0;
		static constexpr int MATRIX_PROJECTION = 1;

	protected:
	private:

		/** Pass a renderer operation instance to the renderer
		 * \param op the operation to pass to the renderer
		 * \return a reference to this
		 */
		Renderer& operator>>(op::RendererOperation* op);

		/** Renderer thread main function */
		static void run(Renderer* renderer);

};

};
