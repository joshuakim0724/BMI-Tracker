#include "ofApp.h"
#include "user.h"
#include "constants.cpp"
#include "fileReader.h"

User user;

void ofApp::setup()
{
    // If it is a returning user, will use previous data, else will create a new user using inputs
    if (returningUser()) {
        user = CreateUserFromFile(FILE_PATH);
    } else {
        getUserInfo();
    }
    font.load(VERDANA_FONT, 24);

    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);

    userGuiSetup();
    calorieGuiSetup();
    dataGuiSetup();
    
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

void ofApp::userGuiSetup() {
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
    
    // Adding buttons to the user gui
    clicker_button = user_gui->addButton(CLICKER_BUTTON); // Clicker counter button
    user_gui->addToggle(TFULLSCREEN_, false); // Fullscreen button
    
    // Events depending on which button
    user_gui->onButtonEvent(this, &ofApp::onButtonEvent);
    user_gui->onToggleEvent(this, &ofApp::onToggleEvent);
}


void ofApp::calorieGuiSetup() {
    // Setting up calorie gui on the top left corner
    calorie_gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    
    // Adding labels and buttons to the calorie gui
    calorie_gui->addLabel(CALORIE_GOAL + to_string((int)user.CalculateCalories(user.getUserActivity()))); // User Calorie label
    calorie_add = calorie_gui->addButton(CALORIE_BUTTON); // Calorie adder button
    calorie_remove = calorie_gui->addButton(CALORIE_REMOVE); // Calorie remover button
    new_day_button = calorie_gui->addButton(NEW_DAY_BUTTON); // Resets the day and calories
    show_data_button = calorie_gui->addButton(DATA_BUTTON);
    
    // Events depending on which button
    calorie_add->onButtonEvent(this, &ofApp::onButtonEvent);
    calorie_remove->onButtonEvent(this, &ofApp::onButtonEvent);
    new_day_button->onButtonEvent(this, &ofApp::onButtonEvent);
}

void ofApp::dataGuiSetup() {
    data_gui = new ofxDatGui();
    data_gui->setPosition(ofGetWidth()/2.5, ofGetHeight()/2);
    
    setUpSliders();
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

void ofApp::setUpSliders() {
    std::vector<int> calorie_data = user.getCaloriesTracker();
    int calorie_goal = user.CalculateCalories(user.getUserActivity());
    float accuracy = 0;
    
    cout << calorie_data.size();
    
    for (int i = 0; i < calorie_data.size(); i++) {
        string day = "Day " + to_string(i + 1);
        
        if (calorie_data[i] > calorie_goal) {
            accuracy = calorie_goal / calorie_data[i];
        } else {
            accuracy = calorie_data[i] / calorie_goal;
        }
        slider = data_gui->addSlider(day, 0, 100, accuracy);
        if (accuracy < 80) {
            slider->setBackgroundColor(ofColor::red);
        }
    }
}

//    // Setting the button color
//    button_->setStripeColor(ofColor::lightSkyBlue);
//    calorie_add->setStripeColor(ofColor::red);
