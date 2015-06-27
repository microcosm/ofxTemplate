#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"

class ofxTemplate : public ofBaseApp{

public:
    void setup(string _filename, int _width=ofGetWidth(), int _height=ofGetHeight(), bool _paused=false, bool _slowMode=false);
    void begin();
    void end();
    void draw();
    void pause();
    void unpause();
    void togglePause();
    void captureFrame();
    void renderGif();
    void exit();

    int width, height;
    int halfWidth, halfHeight;
    int doubleWidth, doubleHeight;
    int tripleWidth, tripleHeight;
protected:
    int colors, frameDuration;
    int framerate, saveOnFrame;
    string filename, renderMessage;
    bool slowMode, renderingNow, paused;
    
    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;
};