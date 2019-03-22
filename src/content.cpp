#include "content.h"

content::content(string _path) {
	importContent(_path);
}

void content::importContent(string _path) {
	if (getExtFromPath(_path) == "jpg") {
		image.load(_path);
	}
	if (getExtFromPath(_path) == "png") {
		image.load(_path);
	}
}

void content::getContentType() {

}

void content::parseMeta() {

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