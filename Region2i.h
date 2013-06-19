/** \file Region2i.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 * \class derplot::math::Region2i
 * \brief Describes a 2D region in an integer plane <tt>(int,int)</tt>
 */

#pragma once

namespace derplot
{

namespace math
{

class Region2i
{
	int x_min, x_max;
	int y_min, y_max;

	public:
		/** Default constructor */
		Region2i();

		/** Main Constructor */
		Region2i(int x_min, int x_max, int y_min, int y_max);

		/** Origin Cornered Constructor */
		Region2i(int x, int y);

		/** Default destructor */
		~Region2i() = default;

		/** Copy constructor
		 *  \param other Object to copy from
		 */
		Region2i(const Region2i& other);

		/** Move constructor
		 *  \param other Object to move from
		 */
		Region2i(Region2i&& other);

		/** Copy Assignment operator
		 *  \param other Object to assign from
		 *  \return A reference to this
		 */
		Region2i& operator=(const Region2i& other);

		/** Move Assignment operator
		 *  \param other Object to assign from
		 *  \return A reference to this
		 */
		Region2i& operator=(Region2i&& other);

		/** Getter for the X minimum edge */
		inline int getMinX(void) const { return x_min; }
		/** Getter for the X maximum edge */
		inline int getMaxX(void) const { return x_max; }
		/** Getter for the Y minimum edge */
		inline int getMinY(void) const { return y_min; }
		/** Getter for the Y maximum edge */
		inline int getMaxY(void) const { return y_max; }

		/**
		 * \return whether this region fits in the super region
		 */
		bool fitsIn(const Region2i& super_region) const;

		/**
		 * \return whether this region fits in the given
		 * origin cornered region
		 */
		bool fitsIn(int width, int height) const;

		/** Determines the pixel position of the normalized
		 * point position (x,y), both ranged -1 to 1
		 * \param x the x coordinate of the point
		 * \param y the y coordinate of the point
		 * \param px output reference to x coordinate of the pixel
		 * \param py output reference to y coordinate of the pixel
		 * \return whether the given point is inside the region's boundaries
		 */
		bool posOf(float x, float y, int& px, int& py) const;

		/**
		 * Redefines the region with the given parameters, if they are valid.
		 * \return whether the given parameters are valid for a region
		 */
		bool set(int x_min, int x_max, int y_min, int y_max);

		/**
		 * \return the region's area in pixels
		 */
		int area(void) const;

	protected:
	private:
		void fix(void);
};

};

};
