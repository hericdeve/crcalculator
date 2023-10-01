#include <iostream>
#include <string>
#include "subject.h"

Subject::Subject() : nome(""), nota(0.0), peso(0.0), periodo(0) {}

Subject::Subject(std::string nomeIn, double notaIn, double pesoIn, long periodoIn) 
    : nome(nomeIn), nota(notaIn), peso(pesoIn), periodo(periodoIn) {}

std::string Subject::getNome() const {
    return this->nome;
}

double Subject::getNota() const {
    return this->nota;
}

double Subject::getPeso() const {
    return this->peso;
}

long Subject::getPeriodo() const {
    return this->periodo;
}

void Subject::setNome(std::string nomeIn) {
    this->nome = nomeIn;
}

void Subject::setNota(double notaIn) {
    this->nota = notaIn;
}

void Subject::setPeso(double pesoIn) {
    this->peso = pesoIn;
}

void Subject::setPeriodo(long periodoIn) {
    this->periodo = periodoIn;
}
