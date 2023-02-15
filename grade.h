#ifndef GRADE_H
#define GRADE_H


#include <iostream>
#include <string>
#include <vector>
#include "subject.h"



using namespace std;


class Grade
{
    public:
       Grade();
       Grade &operator+=(Subject &);
       void showGrade();
       const vector<Subject> getSubjects();

    private:
        vector <Subject> subjects;
        
    bool operator==(Subject &);
    friend ostream &operator<<(ostream &, Grade &);

};



#endif