#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    
//    ofSetLogLevel(OF_LOG_VERBOSE);
//    tonecurve.load("null.acv");
    tonecurve.load("contrast.acv");
    
    src.loadImage("lena.jpg");
    tonecurve.apply(src.getPixelsRef(), dst.getPixelsRef());
    dst.update();
}

//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(),2));
}

//--------------------------------------------------------------
void testApp::draw(){
    tonecurve.debugDraw();
    
    ofPushMatrix();
    ofTranslate(0, 255);
    if (ofGetMousePressed()) {
        dst.draw(0, 0);
    } else {
        src.draw(0, 0);
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if( key == 's') {
        ofSaveFrame();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
