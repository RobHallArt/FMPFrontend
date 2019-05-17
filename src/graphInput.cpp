#include "graphInput.h"

// Borrowed from the content classifier, this class draws graphs on screen that can be interacted with by touch or click.

// Construct 2D graph (X/Y Axis)
graphInput::graphInput(glm::vec2 _position, glm::vec2 _size, glm::vec2 _vecValue, string _title) {
	position = _position;
	size = _size;
	vecValue = _vecValue;
	title = _title;

	mode = 2;
}
// Construct 1D graph (Slider)
graphInput::graphInput(glm::vec2 _position, glm::vec2 _size, float _fltValue, string _title) {
	position = _position;
	size = _size;
	fltValue = _fltValue;
	title = _title;

	mode = 1;
}
// Draw graph.
void graphInput::draw(glm::vec2 _position, glm::vec2 _size) {

	position = _position;
	size = _size;
	
	// Draw 2D Graph based on position and size of graph and data point
	if (mode == 2) {
		ofPushMatrix();
			ofTranslate(position);
			ofPushStyle();
			ofSetColor(255, 255, 255, 25);
			// Draw Background colour.
			ofDrawRectangle(0, 0, size.x, size.y);
			ofPushStyle();
			ofSetColor(255, 0, 0);
			// Draw Vertical Line
			ofDrawLine(0 + (size.x*0.5), 0, 0 + (size.x*0.5), size.y);
			// Draw Horizontal Line
			ofDrawLine(0, 0 + (size.y*0.5), size.x, 0 + (size.y*0.5));
			ofSetColor(0, 0, 255);
			// Draw data point
			ofDrawEllipse(ofMap(vecValue.x, -1, 1, 0, size.x), ofMap(vecValue.y, -1, 1, 0, size.y), ofGetWidth()*0.01, ofGetWidth()*0.01);
			ofPopStyle();
			ofPushStyle();
			ofSetColor(0);
			// Title Graph
			ofDrawBitmapString(title, ofGetWidth()*0.02, ofGetWidth()*0.02);
			ofPopStyle();
			ofPopStyle();
		ofPopMatrix();
	}
	// Draw 1D Graph
	else if (mode == 1) {
		ofPushMatrix();
			ofTranslate(position);
			ofPushStyle();
			ofSetColor(255, 255, 255, 25);
			// Draw Background
			ofDrawRectangle(0, 0, size.x, size.y);
			ofPushStyle();
			ofSetColor(255, 0, 0);
			// Draw Central line
			ofDrawLine(0, size.y*0.5, size.x, size.y*0.5);
			ofSetColor(0, 0, 255);
			// Draw Position of slider
			ofDrawEllipse(ofMap(fltValue, 0, 1, 0, size.x), size.y*0.5, size.x*0.01, size.y*0.8);
			ofPopStyle();
			ofPushStyle();
			ofSetColor(0);
			// Title Graph
			ofDrawBitmapString(title, ofGetWidth()*0.02, ofGetWidth()*0.02);
			ofPopStyle();
			ofPopStyle();
		ofPopMatrix();
	
	}
}

// Move the point when the graph is touched.
// This section is unused in the frontend program.
void graphInput::mousePressed(int _x, int _y) {
	// First check if click location is on graph on screen.
	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y< (position.y+size.y) && mode == 2) {
		// Calculate new value of the graph vector based on the position of the graph and click position
		vecValue = glm::vec2(ofMap(_x - position.x, 0, size.x, -1, 1), ofMap(_y - position.y, 0, size.y, -1, 1));
	}

	// This is the same but for 1D graph.
	if (_x > position.x && _x < (position.x + size.x) && _y > position.y && _y < (position.y + size.y) && mode == 1) {
		fltValue = ofMap(_x - position.x, 0, size.x, 0, 1);
	}
}