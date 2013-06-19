/** \file RendererProgram.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 * \class derplot::RendererProgram
 * \brief Implements rendering operations of the renderer
 */
#pragma once

#include "DisplayBuffer.h"
#include "Mat4x4f.h"
#include "Vector4f.h"
#include "Region2i.h"

namespace derplot
{

enum RendererDrawMode : unsigned char
{
	NOTHING    = 0x00,
	POINTS     = 0x01,
	BIG_POINTS = 0x02,
	LINES      = 0x04,
	LINE_STRIP = 0x05,
	LINE_LOOP  = 0x06
};

class RendererProgram
{
	private:
		DisplayBuffer* p_buffer;
	public:
		math::Mat4x4f modelview;
		math::Mat4x4f proj;
		math::Region2i viewport;
		unsigned int front_color, clear_color;

	public:
		/** Default constructor */
		RendererProgram(void);

		/** Main constructor */
		RendererProgram(DisplayBuffer& buffer);
		/** Default destructor */
		virtual ~RendererProgram();

		/** \return whether the RendererProgram cannot be used */
		bool operator!(void) const;

		/** Copy constructor removed */
		RendererProgram(const RendererProgram& other) = delete;
		/** Assignment operator removed */
		RendererProgram& operator=(const RendererProgram& other) = delete;

		// other drawing operations
		int raw_clear(void);

		// 2D operations (no transformations needed, draw to buffer directly)
		int raw_drawPoint(const std::pair<int,int>& p);
		int raw_drawBigPoint(const std::pair<int,int>& p);
		int raw_drawLine(std::pair<int,int>& p1, std::pair<int,int>& p2);

		// 3D operations (need transformations)
		int drawPoint(const math::Vector4f& p);
		int drawBigPoint(const math::Vector4f& p);
		int drawLine(const math::Vector4f& p1, const math::Vector4f& p2);

		static constexpr unsigned int DEFAULT_FRONT_COLOR = 0xFFFFFFFF;
		static constexpr unsigned int DEFAULT_CLEAR_COLOR = 0xFF000000;
	protected:
	private:

		int transformPoint(math::Vector4f& p, std::pair<int,int>& rp);
};

};
