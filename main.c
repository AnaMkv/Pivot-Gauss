#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <assert.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
//#include <Windows.h>
//#pragma warning(disable:4996) //décommentez ces lignes si vous compilez avec MSVC (sous Windows avec Visual Studio)
#define EPSILON 1e-6
#define PRECISION 1000000

int main(void) {
    //SetConsoleOutputCP(CP_UTF8);
    while (1) {
        printf(
            "Cet utilitaire sert à calculer, à l'aide de l'algorithme du pivot de Gauss, les solutions d'un système de n équations à p inconnues.\n");
        unsigned int correct = 0;
        char afficherEtapes[4] = "non";
        do {
            printf("Voulez-vous afficher les étapes de la résolution ? (Oui/Non)\n");
            scanf("%s", afficherEtapes);
            for (unsigned int i = 0; i < strlen(afficherEtapes); i++)
                afficherEtapes[i] = (char)tolower(afficherEtapes[i]);
            while (getchar() != '\n'){}
            if ((strcmp(afficherEtapes, "oui") == 0 || strcmp(afficherEtapes, "non") == 0))
                correct = 1;
            else if(strcmp(afficherEtapes, "exit") == 0)
                return 0;
            else
                printf("Erreur : la valeur saisie n'est pas correcte.\n\n");
        } while (!correct);
        printf("Combien d'équations comporte votre système ?\n");
        unsigned int nbEqn = 0;
        if (scanf("%u", &nbEqn) != 1) {
            printf("Erreur, la valeur saisie n'est pas un nombre entier positif.\n\n");
            while (getchar() != '\n') {}
            continue;
        }
        assert(nbEqn > 0);
        printf("Combien d'inconnues comporte votre système ?\n");
        unsigned int nbInconnues = 0;
        if (scanf("%u", &nbInconnues) != 1) {
            printf("Erreur, la valeur saisie n'est pas un nombre entier positif.\n\n");
            while (getchar() != '\n') {}
            continue;
        }
        assert(nbInconnues > 0);
        if (nbInconnues > nbEqn) {
            printf("Erreur : il y a plus d'inconnues que d'équations dans le système.\n\n");
            continue;
        }
        double **matrice = init(nbEqn, nbInconnues);
        assert(matrice != NULL);
        resolution(matrice, nbEqn, nbInconnues, afficherEtapes);
        liberation(matrice, nbEqn);
    }
}

double **init(unsigned int nbEqn, unsigned int nbInconnues) {
    double **matrice = malloc(nbEqn * sizeof(double *));
    assert(matrice != NULL);
    for (unsigned int i = 0; i < nbEqn; i++) {
        matrice[i] = (double *) malloc((nbInconnues + 1) * sizeof(double));
        assert(matrice[i] != NULL);
        printf("Veuillez saisir les coefficients de l'équation %d :\n", i + 1);
        for (unsigned int j = 0; j < nbInconnues; j++) {
            printf("Coefficient de l'inconnue %d : ", j + 1);
            if (scanf("%lf", &matrice[i][j]) != 1) {
                printf("Erreur, la valeur saisie n'est pas un nombre valide.\n\n");
                while (getchar() != '\n') {}
                liberation(matrice, nbEqn);
                exit(EXIT_FAILURE);
            }
        }
        printf("Membre de droite de l'équation %d : ", i + 1);
        if (scanf("%lf", &matrice[i][nbInconnues]) != 1) {
            printf("Erreur, la valeur saisie n'est pas un nombre valide.\n\n");
            while (getchar() != '\n') {}
            exit(EXIT_FAILURE);
        }
    }
    return matrice;
}

void liberation(double **matrice, unsigned int nbEqn) {
    for (unsigned int i = 0; i < nbEqn; i++)
        free(matrice[i]);
    free(matrice);
}

