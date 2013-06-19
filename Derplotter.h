/** \file Derplotter.h
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 *
 * \brief Main Derplotter inclusion file
 * \namespace derplot
 * \brief base namespace for the Derplotter library
 *
 * \mainpage Derplotter Index Page
 *
 * \section intro_sec Introduction
 *
 * \b Derplotter is a simple 3D software renderer. With this library, the user can
 * create an arbitrary number of renderers for the purpose of drawing points and lines
 * in a buffer, which can later be used for displaying or further processing.
 *
 * Its interface has a few similarities with the OpenGL API, allowing the programmer to
 * define a clear color and front color, defining and applying transformations on the
 * modelview and projection matrices, and ultimately invoke simple drawing operations.
 *
 * All operations of the renderer are executed in a separate thread,
 * creating the same "illusion" of other graphics API, which operate on a separate
 * graphics processing device.
 *
 * \section install_sec Installation
 *
 * \b Derplotter is a static library.
 *
 * \subsection step1 Step 1: Compiling the library
 *
 * Compile it with the given Makefile in order to produce
 * the static library file \c libDerplotter.a
 *
 * Please make sure that the compiler is willing to accept the C++11 standard.
 * In GCC, this can be done by adding the flag <tt>-std=c++0x</tt> or
 * <tt>-std=c++11</tt>. A version of GCC 4.6.1 or earlier is recommended.
 *
 * \subsection step2 Step 2: Including the library
 *
 * Simply include Derplotter.h to access all features of the library. All declarations
 * of <b>Derplotter</b> are situated in the \c derplot namespace.
 *
 * The actual rendering process is done by creating an instance of \c Renderer and
 * invoking the desired operations with the appropriate functions
 * ( <tt>clear()</tt>, <tt>ortho()</tt>, <tt>drawPoint()</tt> and many others).
 * Since the operations are executed in paralel to the main process thread, the
 * \c flush() function can be used to force the complete execution of all operations in
 * the rendering process before the main thread continues.
 *
 * See the \c Renderer class documentation for more usage information.
 *
 * \subsection step3 Step 3: Linking the library with the program
 *
 * The library has no additional dependencies. Only the \b Derplotter static library
 * needs to be considered. This can be done in gcc using the \c -lDerplotter flag
 * in the linking process.
 *
 */

#pragma once
#ifndef DERPLOTTER_MAIN_H
#define DERPLOTTER_MAIN_H 1

// derplot::math (utility libraries)
#include "MathUtils.h"
#include "Vector4f.h"
#include "Mat4x4f.h"
#include "Region2i.h"

// derplot (base rendering component)
#include "Renderer.h"

#endif
