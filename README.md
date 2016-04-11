[![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

Derplotter is a simple 3D software renderer. With this library, the user can create an arbitrary number of renderers for the purpose of drawing points and lines in a buffer, which can later be used for displaying or further processing.

Its interface has a few similarities with the OpenGL API, allowing the programmer to define a clear color and front color, defining and applying transformations on the modelview and projection matrices, and ultimately invoke simple drawing operations.

All operations of the renderer are executed in a separate thread, creating the same "illusion" of other graphics API, which operate on a separate graphics processing device.
