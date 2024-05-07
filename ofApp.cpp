#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSeedRandom(39);
	ofSetColor(39);
	for (int deg = 0; deg < 360; deg += 30) {

		ofPushMatrix();
		ofRotate(deg);

		auto base_location = glm::vec2(0, -100);
		auto target_location = glm::vec2(0, -340);
		auto distance = target_location - base_location;
		auto len = glm::length(distance);
		auto noise_seed = ofRandom(1000);

		ofBeginShape();
		for (int d = 0; d <= len; d += 1) {

			auto location = base_location + glm::normalize(distance) * d;

			auto gap = abs(len * 0.5 - d);
			auto power = gap < len * 0.35 ? 1 : ofMap(gap, len * 0.35, len * 0.5, 1, 0);

			auto noise_x = ofMap(ofNoise(noise_seed, location.x  * 0.05, (((int)location.y /10) * 10) * 0.025 + ofGetFrameNum() * 0.075), 0, 1, -50, 50);
			location += glm::vec2(noise_x * power, 0);

			ofVertex(location);
		}
		ofEndShape();

		ofPopMatrix();
	}

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}