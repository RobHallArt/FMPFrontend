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

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

	for (int i = 0; i < reacts.size(); i++) {
		reacts[i].clickAnim(glm::vec2(x, y), i);
		if (reacts[i].amClicked(glm::vec2(x, y), i)) {


			string save;

			save = ofToString(contents[contentNum].social.x);
			save += "," + ofToString(contents[contentNum].social.y);

			save += "," + ofToString(contents[contentNum].econ.x);
			save += "," + ofToString(contents[contentNum].econ.y);

			save += "," + ofToString(contents[contentNum].religeous);
			save += "," + ofToString(contents[contentNum].confidence);

			std::cout << save << std::endl;



			if (contentNum < contents.size() - 1) {
				contentNum++;
			}
			else {
				contentNum = 0;
			}
		}
	}
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