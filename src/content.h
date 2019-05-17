#pragma once
#include "ofMain.h"

class content {
	public :

		string title;
		string desc;
		ofImage image;
		ofVideoPlayer video;
		vector<ofImage> slideshow;

		bool importSuccess;

		string path;
		string datPath;

		ofFile file;

		glm::vec2 graph;


		float religeous;
		float confidence;

		content(string _path);

		void importContent(string _path);			// Will have internal string to capture imported metadata for processing.


		void parseMeta();

		void draw();

		
		
};