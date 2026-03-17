#include "ofMain.h"
#include "ofApp.h"
#include "ofxLSL.h"


//========================================================================
int main( ){
#if ENABLE_EVT_MARKER
	ofSetupOpenGL(1500,900+UI_HEIGHT_EVT_MARKER,OF_WINDOW);			// <-------- setup the GL context
#else
	ofSetupOpenGL(1500, 900, OF_WINDOW);			// <-------- setup the GL context
#endif

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
