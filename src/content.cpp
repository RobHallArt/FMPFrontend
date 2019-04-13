#include "content.h"

content::content(string _path) {
	importContent(_path);
}

void content::importContent(string _path) {
	image.load(_path);
	std::cout << _path << std::endl;

	datPath = ofSplitString(_path, ".")[0] + ".txt";

	if (file.open(ofToDataPath(ofSplitString(_path, ".")[0] + ".txt"), ofFile::ReadWrite, false)) {

		std::cout << ofSplitString(_path, ".")[0] + ".txt" << std::endl;
		importSuccess = true;

	}
	else {
		std::cout << "Didn't Work" << std::endl;
		//file.create();
		importSuccess = false;
	}

	parseMeta();
}

void content::getContentType() {

}

void content::parseMeta() {
	if (importSuccess) {

		ofBuffer buf = file.readToBuffer();
		std::cout << buf.getText() << std::endl;
		string str = buf.getText();

		social.x = ofToFloat(ofSplitString(str, ",")[0]);
		social.y = ofToFloat(ofSplitString(str, ",")[1]);

		econ.x = ofToFloat(ofSplitString(str, ",")[2]);
		econ.y = ofToFloat(ofSplitString(str, ",")[3]);

		religeous = ofToFloat(ofSplitString(str, ",")[4]);
		confidence = ofToFloat(ofSplitString(str, ",")[5]);

	}
}

void content::draw() {

	float imageHeight = ofGetHeight()*0.6;
	float imageRatio = (imageHeight / image.getHeight());
	float imageWidth = image.getWidth()*imageRatio;

	if (imageWidth > ofGetWidth()*0.8) {
		imageWidth = ofGetWidth()*0.8;
		imageRatio = (imageWidth / image.getWidth());
		imageHeight = image.getHeight()*imageRatio;
	}

	image.draw((ofGetWidth() -imageWidth)*0.5, ofGetHeight()*0.05, imageWidth, imageHeight);
}

string content::getExtFromPath(string _path) {
	if (ofSplitString(_path, ".").size()>0) {
		string ret = ofSplitString(_path, ".")[1];
		return ret;
		std::cout << ret << std::endl;
	}
	else {
		string ret = "png";
		return ret;
	}
}