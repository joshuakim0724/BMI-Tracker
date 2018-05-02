//
//  fileReader.cpp
//  final-project-joshuakim0724
//
//  Created by Joshua Kim on 5/1/18.
//

#include "fileReader.h"

using std::endl;

/**
 * This will save the trainingVectorModel to a file
 * @param filename is the file it will be exported to
 * https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
 * Used this to set a trunc flag that will clear the file
 */
void SaveToFile(string filename, User user) {
    std::ofstream file_reader(filename, std::ofstream::out | std::ofstream::trunc);

    if (file_reader.is_open()) {
        
        // Storing user data to a text file
        file_reader << user.getAge() << endl;
        file_reader << user.getWeight() << endl;
        file_reader << user.getHeight() << endl;
        file_reader << user.getGender() << endl;
        file_reader << user.getUserActivity() << endl;
        file_reader << user.getCalories() << endl;

        // Now storing calorie vector data
        for (int i = 0; i < user.getCaloriesTracker().size(); i++) {
            file_reader << user.getCaloriesTracker()[i] << endl;
        }
    } else {
        std::cout << "why no work";
    }
    file_reader.close();
}

// This will create a User reading from the file
// http://www.cplusplus.com/forum/general/13135/ Used this to convert string to int
User CreateUserFromFile(string filename) {
    User returning_user;
    std::ifstream file(filename);
    std::vector<string> user_info;
    string file_line;
    
    if (file.fail()) {
        std::cout << "Unable to open file";
        exit(1);
    }
    
    while (std::getline(file, file_line)) {
        user_info.push_back(file_line);
    }
    
    returning_user.setAge(atoi(user_info[0].c_str()));
    returning_user.setWeight(atoi(user_info[1].c_str()));
    returning_user.setHeight(atoi(user_info[2].c_str()));
    returning_user.setGender(user_info[3]);
    returning_user.setUserActivity(atoi(user_info[4].c_str()));
    returning_user.setCalories(atoi(user_info[5].c_str()));
    
    for (int i = 6; i < user_info.size(); i++) {
        returning_user.getCaloriesTracker().push_back(atoi(user_info[i].c_str()));
    }
    
    return returning_user;
}
