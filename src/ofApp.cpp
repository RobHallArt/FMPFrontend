#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//some path, may be absolute or relative to bin/data
	string contentPath = "\content";
	ofDirectory contentDir(contentPath);


	
	//only show png files
	//dir.allowExt("png");
	//populate the directory object
	contentDir.listDir();

	

	//go through and print out all the paths
	for (int i = 0; i < contentDir.size(); i++) {
		if (getExtFromPath(contentDir.getPath(i)) == "jpg" || getExtFromPath(contentDir.getPath(i)) == "png") {
			contents.push_back(content(contentDir.getPath(i)));
		}
		
	}

	for (int i = 0; i < 5; i++) {
		std::cout << ofToString(i) + ".png" << std::endl;
		//ofImage temp;
		//temp.load("reacts/" + ofToString(i) + ".png");
		//temp.setAnchorPercent(temp.getWidth()*0.5, temp.getHeight()*0.5);
		reacts.push_back(react("reacts/" + ofToString(i) + ".png"));
	}

	graphDraw.vecValue = graph;
	religeousSlider.fltValue = religeous;
	confidenceSlider.fltValue = confidence;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < reacts.size(); i++) {
		reacts[i].update(i);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(255);
	contents[contentNum].draw();

	for (int i = 0; i < reacts.size(); i++) {
		reacts[i].draw(i);
	}

	graphDraw.draw(glm::vec2(ofGetWidth()*0.05, ofGetWidth()*0.05), glm::vec2(ofGetWidth()*0.4, ofGetWidth()*0.4));


	religeousSlider.draw(glm::vec2(ofGetWidth()*0.05, ofGetWidth()*0.50), glm::vec2(ofGetWidth()*0.4, ofGetWidth()*0.1));
	confidenceSlider.draw(glm::vec2(ofGetWidth()*0.55, ofGetWidth()*0.50), glm::vec2(ofGetWidth()*0.4, ofGetWidth()*0.1));

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == 's') {
		string save;

		save = ofToString(graph.x);
		save += "," + ofToString(graph.y);

		save += "," + ofToString(religeous);
		//save += "," + ofToString(confidence);

		std::cout << save << std::endl;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){


	if (reacts[0].amClicked(glm::vec2(x, y), 0)) {
		graph.y -= contents[contentNum].graph.y*contents[contentNum].confidence;
		graph.x -= contents[contentNum].graph.x*contents[contentNum].confidence;

		religeous -= contents[contentNum].religeous*contents[contentNum].confidence;
	}
	if (reacts[1].amClicked(glm::vec2(x, y), 0)) {
		graph.y -= contents[contentNum].graph.y*(contents[contentNum].confidence*0.5);
		graph.x -= contents[contentNum].graph.x*(contents[contentNum].confidence*0.5);

		religeous -= contents[contentNum].religeous*(contents[contentNum].confidence*0.5);
	}
	if (reacts[2].amClicked(glm::vec2(x, y), 0)) {
		// Do nothing cause indifferent
	}
	if (reacts[3].amClicked(glm::vec2(x, y), 0)) {
		graph.y += contents[contentNum].graph.y*(contents[contentNum].confidence*0.5);
		graph.x += contents[contentNum].graph.x*(contents[contentNum].confidence*0.5);

		religeous += contents[contentNum].religeous*(contents[contentNum].confidence*0.5);
	}
	if (reacts[4].amClicked(glm::vec2(x, y), 0)) {
		graph.y += contents[contentNum].graph.y*contents[contentNum].confidence;
		graph.x += contents[contentNum].graph.x*(contents[contentNum].confidence*0.5);

		religeous += contents[contentNum].religeous*contents[contentNum].confidence;
	}


	for (int i = 0; i < reacts.size(); i++) {
		reacts[i].clickAnim(glm::vec2(x, y), i);
		if (reacts[i].amClicked(glm::vec2(x, y), i)) {

			if (contentNum < contents.size() - 1) {
				contentNum++;
			}
			else {
				contentNum = 0;
			}
		}
	}


	
	if (graph.x > 1) {
		graph.x = 1;
	}
	if (graph.y > 1) {
		graph.y = 1;
	}
	if (graph.x < -1) {
		graph.x = -1;
	}
	if (graph.y < -1) {
		graph.y = -1;
	}
	if (religeous > 1) {
		religeous = 1;
	}
	if (religeous < 0) {
		religeous = 0;
	}

	graphDraw.vecValue = graph;
	religeousSlider.fltValue = religeous;
	confidenceSlider.fltValue = confidence;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

string ofApp::getExtFromPath(string _path) {
	if (ofSplitString(_path, ".").size() > 0) {
		string ret = ofSplitString(_path, ".")[1];
		return ret;
		std::cout << ret << std::endl;
	}
	else {
		return ".NaN";
	}
}