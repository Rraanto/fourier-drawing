#ifndef NOMBRES_COMPLEXES_H
#define NOMBRES_COMPLEXES_H

/*
 * Définition du type complexe comme un couple d'entiers flottants (partie réelle et partie imaginaire)
 */
struct complexe {
  float re, im;
  complexe(float x, float y):re(x), im(y) {}
};

/* 
 * opérateurs sur les complexes 
 */
complexe operator + (const complexe &x, const complexe &y);

complexe operator * (const complexe &x, const complexe &y);

complexe operator - (const complexe &x, const complexe &y);


/*
 * Fonctions de calcul sur les complexes 
 */

/*
 * Calcule le conjugué d'un nombre complexe
 * argument: complexe z
 * valeur de retour: conjugué de z
 */
complexe conj(complexe z);

/*
 * Calcule le module d'un complexe z
 */
float mod(complexe z);

/*
 * Calcule l'argument d'un complexe z
 */
float arg(complexe z);

/*
 * Retourne le complexe a partir d'une forme polaire 
 */
complexe polar(float r, float theta);

/*
 * Fonctions d'entrées sorties / interactions avec l'utilisateurs sur les complexes
 */
void affiche(complexe z);
#endif


