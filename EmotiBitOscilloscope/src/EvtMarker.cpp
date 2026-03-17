#include "EvtMarker.h"
#include <ofUtils.h>
#include <ofApp.h>

#define UI_EVT_MARKTER_MAX_CNT		100

static ofColor getColor(int event) {
	static ofColor colors[] = {
			ofColor(255,  65,  45),  
			ofColor(255, 105,  50),   
			ofColor(255, 145,  60),  
			ofColor(255, 180,  75),  
			ofColor(255, 210, 110),

			ofColor(10,  40, 120),    
			ofColor(20,  90, 180),    
			ofColor(40, 130, 200),  
			ofColor(60, 160, 220),  
			ofColor(80, 190, 235)
	};
	int idx = std::max(0, std::min(9, event-1));
	return colors[idx];
}
static void drawString(const ofTrueTypeFont& font, const std::string& str, int x, int y) {
	if (font.isLoaded())
	{
		font.drawString(str, x, y);
	} else
	{
		ofDrawBitmapString(str, x, y);
	}
}

// ----------------------------------------------------------------------------
void EvtMarker::feed(uint32_t time, int32_t val) {
	_marks.emplace_back(time, val);

	if (_marks.size() > UI_EVT_MARKTER_MAX_CNT) {
		_marks.pop_front();
	}
}
void EvtMarker::draw() {
	// double window
	float window = _pRefScope ? ((ofxOscilloscope*)_pRefScope)->getTimeWindow() * 2 : 20.0;
	ofApp* app = (ofApp*)ofGetAppPtr();

	ofPushStyle();

	// background
	ofFill();
	ofSetColor(200, 200, 200);
	ofDrawRectangle(0, ofGetWindowHeight() - app->_consoleHeight - UI_HEIGHT_EVT_MARKER, UI_WIDTH_EVT_MARKER, UI_HEIGHT_EVT_MARKER);
	ofNoFill();

	// legend and time span
	std::string str = "Event";
	float x = 10;
	float y = 20 + ofGetWindowHeight() - app->_consoleHeight - UI_HEIGHT_EVT_MARKER;
	ofSetColor(ofColor::red);
	drawString(app->legendFont, str, x, y);

	ofSetColor(ofColor::white);
	str = ofToString(window) + " sec";
	x += 5;
	y += 15;
	drawString(app->axesFont, str, x, y);

	// draw center line
	y = ofGetWindowHeight() - app->_consoleHeight - UI_HEIGHT_EVT_MARKER / 2;
	ofSetLineWidth(3.0);
	ofDrawLine(100, y, 1400, y);
	// draw marks legends
	ofSetLineWidth(2.0);
	y = ofGetWindowHeight() - app->_consoleHeight - UI_HEIGHT_EVT_MARKER;
	for (int i = 1; i <= 10; ++i) {
		ofSetColor(getColor(i));
		x = 1400 + i * 8;
		ofDrawLine(x, y + 5, x, y + 25);
		str = ofToString(i);
		int x2 = x - 3;
		if (i == 1) {
			str = "-" + str;
			x2 -= 2;
		}
		else if (i == 10) {
			str += "+";
			x2 -= 2;
		}
		drawString(app->subLegendFont, str, x2, y + UI_HEIGHT_EVT_MARKER - 7);
	}

	// draw marks
	y = ofGetWindowHeight() - app->_consoleHeight - UI_HEIGHT_EVT_MARKER / 2;
	window *= 1000; // in millisecond
	for (const EvtMarkerPair& p : _marks) {
		if (p._time > _tnow)break;
		if (_tnow > p._time + window)continue;
		float x = 1400 - 1300 * (_tnow - p._time) / window ;
		ofSetColor(getColor(p._val));
		ofDrawLine(x, y -10, x, y + 10);
	}

	ofPopStyle();
}
 