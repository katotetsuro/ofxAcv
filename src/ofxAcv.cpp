//
//  ofxAcv.cpp
//
//  Created by Tetsuro Kato on 3/28/14.
//
//

#include "ofxAcv.h"

const string ofxAcv::tag = "ofxAcv";

ofxAcv::ofxAcv() : loaded(false) {
    
}

ofxAcv::~ofxAcv() {
    
}

bool ofxAcv::load(string file) {
    ifstream ifs(ofToDataPath(file).c_str(), ios::in | ios::binary);
    
    unsigned short s;
    
    ifs.read((char*)&s, sizeof(unsigned short)/2);
    cout << "いらない:" << s << endl;
    
    ifs.read((char*)&s, sizeof(unsigned short));
    cout << "Version: たぶん4:" << s << endl;
    
    ifs.read((char*)&s, sizeof(unsigned short));
    cout << "count of curves in file:" << s << endl;
    
    int numCurve = static_cast<int>(s);
    
    curves.clear();
    for (int i=0; i<numCurve; ++i) {
        ifs.read((char*)&s, sizeof(unsigned short));
        int numPoints = static_cast<int>(s);
        cout << "line number " << (i+1) << " has " << numPoints << " points." << endl;
        CurveLut curve;
        curve.setup();
        for (int j=0; j<numPoints; ++j) {
            ifs.read((char*)&s, sizeof(unsigned short));
            int output = static_cast<int>(s);
            ifs.read((char*)&s, sizeof(unsigned short));
            int input = static_cast<int>(s);
            cout << "mapping " << input << " -> " << output << endl;
            
            // (0,0) and (255,255) are added at CurveLut::setup()
            if ((input==0 && output==0) || (input==255&&output==255)) {
                continue;
            }
            curve.add(ofVec2f(input, output));
        }
        curve.update();
        curves.push_back(curve);
    }
    loaded = true;
}

void ofxAcv::apply(const ofPixelsRef src, ofPixelsRef dst) {
    if (src.getWidth() != dst.getWidth()
        || src.getHeight() != dst.getHeight()
        || src.getNumChannels() != dst.getNumChannels()) {
        ofLogNotice() << "reallocating dst";
        dst.allocate(src.getWidth(), src.getHeight(), src.getNumChannels());
    }
    int w = src.getWidth();
    int h = src.getHeight();
    int ch = src.getNumChannels();
    assert(ch <= curves.size());
    unsigned char* srcPixels = src.getPixels();
    unsigned char* dstPixels = dst.getPixels();
    
    for (int y=0; y<h; ++y) {
        for (int x=0; x<w; ++x) {
            for (int c=0; c<ch; ++c) {
                int idx = (y * w + x) * ch + c;
                dstPixels[idx] = curves[c][srcPixels[idx]];
            }
        }
    }
}

void setColor(int curveIndex) {
    switch (curveIndex) {
        case 0:
            ofSetColor(ofColor::black);
            break;
            
        case 1:
            ofSetColor(ofColor::red);
            break;
            
        case 2:
            ofSetColor(ofColor::green);
            break;
            
        case 3:
            ofSetColor(ofColor::blue);
            break;
            
        case 4:
            ofSetColor(ofColor::gray);
            break;
            
        default:
            ofSetColor(ofColor::fromHsb(curveIndex*10/255, 255, 255));
            break;
    }
}

void ofxAcv::debugDraw() {
    ofPushMatrix();
    ofTranslate(0, 255);
    ofScale(1, -1);
    ofPushStyle();
    int numCurve = curves.size();
    for (int i=0; i<numCurve; ++i) {
        ofSetColor(ofColor::fromHsb(255.f/numCurve*i, 255, 255));
        ofNoFill();
        ofPushMatrix();
//        ofTranslate(i*10, 0);
        ofBeginShape();
        for (int j=0; j<curves[i].size(); ++j) {
            ofVertex(j, curves[i][j]);
        }
        ofEndShape();
        ofPopMatrix();
    }
    ofPopStyle();
    ofPopMatrix();
}
