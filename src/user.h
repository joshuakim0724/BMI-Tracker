//
// Created by Joshua Kim on 4/16/18.
//
#ifndef user_h
#define user_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::string;

class User {

private:

    // Information about the user
    int age_;
    double weight_; // Weight is in Pounds
    double height_; // Height is in Inches
    string gender_; // Gender is either "male" or "female"

    // Information about daily calories
    int activity_;
    int calories_ = 0;
    std::vector<int> calories_tracker;
    
public:

    // Default constructor
    User();
    explicit User(int age_, double weight_, double height_, string gender_);

    // Getters
    int getAge();
    int getWeight();
    int getHeight();
    string getGender();
    int getCalories();
    std::vector<int> getCaloriesTracker();
    int getUserActivity();
    
    // Setters
    void setAge(int age);
    void setWeight(double weight);
    void setHeight(double height);
    void setGender(string gender);
    void setUserActivity(int factor);
    void setCalories(int calories);

    // Methods used to get average calories per day
    bool IsMale();
    double PoundToKg(double pound);
    double CalculateBMRMale();
    double CalculateBMRFemale();

    double GetActivityFactor(int number);
    double CalculateCalories(int ActivityFactor);

    double GetCaloriesPerMeal(int ActivityFactor, int MealNumbers);

    // Methods used to keep track of calories intake
    void UpdateCalorieTracker(int num);
    void AddCalories(int num);
    void RemoveCalories(int num);
    void ResetCalories();
    void NewDay();
    
    void AddCaloriesFromInput();
    void RemoveCaloriesFromInput();
    
    // Methods used to get information from user;
    void GetUserInfo();
    void GetUserAge();
    void GetUserWeight();
    void GetUserHeight();
    void GetUserGender();
    void GetUserActivity();
};

#endif /* user_h */
