#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Subject {
    public:
        Subject();
        Subject(std::string nomeIn, double notaIn, double pesoIn, long periodoIn);

        std::string getNome() const;
        double getNota() const;
        double getPeso() const;
        long getPeriodo() const;

        void setNome(std::string nomeIn);
        void setNota(double notaIn);
        void setPeso(double pesoIn);
        void setPeriodo(long periodoIn);

    private:
        std::string nome;
        double nota;
        double peso;
        long periodo;
};

#endif
