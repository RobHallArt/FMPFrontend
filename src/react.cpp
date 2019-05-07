#include "react.h"

react::react(string _path) {
	image.load(_path);
	
	animLength = 1;
	animating = FALSE;
}


void react::update(int _react) {


	imageWidth = ((ofGetWidth()*0.8) / 5) *0.9;
	imagePosx = ofGetWidth()*0.11 + (_react * ((ofGetWidth()*0.8) / 5)+(imageWidth*0.5));


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


void react::draw(int _react) {

	// use animate to set position when animate true
	ofPushMatrix();


	ofTranslate(imagePosx, ofGetHeight()*0.8);
	image.setAnchorPercent(0.5, 0.5);
	image.draw(0, 0, imageWidth, imageWidth);

	ofPopMatrix();

	if (animating) {
		ofPushMatrix();
		ofPushStyle();

		imageWidth += ofMap(animLength, 1, 0, 0, ofGetWidth()*0.4);
		ofTranslate(imagePosx, ofGetHeight()*0.8);

		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, ofMap(animLength,1,0,255,0));

		image.draw(0, 0, imageWidth, imageWidth);

		ofDisableAlphaBlending();

		ofPopStyle();
		ofPopMatrix();
	}

}

bool react::amClicked(glm::vec2 _mousePos, int _react) {
	//float imageWidth = ((ofGetWidth()*0.8) / 5) *0.9;
	//float imagePosx = ofGetWidth()*0.11 + (_react * ((ofGetWidth()*0.8) / 5)) + imageWidth;
	//ofTranslate(imagePosx, ofGetHeight()*0.7);

	//std::cout << _react << " : " << ofDist(_mousePos.x, _mousePos.y, imagePosx, ofGetHeight()*0.7) << " : "<< imageWidth << std::endl;

	if (ofDist(_mousePos.x, _mousePos.y, imagePosx, ofGetHeight()*0.8) < imageWidth*0.5) {
		return TRUE;
		//animating = TRUE;
		//std::cout << _react << " : Clicked" << std::endl;
	}
	else {
		return FALSE;
	}

}

void react::clickAnim(glm::vec2 _mousePos, int _react) {
	//float imageWidth = ((ofGetWidth()*0.8) / 5) *0.9;
	//float imagePosx = ofGetWidth()*0.11 + (_react * ((ofGetWidth()*0.8) / 5)) + imageWidth;
	//ofTranslate(imagePosx, ofGetHeight()*0.7);

	//std::cout << _react << " : " << ofDist(_mousePos.x, _mousePos.y, imagePosx, ofGetHeight()*0.7) << " : " << imageWidth << std::endl;

	if (ofDist(_mousePos.x, _mousePos.y, imagePosx, ofGetHeight()*0.8) < imageWidth*0.5) {
		//return TRUE;
		animating = TRUE;
		//std::cout << _react << " : Clicked" << std::endl;
	}
	else {
		//return FALSE;
	}

}
