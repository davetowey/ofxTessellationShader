# ofxTessellationShader

A simple ofShader subclass and OSX example for using tessellation shaders in OF.

Requires OpenGL 4+ 

i.e. in main.cpp:

> ofGLWindowSettings settings;

> settings.glVersionMajor = 4;

> settings.glVersionMinor = 1;

> settings.width = 1024;

> settings.height = 786;

> settings.windowMode = OF_WINDOW;

> ofCreateWindow(settings);

Example also makes use of ofxUI - https://github.com/rezaali/ofxUI