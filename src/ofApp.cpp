#include "ofApp.h"
#include "user.h"
#include "constants.cpp"
#include "fileReader.h"

User user;

void ofApp::setup() {
    
    // If it is a returning user, will use previous data, else will create a new user using inputs
    if (returningUser()) {
        user = CreateUserFromFile(FILE_PATH);
    } else {
        getUserInfo();
    }
    font.load(VERDANA_FONT, 24);

    // Setup the windows base
    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);

    userGuiSetup();
    calorieGuiSetup();
    
    // Creates calorie label
    calorie_label = new ofxDatGuiLabel(TODAY_CALORIE + to_string(user.getCalories()));
    calorie_label->setWidth(ofGetWidth() / CALORIE_WIDTH);
    
    // launch the app //
    mFullscreen = false;
    refreshWindow();
}

// Whenever an event happens, interface will update
void ofApp::update() {
    calorie_label->setLabel(TODAY_CALORIE + to_string(user.getCalories())); // Updates the label to correct number of calories
    clicker_button->update();
    calorie_add->update();
    calorie_remove->update();
    new_day_button->update();

    calorie_label->update();
    SaveToFile(FILE_PATH, user);
}

// Makes sure that the buttons, labels, etc. appear on board properly
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
    user_gui->addBreak();
    
    // add a dropdown menu //
    user_gui->addDropdown(CHOOSE_THEME, OPTIONS); // Able to switch betwen themes
    user_gui->addBreak();
    
    // Adding buttons to the user gui
    clicker_button = user_gui->addButton(CLICKER_BUTTON); // Clicker counter button
    user_gui->addColorPicker(COLOR_PICKER, ofColor::fromHex(0xeeeeee)); // Userface color changer
    user_gui->addToggle(TFULLSCREEN_, false); // Fullscreen button
    
    // Events depending on which button
    user_gui->onButtonEvent(this, &ofApp::onButtonEvent);
    user_gui->onToggleEvent(this, &ofApp::onToggleEvent);
    user_gui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
    user_gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    
    // Setting the stripe color of stuff in gui
    folder->setStripeColor(ofColor::skyBlue);
    clicker_button->setStripeColor(ofColor::seaGreen);
}


void ofApp::calorieGuiSetup() {
    
    // Setting up calorie gui on the top left corner
    calorie_gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    
    // Adding labels and buttons to the calorie gui
    calorie_gui->addLabel(CALORIE_GOAL + to_string((int)user.CalculateCalories(user.getUserActivity()))); // User Calorie label
    calorie_gui->addBreak();

    calorie_add = calorie_gui->addButton(CALORIE_BUTTON); // Calorie adder button
    calorie_remove = calorie_gui->addButton(CALORIE_REMOVE); // Calorie remover button
    calorie_gui->addBreak();

    new_day_button = calorie_gui->addButton(NEW_DAY_BUTTON); // Resets the day and calories
    calorie_gui->addBreak();

    data_button = calorie_gui->addButton(SHOW_DATA_BUTTON); // Data for past 10 days
    
    // Events depending on which button
    calorie_add->onButtonEvent(this, &ofApp::onButtonEvent);
    calorie_remove->onButtonEvent(this, &ofApp::onButtonEvent);
    new_day_button->onButtonEvent(this, &ofApp::onButtonEvent);
    data_button->onButtonEvent(this, &ofApp::onButtonEvent);
    
    // Setting the stripe colors of some stuff in gui
    calorie_add->setStripeColor(ofColor::royalBlue);
    calorie_remove->setStripeColor(ofColor::paleVioletRed);
    new_day_button->setStripeColor(ofColor::lightPink);
    data_button->setStripeColor(ofColor::powderBlue);
}

