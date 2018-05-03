//
// Created by Joshua Kim on 4/16/18.
// asdasd

#include "user.h"
#include "ofxDatGui.h"
#include "constants.cpp"

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

const double KGPerPound = 0.453592;

/*---------------------------------Constructors-------------------------------------*/
User::User() {
    age_ = 0;
    weight_ = 0;
    height_ = 0;
    gender_ = "";
}

User::User(int age, double weight, double height, string gender) {
    this->age_ = age;
    this->weight_ = weight;
    this->height_ = height;
    this->gender_ = gender;
}

/*-------------------------------------------Getters--------------------------------------*/
int User::getAge() { return age_; }

int User::getWeight() { return weight_; }

int User::getHeight() { return height_; }

string User::getGender() { return gender_; }

int User::getCalories() { return calories_; }

std::vector<int> User::getCaloriesTracker() { return calories_tracker; }

int User::getUserActivity() { return activity_; }

/*------------------------------------------Setters--------------------------------------*/
void User::setAge(int age) {
    this->age_ = age;
}

void User::setWeight(double weight) {
    this->weight_ = weight;
}

void User::setHeight(double height) {
    this->height_ = height;
}

void User::setGender(string gender) {
    this->gender_ = gender;
}

void User::setCalories(int calories) {
    this->calories_ = calories;
}

void User::setUserActivity(int factor) {
    this->activity_ = factor;
}
/* ---------------------Methods used to get average calories per day------------------- */
bool User::IsMale() {
    return gender_ == "male";
}

double User::PoundToKg(double pound) {
    return pound / KGPerPound;
}

// https://www.livestrong.com/article/238273-how-to-calculate-appropriate-calories-per-day/
// Used this to get a formula to calculate BMR

// This method will calculate BRM which is used with activity factor to get number of calories for males
double User::CalculateBMRMale() {
    double weight_variable = weight_ * 6.23;
    double height_variable = height_ * 12.7;
    double age_variable = age_ * 6.8;

    return weight_variable + height_variable - age_variable + 66;
}

// This method will calculate BRM which is used with activity factor to get number of calories for females
double User::CalculateBMRFemale() {
    double weight_variable = weight_ * 4.35;
    double height_variable = height_ * 4.7;
    double age_variable = age_ * 4.7;

    return weight_variable + height_variable - age_variable + 655;
}

/**
 * Enter a number 0-10 from 0 being getting 0 exercise a week, to 10 being getting vigorous exercise everyday
 * @param number.
 * @return
 */
double User::GetActivityFactor(int number) {
    switch (number) {
        case 0 : return 1;
        case 1 : return 1.2;
        case 2 : return 1.2;
        case 3 : return 1.375;
        case 4 : return 1.375;
        case 5 : return 1.55;
        case 6 : return 1.55;
        case 7 : return 1.75;
        case 8 : return 1.75;
        case 9 : return 1.9;
        case 10 : return 1.9;

        default :
            return -1;
    }
}

/**
 * Gets number of calories depending on BRM and activity factor
 */
double User::CalculateCalories(int ActivityFactor) {
    if (IsMale()) {
        return CalculateBMRMale() * GetActivityFactor(ActivityFactor);
    } else {
        return CalculateBMRFemale() * GetActivityFactor(ActivityFactor);
    }
}

double User::GetCaloriesPerMeal(int ActivityFactor, int MealNumbers) {
    return CalculateCalories(ActivityFactor) / MealNumbers;
}

/* ---------------------Methods used to get keep track of calories------------------- */

void User::UpdateCalorieTracker(int num) {
    if (calories_tracker.size() < MAX_DAYS) {
        calories_tracker.push_back(num);
        return;
    } else {
        calories_tracker.erase(calories_tracker.begin());
        calories_tracker.push_back(num);
    }
}

void User::AddCalories(int num) {
    calories_ += num;
}

void User::RemoveCalories(int num) {
    if (calories_ - num > 0) {
        calories_ -= num;
    } else {
        calories_ = 0;
    }
}

