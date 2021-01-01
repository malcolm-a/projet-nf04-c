//
//  fonctions.h
//  Projet_Malcolm
//
//  Created by Malcolm Aridory on 26/12/2020.
//  Copyright © 2020 Malcolm Aridory. All rights reserved.
//

#ifndef fonctions_h
#define fonctions_h
#include "structures.h"

// cette fonction nous sera utile si l'utilisateur inclut des espaces en écrivant son polynôme

int skip_spaces(const char chaine[], int i) {
    while (chaine[i] == ' ' || chaine[i] == '\t' || chaine[i] == '\n') {
        i++;
    }
    return i;
}


// la fonction suivante va convertir le tableau en polynôme et retourner son plus grand exposant

int tabpoly(const char chaine[], struct polynome polynome[], int degre_max) {
    int i, max_exp, signe, coeff, exp;

    // initialisation du polynôme
    
    for (i = 0; i <= degre_max; i++) {
        polynome[i].coeff = 0;
        polynome[i].degre = i;
    }
    
    // la boucle while va parcourir la saisie de l'utilisateur
    
    i = 0;
    max_exp = 0;
    while (chaine[i] != '\0') {
        i = skip_spaces(chaine, i);

        // on va tout d'abord récupérer le signe
        
        signe = 1;
        if (chaine[i] == '+') {
            i++;
        }
        i = skip_spaces(chaine, i);
        if (chaine[i] == '-') {
            signe = -1;
            i++;
        }
        
        // ici on va convertir le caractère en entier. en effet, le caractère ASCII
        // d'un nombre ne correspond pas à sa valeur, il faut y retirer 48, soit '0'.
        
        i = skip_spaces(chaine, i);
        if (chaine[i] >= '0' && chaine[i] <= '9') {
            coeff = chaine[i] - '0';
            i++;
        } else {
            coeff = 1;
        }
        
        /* on récupère ici l'exposant qui se trouve après x. si x est présent et qu'il y a
        un autre nombre derrière, ce sera l'exposant. sinon ce sera 1 par défaut. si x
        n'est pas présent ce sera 0 par défaut */
        
        if (chaine[i] == 'x') {
            i++;
            if (chaine[i] >= '0' && chaine[i] <= '9') {
                exp = chaine[i] - '0';
                i++;
            } else {
                exp = 1;
            }
        } else {
            exp = 0;
        }
        i = skip_spaces(chaine, i);

        // vérification des erreurs
        
        if (chaine[i] != '\0' && chaine[i] != '+' && chaine[i] != '-')
            return -2;  // erreur de syntaxe
        if (exp > degre_max)
            return -1;  // erreur exposant trop grand
        if (max_exp < exp)
            max_exp = exp;
        polynome[exp].coeff += signe * coeff;
    }
    return max_exp;
}

// algorithme d'affichage du polynôme

void afficher(struct polynome poly[], int degremax) {
    int i, pos;

    pos = 0;
    for (i = degremax; i >= 0; i--) { // on affiche le polynôme du plus haut degré au plus bas
        int coeff = poly[i].coeff;
        int degre = poly[i].degre;
        if (coeff != 0) {
            if (coeff > 0) {
                if (pos > 0)
                    pos += printf("+");
                if (coeff != 1 || degre == 0)
                    pos += printf("%d", coeff);
            }
            else {
                if (coeff != -1 || degre == 0)
                    pos += printf("%d", coeff);
                else
                    pos += printf("-");
            }
            if (degre > 0) {
                printf("x");
                if (degre > 1)
                    pos += printf("%d", degre);
            }
        }
    }
    if (pos == 0) {
        printf("0");
    }
    printf("\n");
}

// algorithme d'addition

struct polynome polyadd(struct polynome polya[], struct polynome polyb[], struct polynome polyc[], int deg1, int deg2) {
    int i;

    if(deg1>deg2) {
        for(i=0;i<=deg2;i++) {
            polyc[i].coeff = polya[i].coeff + polyb[i].coeff;
            polyc[i].degre = polya[i].degre;
        }
        for(i=deg2+1;i<=deg1;i++) {
            polyc[i].coeff = polya[i].coeff;
            polyc[i].degre = polya[i].degre;
        }
    }
    
    else {
        for(i=0;i<=deg1;i++) {
            polyc[i].coeff = polya[i].coeff + polyb[i].coeff;
            polyc[i].degre = polya[i].degre;
        }
        for(i=deg1+1;i<=deg2;i++) {
            polyc[i].coeff = polyb[i].coeff;
            polyc[i].degre = polyb[i].degre;
        }
    }
    return *polyc;
}


// algorithme de soustraction

struct polynome polysub(struct polynome polya[], struct polynome polyb[], struct polynome polyc[], int deg1, int deg2) {
    int i;

    if(deg1>deg2) {
        for(i=0;i<=deg2;i++) {
            polyc[i].coeff = polya[i].coeff - polyb[i].coeff;
            polyc[i].degre = polya[i].degre;
        }
        for(i=deg2+1;i<=deg1;i++) {
            polyc[i].coeff = polya[i].coeff;
            polyc[i].degre = polya[i].degre;
        }
    }
    
    else {
        for(i=0;i<=deg1;i++) {
            polyc[i].coeff = polya[i].coeff - polyb[i].coeff;
            polyc[i].degre = polya[i].degre;
        }
        for(i=deg1+1;i<=deg2;i++) {
            polyc[i].coeff = polyb[i].coeff;
            polyc[i].degre = polyb[i].degre;
        }
    }
    return *polyc;
}

/* Pour les algorithmes d'addition et de soustraction :

On va en premier lieu regarder quel polynôme a l'exposant maximum le plus élevé. On va ensuite
additionner ou soustraire les valeurs des coefficients jusqu'au degré commun le plus haut (le plus haut
exposant de l'autre polynôme). Ensuite, le polynôme d'arrivée prendra les coefficients des degrés plus
élevés du premier polynôme. */

#endif /* fonctions_h */
