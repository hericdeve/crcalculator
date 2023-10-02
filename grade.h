#ifndef GRADE_H
#define GRADE_H

#include <iostream>
#include <vector>
#include <map>
#include "subject.h"

class Grade
{
    public:
       Grade();
       Grade &operator+=(Subject &);
        Grade &operator-=(const Subject &);
        std::vector<Subject>& getSubjectsForEditing();
       const std::vector<Subject>& getSubjects() const;
       double calculateCRA() const;
       double calculateCRAHighestGrade() const;
       std::vector<Subject*> searchSubject(const std::string& name);
       std::map<long, double> calculateCRAPerPeriod() const;
       friend std::ostream &operator<<(std::ostream &, const Grade &);

    private:
        std::vector<Subject> subjects;
};

#endif
