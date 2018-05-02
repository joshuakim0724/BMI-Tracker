//
//  fileReader.cpp
//  final-project-joshuakim0724
//
//  Created by Joshua Kim on 5/1/18.
//

#include "fileReader.h"

using std::endl;
using std::ofstream;

/**
 * This will save the trainingVectorModel to a file
 * @param filename is the file it will be exported to
 * https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
 * Used this to set a trunc flag that will clear the file
 */
void SaveToFile(ofstream &file_reader, string filename, User user) {
    file_reader.open(filename, std::ofstream::out | std::ofstream::trunc);

    file_reader << user.getAge() << endl;
    file_reader << user.getWeight() << endl;
    file_reader << user.getHeight() << endl;
    file_reader << user.getGender() << endl;
    file_reader << user.getUserActivity() << endl;

    for (int i = 0; i < user.getCaloriesTracker().size(); i++) {
        file_reader << user.getCaloriesTracker()[i] << endl;
    }
    file_reader.close();
}
