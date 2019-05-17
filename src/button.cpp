#include "button.h"

// Constructor function for buttons
button::button(string _title) {

	title = _title; 
	// Load font for button text.
	font.load("Roboto-Regular.ttf", 32);
}

// Funtion for drawing buttons
void button::draw(glm::vec2 _position, glm::vec2 _size) {

	position = _position;
	size = _size;

		ofPushMatrix();
		// Translate to button position
		ofTranslate(position);
		ofPushStyle();

		// Set colour based on pressed state.
		if (isPressed) {
			ofSetColor(128);
			
		}
		else {
			ofSetColor(255);
		}
		
		// Draw outline rectangle
		ofDrawRectangle(0, 0, size.x, size.y);
		ofPopStyle();
		ofPushStyle();
		ofSetColor(0);
		// Draw button title
		font.drawString(title, ofGetWidth()*0.02, ofGetWidth()*0.04);
		ofPopStyle();
		ofPopMatrix();

}

// Function to check if a button is pressed and return a boolean.
bool button::mousePressed(int _x, int _y) {
	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y < (position.y + size.y)) {
		isPressed = TRUE;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// Function to reset a button when it is released;
void button::mouseReleased(int _x, int _y) {
	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y < (position.y + size.y)) {
		isPressed = FALSE;
	}
}