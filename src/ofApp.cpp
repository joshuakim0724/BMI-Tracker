#include "ofApp.h"
#include "user.h"
#include "constants.cpp"
#include "fileReader.h"

User user;

void ofApp::setup()
{
    if (returningUser()) {
        user = CreateUserFromFile(FILE_PATH);
    } else {
        
        // Gets user information, then sets up the GUI
        getUserInfo();
    }
    font.load(VERDANA_FONT, 24);

    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);

    // Setting up user_gui on the top right corner
    user_gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    
    // add a folder to group a user info together //
    ofxDatGuiFolder* folder = user_gui->addFolder(USER_INFO, ofColor::white);
    folder->addLabel(AGE_ + to_string(user.getAge()));
    folder->addLabel(WEIGHT_ + to_string(user.getWeight()) + POUNDS_);
    folder->addLabel(HEIGHT_ + to_string(user.getHeight() / 12) + "''" + to_string(user.getHeight() % 12));
    folder->addLabel(GENDER_ + user.getGender());
    folder->addLabel(ACTIVITY_FACTOR + to_string(user.getUserActivity()));

    folder->expand();
    user_gui->addBreak();
    
    user_gui->addLabel(CALORIE_GOAL + to_string((int)user.CalculateCalories(user.getUserActivity())));
    
    // Setting up calorie gui on the top left corner
    calorie_gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    
    calorie_gui->addLabel(CALORIE_GOAL + to_string((int)user.CalculateCalories(user.getUserActivity()))); // User Calorie label
    calorie_add = calorie_gui->addButton(CALORIE_BUTTON); // Calorie adder button
    calorie_remove = calorie_gui->addButton(CALORIE_REMOVE); // Calorie remover button
    new_day_button = calorie_gui->addButton(NEW_DAY_BUTTON); // Resets the day and calories
    show_data_button = calorie_gui->addButton(DATA_BUTTON);
    
    // and a couple of simple buttons to regular gui
    clicker_button = user_gui->addButton(CLICKER_BUTTON); // Clicker counter button
    user_gui->addToggle(TFULLSCREEN_, false); // Fullscreen button

//    // Setting the button color
//    button_->setStripeColor(ofColor::lightSkyBlue);
//    calorie_add->setStripeColor(ofColor::red);
    
    // Events depending on buttons etc.
    calorie_add->onButtonEvent(this, &ofApp::onButtonEvent);
    calorie_remove->onButtonEvent(this, &ofApp::onButtonEvent);
    new_day_button->onButtonEvent(this, &ofApp::onButtonEvent);

    user_gui->onButtonEvent(this, &ofApp::onButtonEvent);
    user_gui->onToggleEvent(this, &ofApp::onToggleEvent);
    
    calorie_label = new ofxDatGuiLabel(TODAY_CALORIE + to_string(user.getCalories()));
    calorie_label->setWidth(ofGetWidth() / 7);
    
    // launch the app //
    mFullscreen = false;
    refreshWindow();
}

void ofApp::update()
{
    calorie_label->setLabel("Today's Calories: " + to_string(user.getCalories()));
    clicker_button->update();
    calorie_add->update();
    calorie_remove->update();
    new_day_button->update();

    calorie_label->update();
    SaveToFile(FILE_PATH, user);
}

void ofApp::draw()
{
    clicker_button->draw();
    calorie_add->draw();
    calorie_remove->draw();
    new_day_button->draw();

    calorie_label->draw();
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target == clicker_button){
        num_clicks++;
        clicker_button->setLabel(CLICKED_ + ofToString(num_clicks) + TIMES_);
        return;
    }
    
    // Calorie Buttons Below
    
    else if (e.target->getLabel() == CALORIE_BUTTON) {
        user.AddCaloriesFromInput();
        return;
    } else if (e.target->getLabel() == CALORIE_REMOVE) {
        user.RemoveCaloriesFromInput();
        return;
    } else if (e.target->getLabel() == "New Day") {
        user.NewDay();
        return;
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
    user_gui->getToggle(TFULLSCREEN_)->setChecked(mFullscreen);
    refreshWindow();
}

void ofApp::refreshWindow()
{
    ofSetFullscreen(mFullscreen);
    if (!mFullscreen) {
        ofSetWindowShape(1920, 1400);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
    positionLabels();
}

void ofApp::positionLabels() {
    calorie_label->setPosition(ofGetWidth()/2.5 , ofGetHeight()/4);
}

void ofApp::getUserInfo() {
    user.GetUserAge();
    user.GetUserWeight();
    user.GetUserHeight();
    user.GetUserGender();
    user.GetUserActivity();
    
    SaveToFile(FILE_PATH, user);
}

bool ofApp::returningUser() {
    bool result = ofSystemYesNoDialoge("Returning User", "Are you a returning user?");
    return result;
}
