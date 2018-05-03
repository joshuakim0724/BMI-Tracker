#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{
    
public:
    int num_clicks;
    
    void setup();
    void update();
    void draw();
    
    void getUserInfo();
    bool returningUser();
    
    ofxDatGui* user_gui;
    ofxDatGui* calorie_gui;
    ofxDatGui* data_gui;
    
    void userGuiSetup();
    void calorieGuiSetup();
    void dataGuiSetup();
    
    ofxDatGuiLabel* calorie_label;
    
    ofxDatGuiSlider* slider;
    
    ofxDatGuiButton* clicker_button;
    ofxDatGuiButton* calorie_add;
    ofxDatGuiButton* calorie_remove;
    ofxDatGuiButton* new_day_button;
    ofxDatGuiButton* data_button;
    
    bool mFullscreen;
    void refreshWindow();
    void toggleFullscreen();
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void positionButtons();
    void positionLabels();
    void setUpSliders();
    
    ofTrueTypeFont font;
};

// Testing
