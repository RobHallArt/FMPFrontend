#pragma once
#include "ofMain.h"

class graphInput {
	public :

		glm::vec2 position;
		glm::vec2 size;
		glm::vec2 vecValue;
		float fltValue;
		int mode;
		string title;

		graphInput(glm::vec2 _position, glm::vec2 _size, glm::vec2 _vecValue, string _title);
		graphInput(glm::vec2 _position, glm::vec2 _size, float _fltValue, string _title);
		void draw(glm::vec2 _position, glm::vec2 _size);
		void mousePressed(int _x, int _y);

		
};