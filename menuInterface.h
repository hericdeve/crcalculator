#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

#include "grade.h"

class MenuInterface {
public:
    MenuInterface();
    void run();
private:
    Grade grade;
    void showMenu();
    void showCRA();
    void showCRAHighestGrade();
    void showCRAPerPeriod();
    void showGrade();
    void addSubject();
    void deleteSubject();
    void editSubject();
};

#endif // MENUINTERFACE_H
