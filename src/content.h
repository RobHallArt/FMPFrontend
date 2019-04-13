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

		glm::vec2 social;
		glm::vec2 econ;

		float religeous;
		float confidence;

		content(string _path);

		void importContent(string _path);			// Will have internal string to capture imported metadata for processing.

		void getContentType();

		void parseMeta();

		void draw();

		string getExtFromPath(string _path);

		
		
};