void resolution(double **matrice, unsigned int nbEqn, unsigned int nbInconnues, const char *afficherEtapes) {
    int afficher = strcmp(afficherEtapes, "oui") == 0;
    printf("\n");
    if (afficher)
        printmatrice(matrice, nbEqn, nbInconnues);
    for (unsigned int i = 0; i < nbEqn; i++) {
        unsigned int pivot = i;
        for (unsigned int j = i + 1; j < nbEqn; j++)
            if (fabs(matrice[j][i]) > fabs(matrice[pivot][i]))
                pivot = j;
        if (pivot != i) {
            echangerLignes(matrice, i, pivot);
            if (afficher)
                printmatrice(matrice, nbEqn, nbInconnues);
        }
        double valeurPivot = matrice[i][i];
        if (fabs(valeurPivot) < EPSILON) {
            int ligneNulle = 1;
            for (unsigned int j = 0; j < nbInconnues; j++)
                if (fabs(matrice[i][j]) > EPSILON) {
                    ligneNulle = 0;
                    break;
                }
            if (ligneNulle && fabs(matrice[i][nbInconnues]) > EPSILON) {
                printf("Système sans solution.\n\n");
                return;
            }
            if (ligneNulle && fabs(matrice[i][nbInconnues]) < EPSILON) {
                printf("Système avec une infinité de solutions de la forme :\n");
                param(matrice, nbInconnues);
                return;
            }
            if (ligneNulle) {
                printf("Erreur : division par 0 impossible.\n\n");
                return;
            }
        }
        for (unsigned int j = 0; j < nbInconnues + 1; j++)
            matrice[i][j] /= valeurPivot;
        if (afficher)
            printmatrice(matrice, nbEqn, nbInconnues);
        for (unsigned int j = i + 1; j < nbEqn; j++) {
            double facteur = matrice[j][i];
            for (unsigned int k = 0; k < nbInconnues + 1; k++)
                matrice[j][k] -= facteur * matrice[i][k];
            if (afficher)
                printmatrice(matrice, nbEqn, nbInconnues);
        }
    }
    for (int i = (int)nbInconnues - 1; i >= 0; i--)
        for (int j = i - 1; j >= 0; j--) {
            double facteur = matrice[j][i];
            for (unsigned int k = 0; k < nbInconnues + 1; k++)
                matrice[j][k] -= facteur * matrice[i][k];
            if (afficher)
                printmatrice(matrice, nbEqn, nbInconnues);
        }
    double *solutions = malloc(nbInconnues * sizeof(double));
    for (unsigned int i = 0; i < nbInconnues; i++)
        solutions[i] = matrice[i][nbInconnues];
    printf("Les solutions sont :\n");
    for (unsigned int i = 0; i < nbInconnues; i++) {
        char* fraction = dtfraction(solutions[i]);
        printf("Inconnue %d = %s\n", i + 1, fraction);
        free(fraction);
    }
    printf("\n");
    free(solutions);
}

void echangerLignes(double **matrice, unsigned int ligne1, unsigned int ligne2) {
    double *temp = matrice[ligne1];
    matrice[ligne1] = matrice[ligne2];
    matrice[ligne2] = temp;
}

void param(double **matrice, unsigned int nbInconnues) {
    printf("x1 = %lf", matrice[0][nbInconnues]);
    for (unsigned int j = 1; j < nbInconnues; j++)
        if (fabs(matrice[0][j]) > 1e-6) {
            if (matrice[0][j] < 0) {
                char* fraction = dtfraction(fabs(matrice[0][j]));
                printf(" + %sx%d", fraction, j + 1);
                free(fraction);
            }
            else {
                char* fraction = dtfraction(matrice[0][j]);
                printf(" - %sx%d", fraction, j + 1);
                free(fraction);
            }
        }
    printf("\n\n");
}

void printmatrice(double **matrice, unsigned int nbEqn, unsigned int nbInconnues) {
    for (unsigned int m = 0; m < nbEqn; m++) {
        for (unsigned int n = 0; n <= nbInconnues; n++) {
            char* fraction = dtfraction(matrice[m][n]);
            printf("%s ", fraction);
            free(fraction);
        }
        printf("\n");
    }
    printf("\n");
}

unsigned int pgdc(unsigned int a, unsigned int b) {
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

char* dtfraction(double nombre) {
    char* fraction = malloc(50 * sizeof(char));
    if (fabs(nombre) < EPSILON) {
        sprintf(fraction, "0");
        return fraction;
    }
    if (fabs(nombre - round(nombre)) < EPSILON) {
        snprintf(fraction, 50, "%.0f", nombre);
        return fraction;
    }
    unsigned int numerateur = (unsigned int)(fabs(nombre) * PRECISION);
    unsigned int denominateur = PRECISION;
    unsigned int diviseur = pgdc(numerateur, denominateur);
    numerateur /= diviseur;
    denominateur /= diviseur;
    if (nombre < 0)
        snprintf(fraction, 50, "-%u/%u", numerateur, denominateur);
    else
        snprintf(fraction, 50, "%u/%u", numerateur, denominateur);
    return fraction;
}