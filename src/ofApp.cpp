#include "ofApp.h"
#include "user.h"
#include "constants.cpp"
User user;

void ofApp::setup()
{
    GetUserInfo();
    font.load(VERDANA_FONT, 24);

    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);


    gui_ = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    
    // add a folder to group a few components together //
    ofxDatGuiFolder* folder = gui_->addFolder(USER_INFO, ofColor::black);
    folder->addLabel(AGE_ + to_string(user.getAge()));
    folder->addLabel(WEIGHT_ + to_string(user.getWeight()) + POUNDS_);
    folder->addLabel(HEIGHT_ + to_string(user.getHeight() / 12) + "''" + to_string(user.getHeight() % 12));
    folder->addLabel(GENDER_ + user.getGender());
    folder->addLabel(ACTIVITY_FACTOR + to_string(user.getUserActivity()));

    folder->expand();
    gui_->addBreak();
    
    gui_->addLabel(CALORIE_GOAL + to_string((int)user.CalculateCalories(user.getUserActivity())));
    // and a couple of simple buttons //
    gui_->addToggle(TFULLSCREEN_, false); // Fullscreen button
    button_ = gui_->addButton(CLICKER_BUTTON); // Clicker counter button
    calorie_button = new ofxDatGuiButton(CALORIE_BUTTON); // Calorie adder button
    new_day_button = new ofxDatGuiButton("New Day");

    button_->setStripeColor(ofColor::lightSkyBlue);
    calorie_button->setStripeColor(ofColor::red);

    positionButtons();
    
    calorie_label = new ofxDatGuiLabel(TODAY_CALORIE + to_string(user.getCalories())); // User Calories label
    
    // Events depending on buttons etc.
    calorie_button->onButtonEvent(this, &ofApp::onButtonEvent);
    new_day_button->onButtonEvent(this, &ofApp::onButtonEvent);

    gui_->onButtonEvent(this, &ofApp::onButtonEvent);
    gui_->onToggleEvent(this, &ofApp::onToggleEvent);
    positionButtons();
    
    // launch the app //
    mFullscreen = false;
    refreshWindow();
}

void ofApp::update()
{
    calorie_label->setLabel("Today's Calories: " + to_string(user.getCalories()));
    button_->update();
    calorie_button->update();
    calorie_label->update();
    new_day_button->update();
}

void ofApp::draw()
{
    button_->draw();
    calorie_button->draw();
    calorie_label->draw();
    new_day_button->draw();
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == button_){
        num_clicks++;
        button_->setLabel(CLICKED_ + ofToString(num_clicks) + TIMES_);
    } else if (e.target->getLabel() == CALORIE_BUTTON) {
        user.AddCaloriesFromInput();
    } else if (e.target->getLabel() == "New Day") {
        user.ResetCalories();
    }
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    if (e.target->is(TFULLSCREEN_)) {
        toggleFullscreen();
    }
}

void ofApp::toggleFullscreen()
{
    mFullscreen = !mFullscreen;
    gui_->getToggle(TFULLSCREEN_)->setChecked(mFullscreen);
    refreshWindow();
}

void ofApp::refreshWindow()
{
    ofSetFullscreen(mFullscreen);
    if (!mFullscreen) {
        ofSetWindowShape(1920, 1400);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
}

void ofApp::positionButtons()
{
    calorie_button->setPosition(ofGetWidth()/2 - calorie_button->getWidth()/2, ofGetHeight()/3 - calorie_button->getHeight());
    new_day_button->setPosition(calorie_button->getX(), calorie_button->getY() + calorie_button->getHeight() + 20);
}

void ofApp::GetUserInfo() {
    user.GetUserAge();
    user.GetUserWeight();
    user.GetUserHeight();
    user.GetUserGender();
    user.GetUserActivity();
}

// Testing
