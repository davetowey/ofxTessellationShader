#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    setupGui();
    
    loadTextures();
    
    tessShader.load("shaders/terrain_vert.glsl","shaders/terrain_frag.glsl","shaders/terrain_tcs.glsl","shaders/terrain_tes.glsl", "shaders/terrain_geom.glsl");
    
    mesh.setMode(OF_PRIMITIVE_PATCHES);
    patchMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    float width = 1024;
    int tiles = 4;
    
    for(int y = 0; y < tiles; y++){
        
        for (int x = 0; x < tiles; x++){
            
            mesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles), 0, -width/2.0 + y*(width/tiles))); // A
            mesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles)+(width/tiles), 0, -width/2.0 + y*(width/tiles))); // B
            mesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles), 0, -width/2.0 + y*(width/tiles)+(width/tiles))); // C
            mesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles)+(width/tiles), 0, -width/2.0 + y*(width/tiles))); //B
            mesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles), 0, -width/2.0 + y*(width/tiles)+(width/tiles))); //C
            mesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles)+(width/tiles), 0, -width/2.0 + y*(width/tiles)+(width/tiles))); //D
            
            patchMesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles), 0, -width/2.0 + y*(width/tiles))); // A
            patchMesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles)+(width/tiles), 0, -width/2.0 + y*(width/tiles))); // B
            patchMesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles), 0, -width/2.0 + y*(width/tiles)+(width/tiles))); // C
            patchMesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles)+(width/tiles), 0, -width/2.0 + y*(width/tiles))); //B
            patchMesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles), 0, -width/2.0 + y*(width/tiles)+(width/tiles))); //C
            patchMesh.addVertex(ofVec3f(-width/2.0 + x*(width/tiles)+(width/tiles), 0, -width/2.0 + y*(width/tiles)+(width/tiles))); //D
            
        }
        
    }
    
    cam.enableMouseInput();
    cam.setDistance(1000);
    
    offset = 0.0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(speed == 0){
        
        offset = 0;
        
    }else{

        offset += speed;
    
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(bg);
    
    ofEnableDepthTest();
    
    
    if(blendMode == "ADD")
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    else if(blendMode == "MULTIPLY")
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    else
        ofDisableBlendMode();

    cam.begin();
    
    tessShader.begin();

    tessShader.setUniform1i("wireframe", bDrawWireframe);
    tessShader.setUniform1i("dynamic", bDynamicLOD);
    tessShader.setUniform1f("alpha", 0.2);
    tessShader.setUniform1f("offset", offset);
    tessShader.setUniformTexture("heightmap", heightMaps[heightIndex], 1);
    tessShader.setUniformTexture("colourmap", colourMaps[colourIndex], 2);
    tessShader.setUniform1i("innerLevel", innerLevel);
    tessShader.setUniform1i("outerLevel", outerLevel);
    tessShader.setUniform3fv("eye_position", cam.getPosition().getPtr());
    tessShader.setUniform1f("ve", ve);
    
    if(bDrawFill) mesh.draw(OF_MESH_FILL);
    
    tessShader.end();
    
    
    if(bDrawPatches){
        
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
        patchMesh.draw(OF_MESH_WIREFRAME);
        
    }
    
    cam.end();
    
    
}

