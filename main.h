#ifndef MAIN_H
#define MAIN_H

double **init(unsigned int nbEqn, unsigned int nbInconnues);

void liberation(double **matrice, unsigned int nbEqn);

void resolution(double **matrice, unsigned int nbEqn, unsigned int nbInconnues, const char* afficherEtapes);

void echangerLignes(double **matrice, unsigned int ligne1, unsigned int ligne2);

void param(double **matrice, unsigned int nbInconnues);

void printmatrice(double **matrice, unsigned int nbEqn, unsigned int nbInconnues);

char* dtfraction(double nombre);

unsigned int pgdc(unsigned int a, unsigned int b);

#endif //MAIN_H
