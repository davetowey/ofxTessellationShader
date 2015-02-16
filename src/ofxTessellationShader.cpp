//
//  ofxTessellationShader.cpp
//
//  Created by Dave Towey on 28/09/2014.
//
//

#include "ofxTessellationShader.h"


//--------------------------------------------------------------
bool ofxTessellationShader::load(string vertName, string fragName, string tcName, string teName, string geomName) {
    
    // TODO: Add check for OpenGL4
    
	if(vertName.empty() == false) setupShaderFromFile(GL_VERTEX_SHADER, vertName);
	if(fragName.empty() == false) setupShaderFromFile(GL_FRAGMENT_SHADER, fragName);
#ifndef TARGET_OPENGLES
	if(geomName.empty() == false) setupShaderFromFile(GL_GEOMETRY_SHADER_EXT, geomName);
    if(tcName.empty() == false) setupShaderFromFile(GL_TESS_CONTROL_SHADER, tcName);
    if(teName.empty() == false) setupShaderFromFile(GL_TESS_EVALUATION_SHADER, teName);
#endif
	if(ofIsGLProgrammableRenderer()){
		bindDefaults();
	}
	return linkProgram();
}