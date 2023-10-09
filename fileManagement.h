#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <string>
#include "grade.h"
#include "subject.h"
#include "fileManagement.h"

std::string trim(const std::string&);
bool compareSubjects(const Subject&, const Subject&);
Grade readOrCreateCSV(const std::string&, const std::string&);
Grade readCSV(const std::string&);
void writeCSV(const std::string&, Grade&); 


#endif // FILEMANAGEMENT_H
