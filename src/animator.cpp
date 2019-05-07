#include "animator.h"


// Animator Constructor with low and high declared
animator::animator(float _fadeTime, int _loopMode, float _low, float _high, char _activateKey) {
	fadeTime = _fadeTime;
	loopMode = _loopMode;
	activateKey = _activateKey;
	low = _low;
	high = _high;
	value = low;
	isAnimating = FALSE;
	loopModeDirection = TRUE;
}

// Animator Constructor with low and high declared
animator::animator(float _fadeTime, int _loopMode, float _low, float _high) {
	fadeTime = _fadeTime;
	loopMode = _loopMode;
	low = _low;
	high = _high;
	value = low;
	isAnimating = FALSE;
	loopModeDirection = TRUE;
}

// Animator Constructor with low and high set to defaults
animator::animator(float _fadeTime, int _loopMode, char _activateKey) {
	fadeTime = _fadeTime;
	loopMode = _loopMode;
	activateKey = _activateKey;
	low = 0;
	high = 1;
	value = low;
	isAnimating = FALSE;
	loopModeDirection = TRUE;
}


void animator::update() {
	// If time since start is more than fade time stop animating and swap direction if in second mode
	if (ofGetElapsedTimeMillis() - startTime >= fadeTime && isAnimating) {

		isAnimating = FALSE;
		loopModeDirection = !loopModeDirection;
	}
	// If animating and map between low and high based on time since start time
	if (isAnimating && loopMode == 1) {
		
		value = ofMap(ofGetElapsedTimeMillis() - startTime, 0, fadeTime, low, high);

		//std::cout << "animating : " << value<<std::endl; // Uncomment to print while animating
	}
	// If second mode, animate in different opposite directions each time
	else if (isAnimating && loopMode == 2) {
		if (loopModeDirection) {
			value = ofMap(ofGetElapsedTimeMillis() - startTime, 0, fadeTime, low, high);
		}
		else {
			value = ofMap(ofGetElapsedTimeMillis() - startTime, 0, fadeTime, high, low);
		}
	}
}

void animator::trigger(char _keyPressed) {
	// If key pressed is the one we set earlier set animating and set startTime to current time
	if (_keyPressed == activateKey) {
		isAnimating = TRUE;
		startTime = ofGetElapsedTimeMillis();
	}
}

void animator::trigger() {
	isAnimating = TRUE;
	startTime = ofGetElapsedTimeMillis();
}