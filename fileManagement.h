#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include "grade.h"

std::string trim(const std::string&);
bool compareSubjects(const Subject&, const Subject&);
Grade readCSV(const std::string&);
void writeCSV(const std::string&, const Grade&); 


#endif // FILEMANAGEMENT_H
