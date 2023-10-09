#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include <string>
#include "grade.h"

class MenuInterface {
public:
    MenuInterface(Grade &grade);
    void run();
private:
    Grade *grade;
    // std::string filePath;

    void showMenu();
    // void showCRA();
    // void showCRAHighestGrade();
    // void showCRAPerPeriod();
    // void showGrade();
    // void addSubject();
    // void deleteSubject();
    // void editSubject();
};

#endif // MENUINTERFACE_H
