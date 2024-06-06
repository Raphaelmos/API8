/*!\file animations.h
 *
 * \brief Votre espace de liberté : c'est ici que vous pouvez ajouter
 * vos fonctions de transition et d'animation avant de les faire
 * référencées dans le tableau _animations du fichier \ref window.c
 *
 * Des squelettes d'animations et de transitions sont fournis pour
 * comprendre le fonctionnement de la bibliothèque. En bonus des
 * exemples dont un fondu en GLSL.
 *
 * \author Farès BELHADJ, amsi@up8.edu
 * \date April 12, 2023
 */
#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif
  typedef struct{
  double x;
  double y;
  }point;

  #define MAX_STEPS 500000

  void mendel(int max);
  void mendel_anim();
  extern void animation_mendel(int state);
  extern void strip(int state);
  extern void rowling(int state);
  extern void tran(int state);
  extern void bwhite(int state);
  extern void mandelbro(int state);
  extern void transit(int state);
  extern void animcercle(int state);
  extern void extransid(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void rouge(int state);
  extern void vert(int state);
  extern void bleu(int state);
  extern void animationsInit(void);
  /* depuis dancing_cubes.c */
  extern void dancing_cubes(int state);
  extern void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void credit_debut(int state);
  extern void credit_fin(int state);

#ifdef __cplusplus
}
#endif

#endif
