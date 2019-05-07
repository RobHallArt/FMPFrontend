#pragma once

#include "ofMain.h"
#include "content.h"
#include "react.h"
#include "graphInput.h"
#include "animator.h"
#include "button.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void setLighting(int channel, int value);
		void printGraph();

		vector<content>contents;
		int contentNum;
		int programMode;
		int lightingMode;
		bool debug;
		bool verbose;
		vector<ofImage> menus;

		int timer;

		glm::vec2 graph;

		float religeous;
		float confidence;

		button end{ "End Experience" };
		button playOn{ "Target Me!" };

		vector<react> reacts;

		ofImage angryReact;

		string getExtFromPath(string _path);

		graphInput graphDraw{ glm::vec2(ofGetWidth()*0.05, ofGetWidth()*0.05), glm::vec2(ofGetWidth()*0.4,ofGetWidth()*0.4), glm::vec2(0,0), "Political Compass" };
		graphInput religeousSlider{ glm::vec2(ofGetWidth()*0.05, ofGetWidth()*0.55), glm::vec2(ofGetWidth()*0.4,ofGetWidth()*0.1), 0, "Religeous Slider" };
		graphInput confidenceSlider{ glm::vec2(ofGetWidth()*0.55, ofGetWidth()*0.55), glm::vec2(ofGetWidth()*0.4,ofGetWidth()*0.1), 0, "Confidence Slider" };
};
