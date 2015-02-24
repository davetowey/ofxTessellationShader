#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    
    //ofSetOpenGLVersion(4,1);
	//ofSetupOpenGL(1024,768,OF_WINDOW);
    
    ofGLWindowSettings settings;
    settings.glVersionMajor = 4;
    settings.glVersionMinor = 1;
    settings.width = 1024;
    settings.height = 786;
    settings.windowMode = OF_WINDOW;
    
    ofCreateWindow(settings);


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
