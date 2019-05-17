#include "content.h"

// Class for storing content with relevant data.

// Constructor class
content::content(string _path) {
	importContent(_path);
}

// Import function loads image and data.
void content::importContent(string _path) {
	image.load(_path);
	std::cout << _path << std::endl;
	
	// Path for data is the same path as the image with the extension changed.
	datPath = ofSplitString(_path, ".")[0] + ".txt";

	// If there is a file at the path then import it.
	if (file.open(ofToDataPath(ofSplitString(_path, ".")[0] + ".txt"), ofFile::ReadWrite, false)) {

		std::cout << ofSplitString(_path, ".")[0] + ".txt" << std::endl;
		importSuccess = true;

	}
	else {
		std::cout << "Didn't Work" << std::endl;
		importSuccess = false;
	}

	// Parse the contents of the imported file.
	parseMeta();
}

// Function to parse the imported file.
void content::parseMeta() {
	if (importSuccess) {
		// Load file into buffer.
		ofBuffer buf = file.readToBuffer();
		std::cout << buf.getText() << std::endl;
		string str = buf.getText();

		// Split buffer into variables.
		graph.x = ofToFloat(ofSplitString(str, ",")[0]);
		graph.y = ofToFloat(ofSplitString(str, ",")[1]);

		religeous = ofToFloat(ofSplitString(str, ",")[2]);
		confidence = ofToFloat(ofSplitString(str, ",")[3]);

	}
}

// Draw Content
void content::draw() {
	// Calculate the size and position of the image to keep the aspect ratio correct.
	float imageHeight = ofGetHeight()*0.6;
	float imageRatio = (imageHeight / image.getHeight());
	float imageWidth = image.getWidth()*imageRatio;

	if (imageWidth > ofGetWidth()*0.8) {
		imageWidth = ofGetWidth()*0.8;
		imageRatio = (imageWidth / image.getWidth());
		imageHeight = image.getHeight()*imageRatio;
	}

	// Draw the image
	image.draw((ofGetWidth() -imageWidth)*0.5, ofGetHeight()*0.05, imageWidth, imageHeight);
}