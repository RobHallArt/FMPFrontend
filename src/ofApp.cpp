#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//some path, may be absolute or relative to bin/data
	artnet.setup("192.168.1.255", 0);
	data.allocate(10, 1, OF_PIXELS_MONO);
	for (int i = 0; i < data.getWidth(); i++) {
		data[i] = 0;
	}

	lightingShootChannel = 1;
	lightingFadeChannel = 3;
	lightingModeChannel = 4;

	setLighting(lightingShootChannel, 0);
	setLighting(lightingFadeChannel, 3);
	setLighting(lightingModeChannel, 1);

	string contentPath = "\content";
	ofDirectory contentDir(contentPath);
	programMode = 0;
	timer = 0;
	timer2 = 0;
	debug = true;
	verbose = false;

	receipt.load("Receipt_Template.png");
	
	//only show png files
	//dir.allowExt("png");
	//populate the directory object
	contentDir.listDir();
	ofImage temp;
	temp.loadImage("menus/TitleCard.png");
	menus.push_back(temp);
	temp.loadImage("menus/MenuSystem-01.png");
	menus.push_back(temp);
	temp.loadImage("menus/MenuSystem-02.png");
	menus.push_back(temp);
	temp.loadImage("menus/MenuSystem-03.png");
	menus.push_back(temp);
	temp.loadImage("menus/MenuSystem-04.png");
	menus.push_back(temp);


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
	//std::cout << ofGetElapsedTimeMillis() << std::endl;
	
	for (int i = 0; i < reacts.size(); i++) {
		reacts[i].update(i);
	}
	if (timer <= 0) {
		timer = 0;
	}
	else {
		timer--;
		std::cout << "Timer : " << timer << std::endl;
	}

	if (timer2 <= 0) {
		timer2 = 0;
	}
	else {
		timer2--;
		std::cout << "Timer2 : " << timer2 << std::endl;
	}

	if (timer == 0 && programMode == 5) {
		programMode = 6;
		timer = 300;
	}

	if (timer == 0 && programMode == 7) {
		programMode = 8;
	}

	if (timer == 0 && programMode == 6) {
		programMode = 10;
		timer = 2000;
		setLighting(lightingShootChannel, 250);
		timer2 = 60;
	}

	if (timer == 0 && programMode == 10) {
		programMode = 0;
	}

	if (timer2 == 0 && programMode == 10) {
		setLighting(lightingShootChannel, 0);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(247,247,247);
	if (programMode == 0) {
		menus[0].draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	if (programMode == 3) {
		contents[contentNum].draw();

		for (int i = 0; i < reacts.size(); i++) {
			reacts[i].draw(i);
		}

		if (debug) {
			graphDraw.draw(glm::vec2(ofGetWidth()*0.05, ofGetWidth()*0.05), glm::vec2(ofGetWidth()*0.4, ofGetWidth()*0.4));
			religeousSlider.draw(glm::vec2(ofGetWidth()*0.05, ofGetWidth()*0.50), glm::vec2(ofGetWidth()*0.4, ofGetWidth()*0.1));
			confidenceSlider.draw(glm::vec2(ofGetWidth()*0.55, ofGetWidth()*0.50), glm::vec2(ofGetWidth()*0.4, ofGetWidth()*0.1));
		}

	}

	if (programMode == 5) {
		menus[1].draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	if (programMode == 7){
		menus[3].draw(0, 0, ofGetWidth(), ofGetHeight());

	}

	if (programMode == 6) {
		ofSetBackgroundColor(247, ofMap(timer, 300, 0, 247, 0), ofMap(timer, 300, 0, 247, 0));
		ofSetColor(255);
		menus[2].draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	if (programMode == 8) {
		menus[4].draw(0, 0, ofGetWidth(), ofGetHeight());
		end.draw(glm::vec2(ofGetWidth()*0.2, ofGetHeight()*0.7),glm::vec2(ofGetWidth()*0.2,ofGetHeight()*0.2));
		playOn.draw(glm::vec2(ofGetWidth()*0.6, ofGetHeight()*0.7), glm::vec2(ofGetWidth()*0.2, ofGetHeight()*0.2));
	}

	if (programMode == 10) {
		ofSetBackgroundColor(0);
	}

	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(programMode, 100, 100);
	ofPopStyle();
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

	if (key == 'b') {
		printGraph();
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
	if (programMode == 0) {
		programMode = 3;
	}

	if (programMode == 3) {
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

		for (int i = 0; i < reacts.size(); i++) {
			reacts[i].clickAnim(glm::vec2(x, y), i);
			if (reacts[i].amClicked(glm::vec2(x, y), i)) {

				if (contentNum < contents.size() - 1) {
					contentNum++;
					if (verbose) { std::cout << glm::distance(graphDraw.vecValue, glm::vec2(0, 0)) << std::endl; }
				}
				else {

					programMode = 5;
					contentNum = 0;
					

					if (glm::distance(graph, glm::vec2(0, 0)) <0.5) {
						printGraph();
						programMode = 5;
						timer = 200;
					}
					else {
						printGraph();
						programMode = 7;
						timer = 200;
					}

					graph = glm::vec2(0, 0);
				}
			}
		}

		graphDraw.vecValue = graph;
		religeousSlider.fltValue = religeous;
		confidenceSlider.fltValue = confidence;
	}

	if (programMode == 8) {
		if (end.mousePressed(x, y)) {
			programMode = 10;
			timer = 2000;
		}
	
		if (playOn.mousePressed(x, y)) {
			programMode = 6;
			timer = 300;
		}
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	end.mouseReleased(x, y);
	playOn.mouseReleased(x, y);
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

void ofApp::setLighting(int channel, int value) {
	if (channel >= 1) {
		data[channel - 1] = value;
	}
	else {
		std::cout << "DMX CHANNEL OUT OF RANGE" << std::endl;
	}

	artnet.sendArtnet(data);
}

void ofApp::printGraph() {
	ofPushMatrix();
	ofPushStyle();
	ofSetColor(255);
	ofDrawRectangle(0,0,200,600);
	receipt.draw(0, 0, 200, 600);
	ofSetColor(0);
	ofPushMatrix();
	ofTranslate(25, 75);
	ofDrawLine(75, 0, 75, 150);
	ofDrawLine(0, 75, 150, 75);
	ofPushMatrix();
	ofTranslate(75, 75);
	ofTranslate(ofMap(graph.x, -1, 1, -75, 75), ofMap(graph.y, -1, 1, -75, 75));
	ofDrawEllipse(0, 0, 10, 10);
	ofPopMatrix();
	ofPopMatrix();

	printImage.grabScreen(0, 0, 200, 600);
	printImage.save("output.png");

	system("printOutput.bat");

	ofPopMatrix();
	ofPopStyle();
}