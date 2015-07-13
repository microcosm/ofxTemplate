#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"

class ofxGifEncoderTemplate : public ofBaseApp{

public:
    void setup(string _filename, int _renderFromFrameCount=-1, int _width=ofGetWidth(), int _height=ofGetHeight());
    void setupPaused(string _filename, int _unpauseFromFrameCount=-1, int _renderFromFrameCount=-1, int _width=ofGetWidth(), int _height=ofGetHeight());
    void fadeInOut(int numFrames, ofColor color=ofColor::black, int _numBlankFramesAfterFadeOut=0);
    void begin();
    void end();
    void endAndCaptureFrame();
    void draw();
    void pause();
    void unpause();
    void togglePause();
    void enableSlowMode();
    void captureFrame();
    void render();
    void exit();

    int width, height;
    int halfWidth, halfHeight;
    int doubleWidth, doubleHeight;
    int tripleWidth, tripleHeight;
protected:
    void drawFboIntoGifEncoder();
    void drawFadeIfNeeded();
    void drawFade();
    void drawBlankFrames();
    int colors, frameDuration;
    int framerate, renderOnFrame, unpauseOnFrame;
    string filename, renderMessage, recordingMessage;
    bool slowMode, renderingNow, paused;
    
    ofxGifEncoder gifEncoder;
    ofFbo fbo;
    ofPixels pixels;
    ofColor fadeColor;
    float fadeAlpha, fadeAlphaIncrement;
    bool fade;
    int beginFadeOutOnFrame, numBlankFramesAfterFadeOut;
};