//
//  ofxTessellationShader.h
//
//  Created by Dave Towey on 28/09/2014.
//
//

#pragma once

#include "ofMain.h"

class ofxTessellationShader : public ofShader {
    
public:
    
    bool load(string vertName, string fragName, string tcName="", string teName="", string geomName="");
	
    
    
};

