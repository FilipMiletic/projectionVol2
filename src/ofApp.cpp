#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    video.loadMovie("NAZIV.mov"); //Load movie file
    video.play();
    
    //setup fbo
    fbo.allocate(videoWidth, videoHeight, GL_RGBA);
    
    //clear fbo so we do not collect artifacts picked up by gpu from memory
    fbo.begin();
    ofClear(255,255,255,0);
    fbo.end();
    
    if (video.isFrameNew()) {
        //draw video into fbo
        fbo.begin();
    }
    
    int alpha = 30;
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, alpha);
    
    //draw image into fbo
    video.draw(0, 0);
    ofDisableAlphaBlending();
    fbo.end();
    
    //Setup matrices
    for (int y=0; y<H-1; y++) {
        for (int x=0; x<W-1; x++) {
            int i1 = x + W*y;
            int i2 = x+1 + W*y;
            int i3 = x + W*(y+1);
            int i4 = x+1 + W*(y+1);
            
            mesh.addTriangle(i1, i2, i3);
            mesh.addTriangle(i2, i4, i3);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //Update video
    video.update();
    
    for (int y=0; y < H; y++){
        for (int x=0; x < W; x++){
            
            //vertex index
            int i = x + W*y;
            ofPoint p = mesh.getVertex(i);
            
            float scaleX = videoWidth/W;
            float scaleY = videoHeight/H;
            
            //get brightness
            int index = ((x * scaleX) + videoWidth * (y * scaleY)) * 4;
            int brightness = fboPixels[index]; // 4 is an arbitrary scalar to reduce the amount of distortion
            
            //Change z-coordinate of vertex
            p.z = brightness;
            mesh.setVertex(i, p);
            
            //Change color of Vertex
            mesh.setColor(i, ofColor(255,255,255));
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    ofSetHexColor(0xffffff);
    
    //fbo.draw(0, 0);
    
    ofPushMatrix(); // storing the coordinate system
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
   // mesh.drawWireframe();
    ofPopMatrix(); // restore coordinate system
    
    video.bind();
    mesh.draw();
    video.unbind();
    
    tiltCurrent = ofLerp(tiltCurrent, tiltTarget, 0.1);
    turnCurrent = ofLerp(turnCurrent, turnTarget, 0.1);
    
    ofRotateX(tiltCurrent);
    ofRotateZ(turnCurrent);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_DOWN) {
        tiltTarget -= 5;
    } else
    if (key == OF_KEY_UP) {
        tiltTarget += 5;
    } else
    if (key == OF_KEY_LEFT) {
        turnTarget -= 5;
    } else
    if (key == OF_KEY_RIGHT) {
        turnTarget += 5;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
