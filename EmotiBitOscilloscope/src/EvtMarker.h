#pragma once
#include <deque>
#include <ofxOscilloscope.h>

#define ENABLE_EVT_MARKER		1

#define UI_HEIGHT_EVT_MARKER	40
#define UI_WIDTH_EVT_MARKER		1500

// ref EmotiBitPacket::TypeTag: for other tags
#define TypeTag_EVT_MARKER		"EV"
#define TypeTag_EVT_MARKER_ECHO	"VE"

// a special event used by custom app to get communication delay
#define SYNC_EVT_ID				255


struct EvtMarkerPair {
	uint32_t _time;
	int32_t _val; 
	struct EvtMarkerPair(uint32_t time, int32_t val) {
		_time = time;
		_val = val;
	}
};

class EvtMarker {
public:
	EvtMarker() {
		_tnow = 0;
		_pRefScope = nullptr;
	}

	void setRefScope(const ofxOscilloscope& refScope) {
		_pRefScope = &refScope;
	}
	void setTNow(uint32_t tnow) {
		_tnow = tnow;
	}
	void feed(uint32_t time, int32_t val);
	void draw();

private:
	uint32_t _tnow;
	const ofxOscilloscope* _pRefScope;
	std::deque<EvtMarkerPair> _marks;
};