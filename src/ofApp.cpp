#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Set Up ArtNet Sender - Last byte set to 255 to broadcast to every ArtNet node on subnet.
	artnet.setup("10.193.28.255", 0);
	// Allocate 10 mono pixels which represent dmx channels.
	data.allocate(10, 1, OF_PIXELS_MONO);

	// Set all the channels to 0.
	for (int i = 0; i < data.getWidth(); i++) {
		data[i] = 0;
	}

	// Set which channel is used for the air cannon and the lighting.
	lightingShootChannel = 1;
	lightingModeChannel = 6;

	// Set variable defaults.
	programMode = 0;
	timer = 0;
	timer2 = 0;
	debug = false;
	verbose = false;

	// Set the relevant channels to the default value.
	setLighting(lightingShootChannel, 0);
	setLighting(lightingModeChannel, 0);

	// Set up the directory to look in for content.
	string contentPath = "\content";
	ofDirectory contentDir(contentPath);
	contentDir.listDir();

	// Load the image with the receipt template.
	receipt.load("Receipt_Template.png");
	
	// Load menus into menu array.
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


	// Loop through content and add it to content array.
	for (int i = 0; i < contentDir.size(); i++) {
		// Check if content is an image.
		if (getExtFromPath(contentDir.getPath(i)) == "jpg" || getExtFromPath(contentDir.getPath(i)) == "png") {
			// Push content into array.
			contents.push_back(content(contentDir.getPath(i)));
		}
		
	}

	// Loop through reacts.
	for (int i = 0; i < 5; i++) {
		// Push back reacts into array.
		if (debug) { std::cout << ofToString(i) + ".png" << std::endl; }
		reacts.push_back(react("reacts/" + ofToString(i) + ".png"));
	}

	// Reset graphs drawn when debugging.
	graphDraw.vecValue = graph;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	// Update animation of reacts.
	for (int i = 0; i < reacts.size(); i++) {
		reacts[i].update(i);
	}

	// Update timers.
	if (timer <= 0) {
		timer = 0;
	}
	else {
		timer--;
		if (debug) { std::cout << "Timer : " << timer << std::endl; }
	}
	if (timer2 <= 0) {
		timer2 = 0;
	}
	else {
		timer2--;
		if (debug) { std::cout << "Timer2 : " << timer2 << std::endl; }
	}

	// Check timers and update program and ArtNet DMX signals accordingly.
	if (timer == 0 && programMode == 5) {
		programMode = 6;
		setLighting(lightingModeChannel, 75);
		timer = 300;
	}

	if (timer == 0 && programMode == 7) {
		programMode = 8;
	}

	if (timer == 0 && programMode == 6) {
		programMode = 10;
		timer = 500;
		setLighting(lightingShootChannel, 250);
		setLighting(lightingModeChannel, 145);
		timer2 = 60;
	}

	if (timer == 0 && programMode == 10) {
		programMode = 0;
		setLighting(lightingModeChannel, 45);
	}

	if (timer2 == 0 && programMode == 10) {
		setLighting(lightingShootChannel, 0);
		setLighting(lightingModeChannel, 0);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	// Set fallback background to represent Facebook background colour.
	ofSetBackgroundColor(247,247,247);

	// Draw different scenes based on programMode. Now I read it this could have been a switch statement just as easily.

	// Title Card
	if (programMode == 0) {
		menus[0].draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	// Reacting to content
	if (programMode == 3) {
		contents[contentNum].draw();

		for (int i = 0; i < reacts.size(); i++) {
			reacts[i].draw(i);
		}

		// If the debug flag is true, draw graphs over the top to make sure reactions are doing the right thing to the rating of the user.
		if (debug) {
			graphDraw.draw(glm::vec2(ofGetWidth()*0.05, ofGetWidth()*0.05), glm::vec2(ofGetWidth()*0.4, ofGetWidth()*0.4));
		}

	}

	// You have met the criteria of the intended demographic
	if (programMode == 5) {
		menus[1].draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	// You have not met the criteria of the intended deomgraphic.
	if (programMode == 7){
		menus[3].draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	// You have been targeted (Background fades to red based on timer).
	if (programMode == 6) {
		ofSetBackgroundColor(247, ofMap(timer, 300, 0, 247, 0), ofMap(timer, 300, 0, 247, 0));
		ofSetColor(255);
		menus[2].draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	// Do you want to experience targeting? Buttons are drawn to pick.
	if (programMode == 8) {
		menus[4].draw(0, 0, ofGetWidth(), ofGetHeight());
		end.draw(glm::vec2(ofGetWidth()*0.2, ofGetHeight()*0.7),glm::vec2(ofGetWidth()*0.2,ofGetHeight()*0.2));
		playOn.draw(glm::vec2(ofGetWidth()*0.6, ofGetHeight()*0.7), glm::vec2(ofGetWidth()*0.2, ofGetHeight()*0.2));
	}

	// End of Program (Black Screen)
	if (programMode == 10) {
		ofSetBackgroundColor(0);
	}

	// If debugging, draw programMode in top left of display.
	if (debug) {
		ofPushStyle();
		ofSetColor(255, 0, 0);
		ofDrawBitmapString(programMode, 100, 100);
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// Debugging Tools
	if (debug) {

		// If key S is pressed print out values from user political graph to console.
		if (key == 's') {
			string save;

			save = ofToString(graph.x);
			save += "," + ofToString(graph.y);

			save += "," + ofToString(religeous);
			//save += "," + ofToString(confidence);

			std::cout << save << std::endl;
		}

		// If B key pressed run printer code.
		if (key == 'b') {
			printGraph();
		}
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

	// If statements for checking touch events.

	// If programMode is 0 (Welcome Screen) a touch anywhere will skip to programMode 3 (Reacting) 
	if (programMode == 0) {
		programMode = 3;
	}

	// If programMode is 3 (Reacting) listen for clicked reacts and make appropriate adjustments to graph.
	if (programMode == 3) {
		// Angry Clicked
		if (reacts[0].amClicked(glm::vec2(x, y), 0)) {
			graph.y -= contents[contentNum].graph.y*contents[contentNum].confidence;
			graph.x -= contents[contentNum].graph.x*contents[contentNum].confidence;

			religeous -= contents[contentNum].religeous*contents[contentNum].confidence;
		}
		// Sad Clicked
		if (reacts[1].amClicked(glm::vec2(x, y), 0)) {
			graph.y -= contents[contentNum].graph.y*(contents[contentNum].confidence*0.5);
			graph.x -= contents[contentNum].graph.x*(contents[contentNum].confidence*0.5);

			religeous -= contents[contentNum].religeous*(contents[contentNum].confidence*0.5);
		}
		// Indifferent Clicked
		if (reacts[2].amClicked(glm::vec2(x, y), 0)) {
			// Do nothing cause indifferent
		}
		// Like Clicked
		if (reacts[3].amClicked(glm::vec2(x, y), 0)) {
			graph.y += contents[contentNum].graph.y*(contents[contentNum].confidence*0.5);
			graph.x += contents[contentNum].graph.x*(contents[contentNum].confidence*0.5);

			religeous += contents[contentNum].religeous*(contents[contentNum].confidence*0.5);
		}
		// Love Clicked
		if (reacts[4].amClicked(glm::vec2(x, y), 0)) {
			graph.y += contents[contentNum].graph.y*contents[contentNum].confidence;
			graph.x += contents[contentNum].graph.x*(contents[contentNum].confidence*0.5);

			religeous += contents[contentNum].religeous*contents[contentNum].confidence;
		}

		// Keep point from leaving graph.
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

		// Loop through reacts.
		for (int i = 0; i < reacts.size(); i++) {
			// Start animating.
			reacts[i].clickAnim(glm::vec2(x, y), i);
			// On click of react.
			if (reacts[i].amClicked(glm::vec2(x, y), i)) {
				// If more content exists go onto next piece.
				if (contentNum < contents.size() - 1) {
					contentNum++;
					if (verbose) { std::cout << glm::distance(graphDraw.vecValue, glm::vec2(0, 0)) << std::endl; }
				}
				else {
					// Otherwise reset contentNum for the next user of the program.
					contentNum = 0;
					
					// Check if user is in target region and change to relevant programMode, run receipt printer code and set timers and lighting states as required.
					if (glm::distance(graph, glm::vec2(0, 0)) <0.5) {
						printGraph();
						programMode = 5;
						timer = 200;
					}
					else {
						printGraph();
						setLighting(lightingModeChannel, 105);
						programMode = 7;
						timer = 200;
					}

					// Reset user graph for next user.
					graph = glm::vec2(0, 0);
				}
			}
		}
		
		// Update debug graph.
		graphDraw.vecValue = graph;
	}

	// Listen for buttons on the screen where you can decide to be targeted or not.
	if (programMode == 8) {
		// If the end button is clicked, turn off the lights and skip to the end of the program.
		if (end.mousePressed(x, y)) {
			programMode = 10;
			setLighting(lightingModeChannel, 0);
			timer = 500;
		}
		// If the target me button is clicked, set lights to red and skip to the targeted page. 
		if (playOn.mousePressed(x, y)) {
			programMode = 6;
			setLighting(lightingModeChannel, 75);
			timer = 300;
		}
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	// Run code to make buttons work better on touch screen.
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

// Custom extra functions.

// Get the file extension from a path or filename.
string ofApp::getExtFromPath(string _path) {
	// If string can be split by '.'
	if (ofSplitString(_path, ".").size() > 0) {
		// Return the part after the '.'
		string ret = ofSplitString(_path, ".")[1];
		return ret;
		if (verbose) { std::cout << ret << std::endl; }
	}
	else {
		return ".NaN";
	}
}

// Simplified ArtNet Sender to single command.
void ofApp::setLighting(int channel, int value) {
	if (channel >= 1) {
		data[channel - 1] = value;
	}
	else {
		std::cout << "DMX CHANNEL OUT OF RANGE" << std::endl;
	}

	artnet.sendArtnet(data);
}

// Receipt Printer code.
void ofApp::printGraph() {
	// This draws everything that prints on screen for one frame.
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

	// It is then saves that section of the screen to a file.
	printImage.grabScreen(0, 0, 200, 600);
	printImage.save("output.png");

	// Finally it runs a system command which prints the file from the command line.
	system("printOutput.bat");

	ofPopMatrix();
	ofPopStyle();
}