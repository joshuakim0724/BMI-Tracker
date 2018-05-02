#include "ofApp.h"
#include "user.h"
#include "constants.cpp"
#include "fileReader.h"

User user;

void ofApp::setup()
{
    if (ReturningUser()) {
        user = CreateUserFromFile(FILE_PATH);
    } else {
        
        // Gets user information, then sets up the GUI
        GetUserInfo();
    }
    font.load(VERDANA_FONT, 24);

    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);

    gui_ = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    
    // add a folder to group a few components together //
    ofxDatGuiFolder* folder = gui_->addFolder(USER_INFO, ofColor::white);
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
    calorie_add = new ofxDatGuiButton(CALORIE_BUTTON); // Calorie adder button
    calorie_remove = new ofxDatGuiButton(CALORIE_REMOVE); // Calorie remover button
    new_day_button = new ofxDatGuiButton(NEW_DAY_BUTTON); // Resets the day

    // Setting the button color
    button_->setStripeColor(ofColor::lightSkyBlue);
    calorie_add->setStripeColor(ofColor::red);

    positionButtons();
    
    calorie_label = new ofxDatGuiLabel(TODAY_CALORIE + to_string(user.getCalories())); // User Calories label
    
    // Events depending on buttons etc.
    calorie_add->onButtonEvent(this, &ofApp::onButtonEvent);
    calorie_remove->onButtonEvent(this, &ofApp::onButtonEvent);
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
    calorie_add->update();
    calorie_remove->update();
    new_day_button->update();

    calorie_label->update();
    SaveToFile(FILE_PATH, user);
}

void ofApp::draw()
{
    button_->draw();
    calorie_add->draw();
    calorie_remove->draw();
    new_day_button->draw();

    calorie_label->draw();
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target == button_){
        num_clicks++;
        button_->setLabel(CLICKED_ + ofToString(num_clicks) + TIMES_);
    } else if (e.target->getLabel() == CALORIE_BUTTON) {
        user.AddCaloriesFromInput();
    } else if (e.target->getLabel() == CALORIE_REMOVE) {
        user.RemoveCaloriesFromInput();
    } else if (e.target->getLabel() == "New Day") {
        user.NewDay();
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
    calorie_add->setPosition(ofGetWidth()/2 - calorie_add->getWidth()/2, ofGetHeight()/3 - calorie_add->getHeight());
    calorie_remove->setPosition(calorie_add->getX(), calorie_add->getY() + calorie_add->getHeight() + 20);
    new_day_button->setPosition(calorie_remove->getX(), calorie_remove->getY() + calorie_remove->getHeight() + 20);
}

void ofApp::GetUserInfo() {
    user.GetUserAge();
    user.GetUserWeight();
    user.GetUserHeight();
    user.GetUserGender();
    user.GetUserActivity();
    
    SaveToFile(FILE_PATH, user);
}

bool ofApp::ReturningUser() {
    bool result = ofSystemYesNoDialoge("Returning User", "Are you a returning user?");
    return result;
}
