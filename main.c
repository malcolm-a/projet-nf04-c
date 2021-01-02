//
//  main.c
//  Projet_Malcolm
//
//  Created by Malcolm Aridory on 26/12/2020.
//  Copyright © 2020 Malcolm Aridory. All rights reserved.
//

#include <stdio.h>
#include "fonctions.h"
#include "structures.h"


int main(int argc, const char *argv[]) {
    struct polynome poly1[6],poly2[6],poly3[6]; // le degré maximum est 5
    char chainea[100],chaineb[100];
    int deg1,deg2,deg3;
    char reponse;

    printf("Entrez votre premier polynôme\n");
    fgets(chainea, sizeof(chainea), stdin);

    deg1 = tabpoly(chainea, poly1, 5);
    if (deg1 < 0)
        
        if (deg1 == -1)
            printf("exposant trop grand\n");
        else if (deg1 == -2)
            printf("erreur de syntaxe\n");
        else
            printf("erreur\n");
    else
        afficher(poly1, deg1);
    
    printf("Entrez votre second polynôme\n");
    if (!fgets(chaineb, sizeof(chainea), stdin))
        return 1;

    deg2 = tabpoly(chaineb, poly2, 5);
    if (deg2 < 0)
        
        if (deg2 == -1)
            printf("exposant trop grand\n");
        else if (deg2 == -2)
            printf("erreur de syntaxe\n");
        else
            printf("erreur\n");
    else
        afficher(poly2, deg2);

    
     printf("\nVoulez-vous effectuer une addition ou une soustraction ? (A/S)\n");
      scanf("%c",&reponse);
          if (reponse == 'A' || reponse == 'a')
              polyadd(poly1, poly2, poly3, deg1, deg2);
          else if (reponse == 'S' || reponse == 's')
              polysub(poly1, poly2, poly3, deg1, deg2);
          else
              printf("Erreur de saisie\n");
    
      if (deg1 > deg2)
          deg3 = deg1;
      else
          deg3 = deg2;
    
      printf("\nle résultat est : \n");
      afficher(poly3, deg3);
      printf("\n");
    
    return 0;
}