// Used to reset number of calories for the user when day is passed
void User::ResetCalories() {
    calories_ = 0;
}

// Pushes number of calories to the vector then resets calories
void User::NewDay() {
    UpdateCalorieTracker(calories_);
    ResetCalories();
}

void User::AddCaloriesFromInput() {
    string input_ = "";
    int num_calories = 0;
    input_ = ofSystemTextBoxDialog("Please enter number of calories");
    
    while (true) {
        
        // This code converts from string to number safely. If it fails, then asks for a new input
        stringstream myStream(input_);
        if (myStream >> num_calories) {
            break;
        }
        input_ = ofSystemTextBoxDialog("Error: Please only enter numbers");
    }
    AddCalories(num_calories);
}

void User::RemoveCaloriesFromInput() {
    string input_ = "";
    int num_calories = 0;
    input_ = ofSystemTextBoxDialog("Please enter number of calories");
    
    while (true) {
        
        // This code converts from string to number safely. If it fails, then asks for a new input
        stringstream myStream(input_);
        if (myStream >> num_calories) {
            break;
        }
        input_ = ofSystemTextBoxDialog("Error: Please only enter numbers");
    }
    RemoveCalories(num_calories);
}
// These methods below will get user information from input boxes

// http://www.cplusplus.com/forum/articles/6046/ Used this to learn how to use cin correctly
void User::GetUserAge() {
    string input_ = "";
    int user_age = 0;
    input_ = ofSystemTextBoxDialog("Please enter your age");
    
    while (true) {
        
        // This code converts from string to number safely. If it fails, then asks for a new input
        stringstream myStream(input_);
        if (myStream >> user_age) {
            break;
        }
        input_ = ofSystemTextBoxDialog("Error: Please enter your age (Numbers Only)");
    }
    age_ = user_age;
}

void User::GetUserWeight() {
    string input_ = "";
    double user_weight = 0;
    input_ = ofSystemTextBoxDialog("Please enter your weight in pounds");
    
    while (true) {
        
        // This code converts from string to number safely. If it fails, then asks for a new input
        stringstream myStream(input_);
        if (myStream >> user_weight) {
            break;
        }
        input_ = ofSystemTextBoxDialog("Error: Invalid input, please try again");
    }
    user_weight = roundf(user_weight);
    weight_ = user_weight;
}

void User::GetUserHeight() {
    string input_ = "";
    double user_height = 0;
    input_ = ofSystemTextBoxDialog("Please enter your height in inches");
    
    while (true) {
        
        // This code converts from string to number safely. If it fails, then asks for a new input
        stringstream myStream(input_);
        if (myStream >> user_height) {
            break;
        }
        input_ = ofSystemTextBoxDialog("Error: Invalid input, please try again");
    }
    user_height = roundf(user_height);
    height_ = user_height;
}

void User::GetUserGender() {
    string user_gender = "";
    user_gender = ofSystemTextBoxDialog ("Please enter your gender (male/female) (Case Sensitive)");
    
    while (true) {
        
        // Makes sure the input is either 'male' or 'female'
        if (user_gender == "male" || user_gender == "female") {
            break;
        }
        
        user_gender = ofSystemTextBoxDialog("Error: Re-enter gender (Lowercase 'male' or 'female')");
    }
   gender_ = user_gender;
}

void User::GetUserActivity() {
    string input_ = "";
    int user_activity = 0;
    input_ = ofSystemTextBoxDialog("Please enter your weekly activity factor (0-10)");
    
    while (true) {
        
        // This code converts from string to number safely. If it fails, then asks for a new input
        stringstream myStream(input_);
        if (myStream >> user_activity) {
            
            // Makes sure the number is between 0-10
            if (user_activity >= 0 && user_activity <= 10) {
                break;
            }
        }
        input_ = ofSystemTextBoxDialog("Error: Invalid input, please try again");
    }
    user_activity = roundf(user_activity);
    activity_ = user_activity;
}

