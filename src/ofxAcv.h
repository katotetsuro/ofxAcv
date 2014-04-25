//
//  ofxAcv.h
//
//  Created by Tetsuro Kato on 3/28/14.
//
//

#ifndef __ofxAcv__
#define __ofxAcv__

#include "ofMain.h"
#include "CurveLut.h"

class ofxAcv {
    
public:
    ofxAcv();
    ~ofxAcv();
    bool load(string file);
    void apply(const ofPixelsRef src, ofPixelsRef dst);
    void beginShader();
    void endShader();
    void debugDraw();
    
private:
    static const string tag;
        
    bool loaded;
    vector<CurveLut> curves;
};


#endif /* defined(__ofxAcv__) */
