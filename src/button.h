#pragma once
#include "ofMain.h"

class button {
	public :
		glm::vec2 position;
		glm::vec2 size;
		bool isPressed;
		string title;
		ofTrueTypeFont font;
		button(string _title);
		void draw(glm::vec2 _position, glm::vec2 _size);
		bool mousePressed(int _x, int _y);
		void mouseReleased(int _x, int _y);
		
};