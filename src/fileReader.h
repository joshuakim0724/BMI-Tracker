//
//  fileReader.h
//  final-project-joshuakim0724
//
//  Created by Joshua Kim on 5/1/18.
//

#ifndef fileReader_h
#define fileReader_h

#include "user.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>

using std::string;

void SaveToFile(string filename, User user);

User CreateUserFromFile(string filename);

#endif /* fileReader_hpp */
