#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "subject.h"
#include "grade.h"
#include "groupby.h"

using namespace std;

Grade::Grade(){};

bool operator==(Subject &subject1, Subject &subject2)
{
    if (subject1.getNome() == subject2.getNome())
        return true;
    return false;
}

const vector<Subject>  Grade::getSubjects(){
    return this->subjects;

}

Grade & Grade::operator+=(Subject &subject)
{
    int found = 0;

    if (!this->subjects.size())
    {
        this->subjects.push_back(subject);
        
    }

    else
    {
        for (vector<Subject>::iterator it = this->subjects.begin(); it != this->subjects.end(); it++)
        {
            if (subject == *it)
            {
                // cout << "Subject já catalogada." << endl;
                found = 1;   
            }
        }
        this->subjects.push_back(subject);     
    }
   
    return *this;
}

ostream &operator<<(ostream &ostream, Grade &grade)
{   
    string spacer = "---------------------------------------------------------------------------------------------";
    cout << left << setw(45) << "Disciplina " << setw(20) << "Nota" << setw(20) << left << setw(20) << "Peso" <<  setw(20) << left <<"Período" << endl << endl;
    cout << spacer << endl;
    vector <Subject> subjects = grade.getSubjects();
    for (unsigned indice = 0; indice < subjects.size(); indice++ )
        cout << left << setw(45) << subjects.at(indice).getNome() << fixed << left << setw(20) << setprecision(1)  << subjects.at(indice).getNota() << left << setw(20) << setprecision(1) << fixed << subjects.at(indice).getPeso() << setw(20) << left << fixed << subjects.at(indice).getPeriodo() << endl;
    return ostream;
}

void Grade::showGrade(){



}