void ofApp::dataGuiSetup() {
    data_gui = new ofxDatGui();
    data_gui->setPosition(ofGetWidth()/2.5, ofGetHeight()/2);
    
    setUpSliders();
    data_gui->setEnabled(false); // Makes sure you can't actually use the sliders
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
    } else if (e.target->getLabel() == NEW_DAY_BUTTON) {
        user.NewDay();
        return;
        
    // Show/Clear Data Button Below
        
    } else if (e.target->getLabel() == SHOW_DATA_BUTTON) {
        dataGuiSetup();
        data_button->setLabel(CLEAR_DATA_BUTTON); // Changes label to button to clear
        return;
    } else if (e.target->getLabel() == CLEAR_DATA_BUTTON) {
        data_gui->setVisible(false); // Makes the gui disapear
        data_button->setLabel(SHOW_DATA_BUTTON); // Changes label back
    }
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e) {
    if (e.target->is(TFULLSCREEN_)) {
        toggleFullscreen();
    }
}

// Depending on which thing user clicks, theme changes
void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e) {
    if (e.target->getLabel() == THEME1) {
        user_gui->setTheme(new ofxDatGuiTheme(true));
    } else if (e.target->getLabel() == THEME2) {
        user_gui->setTheme(new ofxDatGuiThemeWireframe);
    } else if (e.target->getLabel() == THEME3) {
        user_gui->setTheme(new ofxDatGuiThemeMidnight);
    } else if (e.target->getLabel() == THEME4) {
        user_gui->setTheme(new ofxDatGuiThemeAqua);
    } else if (e.target->getLabel() == THEME5) {
        user_gui->setTheme(new ofxDatGuiThemeCharcoal);
    } else if (e.target->getLabel() == THEME6) {
        user_gui->setTheme(new ofxDatGuiThemeAutumn);
    } else if (e.target->getLabel() == THEME7) {
        user_gui->setTheme(new ofxDatGuiThemeCandy);
    } else if (e.target->getLabel() == THEME8) {
        user_gui->setTheme(new ofxDatGuiThemeSmoke);
    }
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e) {
    ofSetBackgroundColor(e.color);
}

void ofApp::toggleFullscreen() {
    mFullscreen = !mFullscreen;
    user_gui->getToggle(TFULLSCREEN_)->setChecked(mFullscreen);
    refreshWindow();
}

void ofApp::refreshWindow() {
    ofSetFullscreen(mFullscreen);
    if (!mFullscreen) {
        ofSetWindowShape(1920, 1400);
        ofSetWindowPosition((ofGetScreenWidth()/2)-(1920/2), 0);
    }
    positionLabels(); // Positions the calorie label
}

void ofApp::positionLabels() {
    calorie_label->setPosition(ofGetWidth()/XPOSITION_MULTIPLER , ofGetHeight()/YPOSITION_MULTIPLER);
}

// Gets user information from input boxes
void ofApp::getUserInfo() {
    user.GetUserAge();
    user.GetUserWeight();
    user.GetUserHeight();
    user.GetUserGender();
    user.GetUserActivity();
    
    SaveToFile(FILE_PATH, user);
}

bool ofApp::returningUser() {
    return ofSystemYesNoDialoge(RETURNING, PREVIOUS_USER);
}

void ofApp::setUpSliders() {
    std::vector<int> calorie_data = user.getCaloriesTracker();
    double calorie_goal = user.CalculateCalories(user.getUserActivity());
    float accuracy;

    for (int i = 0; i < calorie_data.size(); i++) {
        string day = DAY + to_string(i + 1);

        if (calorie_data[i] > calorie_goal) {
            accuracy = (calorie_goal / calorie_data[i]) * 100;
        } else {
            accuracy = (calorie_data[i] / calorie_goal) * 100;
        }
        
        slider = data_gui->addSlider(day, 0, 100, accuracy);
        slider->setLabelColor(ofColor::black);
        
        // If the accuracy is below the limit, sets the color to red, else green
        if (accuracy < ACCURACY_LIMIT) {
            slider->setStripeColor(ofColor::red);
            slider->setBackgroundColor(ofColor::red);
        } else {
            slider->setStripeColor(ofColor::green);
            slider->setBackgroundColor(ofColor::green);
        }
    }
}