//--------------------------------------------------------------
void ofApp::exit()
{
    gui->saveSettings("settings.xml");
    delete gui;
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
    
    if(e.getName() == "BG_RED"){
        
        ofxUISlider *slider = e.getSlider();
        bg.r = slider->getScaledValue();
    
    }else  if(e.getName() == "BG_GREEN"){
    
        ofxUISlider *slider = e.getSlider();
        bg.g = slider->getScaledValue();
    
    }else if(e.getName() == "BG_BLUE"){
        
        ofxUISlider *slider = e.getSlider();
        bg.b = slider->getScaledValue();
    
    }else if(e.getName() == "SPEED"){
        
        ofxUISlider *slider = e.getSlider();
        speed = slider->getScaledValue();
        
    }else if(e.getName() == "BLEND_MODE"){
        
        ofxUIRadio *radio = (ofxUIRadio *)(e.widget);
        blendMode = radio->getActiveName();
    
    }else if(e.getName() == "PATCHES"){
        
        ofxUIToggle *toggle = e.getToggle();
        bDrawPatches = toggle->getValue();
        
    }else if(e.getName() == "FILL"){
        
        ofxUIToggle *toggle = e.getToggle();
        bDrawFill = toggle->getValue();

    }else if(e.getName() == "WIREFRAME"){
        
        ofxUIToggle *toggle = e.getToggle();
        bDrawWireframe = toggle->getValue();
        
    }else if(e.getName() == "INNER_TESS"){
        
        ofxUIIntSlider *slider = (ofxUIIntSlider*)e.getSlider();
        innerLevel = slider->getValue();
        
    }else if(e.getName() == "OUTER_TESS"){
        
        ofxUIIntSlider *slider = (ofxUIIntSlider*)e.getSlider();
        outerLevel = slider->getValue();
        
    }else if(e.getName() == "DYNAMIC_LOD"){
        
        ofxUIToggle *toggle = e.getToggle();
        bDynamicLOD = toggle->getValue();

    }else  if(e.getName() == "VE"){
        
        ofxUISlider *slider = e.getSlider();
        ve = slider->getScaledValue();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'g':
            gui->toggleVisible();
            break;
        case '.':
            heightIndex++;
            heightIndex %= heightMaps.size();
            break;
        case ',':
            heightIndex--;
            heightIndex %= heightMaps.size();
            break;
        case '=':
            colourIndex++;
            colourIndex %= colourMaps.size();
            break;
        case '-':
            colourIndex--;
            colourIndex %= colourMaps.size();
            break;
        default:
            break;
    }

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::loadTextures(){
    
    heightMaps.push_back(ofTexture());
    heightMaps.back().setTextureWrap(GL_REPEAT, GL_REPEAT);
    ofLoadImage(heightMaps[heightMaps.size()-1],"rough_height.png");
    
    heightMaps.push_back(ofTexture());
    heightMaps.back().setTextureWrap(GL_REPEAT, GL_REPEAT);
    ofLoadImage(heightMaps[heightMaps.size()-1],"repeatable.png");
    
    colourMaps.push_back(ofTexture());
    colourMaps.back().setTextureWrap(GL_REPEAT, GL_REPEAT);
    ofLoadImage(colourMaps[colourMaps.size()-1],"rough_rgb.png");
    
    colourMaps.push_back(ofTexture());
    colourMaps.back().setTextureWrap(GL_REPEAT, GL_REPEAT);
    ofLoadImage(colourMaps[colourMaps.size()-1],"rough_height.png");
    
    colourMaps.push_back(ofTexture());
    colourMaps.back().setTextureWrap(GL_REPEAT, GL_REPEAT);
    ofLoadImage(colourMaps[colourMaps.size()-1],"white.jpg");
    
    
    heightIndex = 0;
    colourIndex = 0;

    
}
//--------------------------------------------------------------
void ofApp::setupGui(){
    
    gui = new ofxUICanvas();
    
    gui->addLabel("BACKGROUND");
    gui->addSlider("BG_RED",0.0,255.0,100.0);
    gui->addSlider("BG_GREEN",0.0,255.0,100.0);
    gui->addSlider("BG_BLUE",0.0,255.0,100.0);
    
    gui->addSpacer();
    gui->addSpacer();
    
    gui->addSlider("SPEED", 0.0, 20.0, 10.0);
    
    vector<string> modes;
    modes.push_back("ADD");
    modes.push_back("MULTIPLY");
    modes.push_back("NONE");
    
    gui->addSpacer();
    gui->addSpacer();
    
    gui->addLabel("BLEND MODE");
    gui->addRadio("BLEND_MODE", modes);
    
    gui->addSpacer();
    gui->addSpacer();
    
    gui->addLabel("DRAW MODE");
    gui->addToggle("PATCHES", false);
    gui->addToggle("FILL", true);
    gui->addToggle("WIREFRAME", false);
    
    gui->addSpacer();
    gui->addSpacer();
    
    gui->addLabel("TESSELLATION");
    gui->addToggle("DYNAMIC_LOD", false);
    gui->addIntSlider("INNER_TESS", 0, 32, 4);
    gui->addIntSlider("OUTER_TESS", 0, 32, 4);
    
    gui->addSpacer();
    gui->addSpacer();
    
    gui->addSlider("VE",0.0,1000.0,200.0);
    
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
    gui->loadSettings("settings.xml");
    
}
