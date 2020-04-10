#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int number_of_satellite = 60;
	int number_of_log = 20;

	auto base_seed_x = ofRandom(1000);
	auto base_seed_y = ofRandom(1000);
	auto base_location = glm::vec3(
		ofMap(ofNoise(base_seed_x, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -250, 250),
		ofMap(ofNoise(base_seed_y, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -250, 250),
		0);
	auto base_radius = 100;

	ofSetColor(239);
	ofDrawSphere(base_location, base_radius);

	vector<glm::vec3> location_list;
	for (int i = 0; i < number_of_satellite; i++) {

		float noise_seed_x = ofRandom(1000);
		float noise_seed_y = ofRandom(1000);
		auto location = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
		location = glm::normalize(location) * base_radius * 1.2;

		for (int k = 0; k < number_of_log; k++) {

			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + k) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + k) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
			auto tmp_base_location = glm::vec3(
				ofMap(ofNoise(base_seed_x, (ofGetFrameNum() + k) * 0.005), 0, 1, -250, 250),
				ofMap(ofNoise(base_seed_y, (ofGetFrameNum() + k) * 0.005), 0, 1, -250, 250),
				0);
			auto loc = tmp_base_location + glm::vec4(location, 0) * rotation_y * rotation_x;
			location_list.push_back(loc);
		}
	}

	ofSetColor(39);
	for (int i = 0; i < location_list.size(); i++) {

		//ofDrawSphere(location_list[i], 2);
		for (int k = i + 1; k < location_list.size(); k++) {

			if (glm::distance(location_list[i], location_list[k]) < 35) {

				ofDrawLine(location_list[i], location_list[k]);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}