#include "button.h"

button::button(string _title) {

	title = _title; 
	font.load("Roboto-Regular.ttf", 32);
}

void button::draw(glm::vec2 _position, glm::vec2 _size) {

	position = _position;
	size = _size;

		ofPushMatrix();
		ofTranslate(position);
		ofPushStyle();
		if (isPressed) {
			ofSetColor(128);
			
		}
		else {
			ofSetColor(255);
		}
		
		ofDrawRectangle(0, 0, size.x, size.y);
		ofPopStyle();
		ofPushStyle();
		ofSetColor(0);
		//ofDrawBitmapString(title, ofGetWidth()*0.02, ofGetWidth()*0.02);
		font.drawString(title, ofGetWidth()*0.02, ofGetWidth()*0.04);
		ofPopStyle();
		ofPopMatrix();

}

bool button::mousePressed(int _x, int _y) {
	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y < (position.y + size.y)) {
		isPressed = TRUE;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void button::mouseReleased(int _x, int _y) {
	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y < (position.y + size.y)) {
		isPressed = FALSE;
	}
}