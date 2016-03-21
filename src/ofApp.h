#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofVideoPlayer video; //Prerecorded video
    ofFbo fbo;
    ofMesh mesh;
    
    float tiltCurrent = 0;
    float tiltTarget = 0;
    float turnCurrent = 1;
    float turnTarget = 1;
    
private:
    int videoHeight = 720;
    int videoWidth = 480;
    int W = 100;
    int H = 100;
    int meshSize = 6;
		
};
