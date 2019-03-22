#pragma once
#include "ofMain.h"

class content {
	public :

		string title;
		string desc;
		ofImage image;
		ofVideoPlayer video;
		vector<ofImage> slideshow;

		float controversial;
		float politicalStance;

		content(string _path);

		void importContent(string _path);			// Will have internal string to capture imported metadata for processing.

		void getContentType();

		void parseMeta();

		void draw();

		string getExtFromPath(string _path);
		
		
};