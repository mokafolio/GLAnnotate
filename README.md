GLAnnotate [![Build Status](https://travis-ci.org/mokafolio/Stick.svg?branch=master)](https://travis-ci.org/mokafolio/GLAnnotate)
======

Overview
--------

*GLAnnotate* is a single header *OpenGL* utility for rapid prototyping and debug drawing in *OpenGL*. It gives you all the simple but slow things we miss from oldschool *OpenGL* such as matrix stacks and immediate mode drawing.

In addition to that it also supports custom vertex attributes.

Baisc Example
--------

```
//setup orthi projection
gla.ortho(0, 800, 600, 0, -1, 1);
gla.setColor(1.0, 0.5, 0.25);
gla.circle(400, 300, 100);

gla.setColor(0.25, 0.5, 1.0);
gla.rect(50, 50, 100, 100);

gla.setColor(1.0, 0.0, 0.0);
gla.line(100, 100, 400, 300);

//easy way to draw a texture (tex is an OpenGL texture handle)
gla.setColor(1.0, 1.0, 1.0);
gla.texture(tex, 400, 200, tw, th);

//draw a custom shape
gla.begin(GL_TRIANGLE_FAN);
gla.setColor(1.0, 1.0, 1.0);
gla.vertex(100, 200, 0);
gla.setColor(1.0, 0.0, 0.3);
gla.vertex(50, 200, 0);
gla.setColor(1.0, 1.0, 0.3);
gla.vertex(100, 100, 0);
gla.setColor(1.0, 0.25, 0.3);
gla.vertex(150, 200, 0);
gla.setColor(1.0, 0.25, 1.0);
gla.vertex(150, 300, 0);
gla.setColor(0.0, 0.25, 1.0);
gla.vertex(50, 300, 0);
gla.setColor(1.0, 0.0, 0.3);
gla.vertex(50, 200, 0);
gla.end();
```

Supported Platforms
-------------

*Linux* and *OSX* at this point in time. (should be trivial to add more)


Dependencies
--------

OpenGL


License
-------------

MIT License.


Installation
-------------

Either install the header file in the default location:

```
mkdir build
cd build
cmake ..
make install
```

and then include it like this

```
#include <GLAnnotate/GLAnnotate.hpp>
```

Or simply copy the file into your project and include it from there!

