#include "react.h"

// React constructor
react::react(string _path) {
	image.load(_path);
	
	animLength = 1;
	animating = FALSE;
}

// React update
void react::update(int _react) {

	// Scale and position calculated based on position in array.
	imageWidth = ((ofGetWidth()*0.8) / 5) *0.9;
	imagePosx = ofGetWidth()*0.11 + (_react * ((ofGetWidth()*0.8) / 5)+(imageWidth*0.5));

	// Change size when animating
	if (animating) {
		if (animLength > 0.1) {
			animLength -= 0.1;
		}
		else {
			animLength = 1;
			animating = FALSE;
		}
	}
}

// Draw to screen.
void react::draw(int _react) {
	
	// Push matrix so as not to disturb other draws on screen.
	ofPushMatrix();
	// Translate to position.
	ofTranslate(imagePosx, ofGetHeight()*0.8);
	// Draw from center of image.
	image.setAnchorPercent(0.5, 0.5);
	// Draw
	image.draw(0, 0, imageWidth, imageWidth);
	// Pop matrix to return draw position.
	ofPopMatrix();

	// If animating.
	if (animating) {
		ofPushMatrix();
		ofPushStyle();

		// Calculate new scale based on position in animation.
		imageWidth += ofMap(animLength, 1, 0, 0, ofGetWidth()*0.4);
		ofTranslate(imagePosx, ofGetHeight()*0.8);

		ofEnableAlphaBlending();
		// Set transparency based on position in animation
		ofSetColor(255, 255, 255, ofMap(animLength,1,0,255,0));
		// Draw
		image.draw(0, 0, imageWidth, imageWidth);

		ofDisableAlphaBlending();

		ofPopStyle();
		ofPopMatrix();
	}

}

// Check if this particular react is clicked based on positon, scale and mouse position.
bool react::amClicked(glm::vec2 _mousePos, int _react) {

	if (ofDist(_mousePos.x, _mousePos.y, imagePosx, ofGetHeight()*0.8) < imageWidth*0.5) {
		return TRUE;
	}
	else {
		return FALSE;
	}

}

// Simmilar to amClicked but triggers animation rather than returning a value.
void react::clickAnim(glm::vec2 _mousePos, int _react) {
	
	if (ofDist(_mousePos.x, _mousePos.y, imagePosx, ofGetHeight()*0.8) < imageWidth*0.5) {
		animating = TRUE;
	}
	
}
