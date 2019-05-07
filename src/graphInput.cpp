#include "graphInput.h"

graphInput::graphInput(glm::vec2 _position, glm::vec2 _size, glm::vec2 _vecValue, string _title) {
	position = _position;
	size = _size;
	vecValue = _vecValue;
	title = _title;

	mode = 2;
}

graphInput::graphInput(glm::vec2 _position, glm::vec2 _size, float _fltValue, string _title) {
	position = _position;
	size = _size;
	fltValue = _fltValue;
	title = _title;

	mode = 1;
}

void graphInput::draw(glm::vec2 _position, glm::vec2 _size) {

	position = _position;
	size = _size;
	if (mode == 2) {
		ofPushMatrix();
			ofTranslate(position);
			ofPushStyle();
			ofSetColor(255, 255, 255, 25);
			ofDrawRectangle(0, 0, size.x, size.y);
			ofPushStyle();
			ofSetColor(255, 0, 0);
			ofDrawLine(0 + (size.x*0.5), 0, 0 + (size.x*0.5), size.y);
			ofDrawLine(0, 0 + (size.y*0.5), size.x, 0 + (size.y*0.5));
			ofSetColor(0, 0, 255);
			ofDrawEllipse(ofMap(vecValue.x, -1, 1, 0, size.x), ofMap(vecValue.y, -1, 1, 0, size.y), ofGetWidth()*0.01, ofGetWidth()*0.01);
			ofPopStyle();
			ofPushStyle();
			ofSetColor(0);
			ofDrawBitmapString(title, ofGetWidth()*0.02, ofGetWidth()*0.02);
			ofPopStyle();
			ofPopStyle();
		ofPopMatrix();
	}
	else if (mode == 1) {
		ofPushMatrix();
			ofTranslate(position);
			ofPushStyle();
			ofSetColor(255, 255, 255, 25);
			ofDrawRectangle(0, 0, size.x, size.y);
			ofPushStyle();
			ofSetColor(255, 0, 0);
			ofDrawLine(0, size.y*0.5, size.x, size.y*0.5);
			ofSetColor(0, 0, 255);
			ofDrawEllipse(ofMap(fltValue, 0, 1, 0, size.x), size.y*0.5, size.x*0.01, size.y*0.8);
			ofPopStyle();
			ofPushStyle();
			ofSetColor(0);
			ofDrawBitmapString(title, ofGetWidth()*0.02, ofGetWidth()*0.02);
			ofPopStyle();
			ofPopStyle();
		ofPopMatrix();
	
	}
}

void graphInput::mousePressed(int _x, int _y) {
	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y< (position.y+size.y) && mode == 2) {
		vecValue = glm::vec2(ofMap(_x - position.x, 0, size.x, -1, 1), ofMap(_y - position.y, 0, size.y, -1, 1));
	}

	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y < (position.y + size.y) && mode == 1) {
		fltValue = ofMap(_x - position.x, 0, size.x, 0, 1);
	}
}