#include <iostream>
#include <vector>
#include <string>
#include "subject.h"

using namespace std;

Subject::Subject(){}

Subject::Subject(string nomeIn, double notaIn, double pesoIn, double periodoIn){}



const string Subject:: getNome()
{
    return this->nome;
}


double Subject::getNota()
{
    return this->nota;
}

const double Subject::getPeso()
{
    return this->peso;
}

long Subject::getPeriodo()
{
    return this->periodo;
}

void Subject:: setNome(string nomeIn)
{
    this->nome = nomeIn;
}

void Subject::setNota(double notaIn)
{
    this->nota = notaIn;
}

void Subject::setPeso(double pesoIn)
{
    this->peso = pesoIn;
}

void Subject::setPeriodo(long periodoIn)
{
    this->periodo = periodoIn;
}