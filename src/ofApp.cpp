#include "ofApp.h"
#include "ofxRealsense.h"

//--------------------------------------------------------------
void ofApp::setup() {
	vector<string> serials = ofxRealsense::get_serials();
	cout << "Connected RealSense devices:" << endl;
	for (int i = 0; i < serials.size(); i++) {
		cout << i + 1 << ":\t" << serials[i] << endl;
	}
	if (serials.size() == 0) {
		cout << "No connected RealSense devices!" << endl;
	}
	else {
		/*
		See available resolutions and framerates at ofxRealsense.h comments
		*/
		ofxRealsense_Settings S;
		S.depth_w = mainWidth;
		S.depth_h = mainHeight;
		S.depth_fps = 30;
		S.rgb_w = mainWidth;
		S.rgb_h = mainHeight;
		S.rgb_fps = 30;


		device_.setup(serials[0], S);
	}

	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	for (int i = 0; i < mainWidth; i += 1) {
		for (int j = 0; j < mainHeight; j += 1) {
			mesh.addVertex(ofPoint(i, j));
		}
	}

	//for (int i = 0; i < mainWidth - 1; i += 1) {
		//for (int j = 0; j < mainHeight - 1; j += 1) {
			//mesh.addIndex(j + 1);
			//mesh.addIndex((i + 1) + j * mainWidth);
			//mesh.addIndex(i + (j + 1) * mainWidth);
			//mesh.addIndex((i + 1) + j * mainWidth);
			//mesh.addIndex((i + 1) + (j + 1) * mainWidth);
			//mesh.addIndex(i + (j + 1) * mainWidth);
		//}
	//}

	//cam.tilt(180);
	//cam.setPosition(-500, 0, 0);

	//CALIBRATION
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
	device_.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);

	//if (draw_textures) {
	//	ofTexture texture;
	//	ofPixels pix;
	//	int x = 0;
	//	float scale = 1;
	//	vector<float> data;
	//	if (device_.connected()) {
	//		cam.begin();
	//		device_.get_depth_pixels_mm(mainWidth, mainHeight, data);
	//		device_.get_depth_texture(texture);
	//		ofSetColor(255);
	//		texture.readToPixels(pix);
	//		int count = 0;
	//		for (int i = 0; i < mainWidth; i+=1) {
	//			for (int j = 0; j < mainHeight; j+=1) {
	//				ofColor c = pix.getColor(i, j);
	//				ofVec3f position = mesh.getVertex(count);
	//				position.x = i;
	//				position.y = j;
	//				position.z = (c.r + c.b + c.g) / 3;
	//				mesh.setVertex(count, position);
	//				count++;
	//			}
	//		}
	//		ofSetColor(255);
	//		mesh.drawWireframe();
	//		cam.end();
	//	}
	//}

	if (draw_textures) {
		ofTexture texture;
		ofPixels pix;
		vector<float> data;
		if (device_.connected()) {
			device_.get_depth_pixels_mm(mainWidth, mainHeight, data);
			device_.get_depth_texture(texture);


			vector<glm::vec3>& pc = mesh.getVertices();


			device_.get_point_cloud(pc);


			//for (int i = 0; i < pc.size(); i++) {
				//float x = ofMap(pc[i].x, mainWidth, 0, 0 - TLCalibration.x, ofGetWidth() + BRCalibration.x);
				//float y = ofMap(pc[i].y, mainHeight, 0, 0 - TLCalibration.y, ofGetHeight() + BRCalibration.y);

				//ofColor blue = ofColor::fromHsb(170, ofMap(pc[i].z, 0, 3000, 0, 255), 255);
				//ofSetColor(blue);


			
			//}


			//for (int i = 1; i < mainWidth; i += 5) {
			//	for (int j = 0; j < mainHeight; j += 5) {

			//		int pos = (((i - 1) * mainHeight) + i);



			//		float size = ofMap(pc[pos].z, 500, 3000, 0, 10);

			//		ofDrawCircle(x, y, size);
			//	}
			//}

			ofSetColor(255);
			//texture.draw(0, 0, ofGetWidth(), ofGetHeight());
			//texture.readToPixels(pix);
			//int skip = 5;
			//for (int k = 0; k < data.size(); k+=skip) {
			//	if (k == 0) {
			//		y = 0;
			//		x = 0;
			//	}
			//	if (x >= 640) {
			//		y++;
			//		x = 0;
			//	}
			//	x+=skip;

			//	float m_x = ofMap(x, mainWidth, 0, 0 - TLCalibration.x, ofGetWidth() + BRCalibration.x);
			//	float m_y = ofMap(y, mainHeight, 0, 0 - TLCalibration.y, ofGetHeight() + BRCalibration.y);

			//	ofColor blue = ofColor::fromHsb(170, ofMap(data[k], 0, 4000, 0, 255), 255);
			//	ofSetColor(blue);

			//	ofDrawCircle(x, y, 4);
			//	
			//}

			for (int y = 0; y < mainHeight; y += 5) {
				for (int x = 0; x < mainWidth; x += 5) {
					int index = y * mainWidth + x;
					ofColor blue = ofColor::fromHsb(170, ofMap(data[index], 0, 4000, 0, 255), 255);
					ofSetColor(blue);
					ofDrawCircle(x, y, 2);
				}
			}

			//for (int i = 1; i < mainWidth; i += 1) {
			//	for (int j = 1; j < mainHeight; j += 1) {

			////		//CURRENTLY FLIPPED
			//		//float x = ofMap(i, mainWidth, 0, 0 - TLCalibration.x, ofGetWidth() + BRCalibration.x);
			//		//float y = ofMap(j, mainHeight, 0, 0 - TLCalibration.y, ofGetHeight() + BRCalibration.y);

			//		float x = i;
			//		float y = j;

			//		int dataPosition = (((i - 1) * mainHeight) + i);
			//		
			//		ofColor blue = ofColor::fromHsb(170, ofMap(data[dataPosition], 0, 4000, 0, 255), 255);
			//		ofSetColor(blue);
			//		ofDrawCircle(x, y, 2);

			//	}
			//}
			//ofSetColor(255);
		}


	}
	//if (draw_points) {
	//	ofMesh mesh;
	//	cam.begin();

	//	ofPushMatrix();
	//	ofScale(0.1, -0.1, 0.1);

	//	if (device_.connected()) {
	//		vector<glm::vec3>& pc = mesh.getVertices();
	//		device_.get_point_cloud(pc);

	//		ofSetColor(255, 0, 0);
	//		mesh.drawVertices();
	//	}
	//	ofPopMatrix();
	//	cam.end();
	//}

	ofDrawBitmapStringHighlight("FPS: " + ofToString(ofGetFrameRate(), 0), 20, 20);
	ofDrawBitmapStringHighlight("x1: " + ofToString(x1, 0), 20, 50);
	ofDrawBitmapStringHighlight("y1: " + ofToString(y1, 0), 20, 80);
	ofDrawBitmapStringHighlight("x2: " + ofToString(x2, 0), 20, 110);
	ofDrawBitmapStringHighlight("y2: " + ofToString(y2, 0), 20, 140);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') draw_textures = !draw_textures;
	//if (key == '2') draw_points = !draw_points;

	//SET CALIBRATION
	if (key == '3') {
		TLCalibration.set(x1, y1);
		BRCalibration.set(x2, y2);
	}

	//RESET CALIBRATION
	if (key == '4') {
		TLCalibration.set(0, 0);
		BRCalibration.set(0, 0);
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
	}

	//RESET CALIBRATION
	if (key == 'q') {x1 += 10;}
	if (key == 'a') { x1 -= 10;}

	if (key == 'w') { y1 += 10;}
	if (key == 's') { y1 -= 10;}

	if (key == 'e') { x2 += 10; }
	if (key == 'd') { x2 -= 10; }

	if (key == 'r') { y2 += 10; }
	if (key == 'f') { y2 -= 10; }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	x1 = x;
	y1 = y;
	ofLog() << "position 1 - " << x << " -  " << y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	x2 = x;
	y2 = y;
	ofLog() << "position 2 - " << x << " - " << y;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
