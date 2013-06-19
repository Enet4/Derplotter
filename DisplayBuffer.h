/** \file DisplayBuffer.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 * \class derplot::DisplayBuffer
 * \brief Abstraction of a display buffer, with simple access functions.
 */

#pragma once

namespace derplot
{

class DisplayBuffer
{
	private:
		int width;
		int height;
		unsigned int* buff;
		unsigned int* inner_buff;

	public:
		/** Default constructor */
		DisplayBuffer();

		/** Main Constructor
		 * \param width
		 * \param height
		 * \param extern_buffer
		 */
		DisplayBuffer(int width, int height, void* extern_buffer = nullptr);

		/** Default destructor */
		~DisplayBuffer();

		/** No Copy constructor */
		DisplayBuffer(const DisplayBuffer& other) = delete;

		/** Move constructor
		 *  \param other object to move from
		 */
		DisplayBuffer(DisplayBuffer&& other);

		/** No Copy Assignment operator */
		DisplayBuffer& operator=(const DisplayBuffer& other) = delete;

		/** Move Assignment operator
		 *  \param other object to assign from
		 *  \return a reference to this
		 */
		DisplayBuffer& operator=(DisplayBuffer&& other);

		/** Checks whether the buffer can be used.
		 * \return \b true iif the buffer is not ready
		 */
		bool operator!(void) const;

		/** Getter for the width of the buffer
		 * \return the buffer's width
		 */
		int getWidth(void) const;

		/** Getter for the height of the buffer
		 * \return the buffer's height
		 */
		int getHeight(void) const;

		/** Getter for the buffer data pointer
		 * \return a pointer to the buffer data
		 */
		const unsigned int* data(void) const;

		/**
		 * \param x
		 * \param y
		 * \param output reference of index
		 * \return Whether the given coordinates are valid
		 */
		bool indexOf(unsigned int x, unsigned int y, unsigned int& ind) const;


		/**
		 * Clears the buffer using the given color.
		 * \param color the 32-bit ARGB color value.
		 * \return whether the operation was successful
		 */
		bool clear(unsigned int color);

		/**
		 * \param x
		 * \param y
		 * \param color
		 * \return Whether the given coordinates are valid
		 */
		bool plot(int x, int y, unsigned int color);

	protected:
	private:

		unsigned int* usedbuffer(void);
};

};
