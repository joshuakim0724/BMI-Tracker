#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{
    
public:
    int num_clicks;
    
    void setup();
    void update();
    void draw();
    
    void GetUserInfo();
    
    ofxDatGui* gui_;
    ofxDatGuiLabel* calorie_label;
    ofxDatGuiButton* button_;
    ofxDatGuiButton* calorie_button;
    ofxDatGuiButton* new_day_button;
    
    bool mFullscreen;
    void refreshWindow();
    void toggleFullscreen();
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void positionButtons();
    
    ofTrueTypeFont font;
};

// Testing
