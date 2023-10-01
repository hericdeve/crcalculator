#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include "grade.h"

std::string trim(const std::string& str);
Grade readCSV(const std::string& filePath);


#endif // FILEMANAGEMENT_H
