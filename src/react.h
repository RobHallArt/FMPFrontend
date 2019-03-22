#pragma once
#include "ofMain.h"

class react {
	public :

		ofImage image;
		float animLength;

		bool animating;

		react(string _path);

		void update(int _react);

		void draw(int _react);

		bool amClicked(glm::vec2 _mousePos, int _react);
		void clickAnim(glm::vec2 _mousePos, int _react);

		float imageWidth;
		float imagePosx;
		
		
};