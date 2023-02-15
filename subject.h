#ifndef SUBJECT_H
#define SUBJECT_H


#include <iostream>
#include <string>

using namespace std;


class Subject
{
    public:
        Subject();
        Subject(string, double, double, double);
        const string getNome();
        double getNota();
        const double getPeso();
        long getPeriodo();
        void setNome(string);
        void setNota(double);
        void setPeso(double);
        void setPeriodo(long);

    private:
        string nome;
        double nota;
        double peso;
        long periodo;

};




#endif