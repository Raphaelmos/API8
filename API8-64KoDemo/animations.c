/*!\file animations.c
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

#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <GL4D/gl4dg.h>
#include <SDL_image.h>

/*!\brief identifiant de la géométrie QUAD GL4Dummies */
static GLuint _quadId = 0;
static int max = 10;
static int etat = 0;
static float steps = 5.0f;


void run_shaders(GLuint shaderId, GLuint quadId, float* time, float timeScale, Uint32* lastTimePtr) {
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (*lastTimePtr > 0) ? (currentTime - *lastTimePtr) / 1000.0f : 0.0f;
    *lastTimePtr = currentTime;
    *time += deltaTime * timeScale;
    glUseProgram(shaderId);
    glUniform1f(glGetUniformLocation(shaderId, "time"), *time);
    int width, height;
    SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &width, &height);
    glUniform2f(glGetUniformLocation(shaderId, "resolution"), (float) width, (float) height);
    gl4dgDraw(quadId);
    glUseProgram(0);
}
void strip(int state) {
    static float time = 0.0;
    static GLuint _pId = 0, _quadId = 0;
    static Uint32 lastTime = 0;
    switch (state) {
    case GL4DH_INIT:
        _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/strip.fs", NULL);
        _quadId = gl4dgGenQuadf();
        break;
    case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
    case GL4DH_DRAW:
        run_shaders(_pId, _quadId, &time, 1.0f, &lastTime);
        break;
    }
}

void rowling(int state) {
    static float time = 0.0;
    static GLuint _pId = 0, _quadId = 0;
    static Uint32 lastTime = 0;
    switch (state) {
    case GL4DH_INIT:
        _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/rowling.fs", NULL);
        _quadId = gl4dgGenQuadf();
        break;
    case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
    case GL4DH_DRAW:
        run_shaders(_pId, _quadId, &time, 1.5f, &lastTime);
        break;
    }
}

void tran(int state) {
    static float time = 0.0;
    static GLuint _pId = 0, _quadId = 0;
    static Uint32 lastTime = 0;
    switch (state) {
    case GL4DH_INIT:
        _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/tran.fs", NULL);
        _quadId = gl4dgGenQuadf();
        break;
    case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
    case GL4DH_DRAW:
        run_shaders(_pId, _quadId, &time, 1.5f, &lastTime);
        break;
    }
}

void bwhite(int state) {
    static float time = 0.0;
    static GLuint _pId = 0, _quadId = 0;
    static Uint32 lastTime = 0;
    switch (state) {
    case GL4DH_INIT:
        _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/bwhite.fs", NULL);
        _quadId = gl4dgGenQuadf();
        break;
    case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
    case GL4DH_DRAW:
        run_shaders(_pId, _quadId, &time, 1.5f, &lastTime);
        break;
    }
}

void mandelbro(int state) {
    static float time = 0.0;
    static GLuint _pId = 0, _quadId = 0;
    static Uint32 lastTime = 0;
    switch (state) {
    case GL4DH_INIT:
        _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mandelbro.fs", NULL);
        _quadId = gl4dgGenQuadf();
        break;
    case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
    case GL4DH_DRAW:
        run_shaders(_pId, _quadId, &time, 1.5f, &lastTime);
        break;
    }
}

void transit(int state) {
    static float time = 0.0;
    static GLuint _pId = 0, _quadId = 0;
    static Uint32 lastTime = 0;
    switch (state) {
    case GL4DH_INIT:
        _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/transit.fs", NULL);
        _quadId = gl4dgGenQuadf();
        break;
    case GL4DH_FREE: gl4dgDelete(_quadId); gl4duClean(GL4DU_ALL); break;
    case GL4DH_DRAW:
        run_shaders(_pId, _quadId, &time, 1.5f, &lastTime);
        break;
    }
}





void extransid(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}







void transition_fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default:
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}


void animation_mendel(int state) {
  static GLuint screen_id;
  switch(state) {
  case GL4DH_INIT:
    screen_id = gl4dpInitScreen();
    gl4dpUpdateScreen(NULL);
    return;
  case GL4DH_FREE:
  gl4dpSetScreen(screen_id);
  gl4dpDeleteScreen();
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
      gl4dpSetScreen(screen_id);
      mendel_anim();
      gl4dpUpdateScreen(NULL);
    return;
  }
}



void fondu(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void rouge(int state) {
  /* INITIALISEZ VOS VARIABLES */
  /* ... */
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return;
  }
}

void vert(int state) {
  /* INITIALISEZ VOS VARIABLES */
  /* ... */
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return;
  }
}

void bleu(int state) {
  /* INITIALISEZ VOS VARIABLES */
  /* ... */
  Sint16 * s;
  int l, i;
  GLfloat temp;
  static GLfloat intensite_de_bleu = 0.0f;
  switch(state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    return;
  case GL4DH_FREE:
  gl4dpDeleteScreen();
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Sint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    for(i = 0, temp = 0.0f; i < l / 2; i++) {
      temp += abs(s[i]) / (GLfloat)(1 << 15);
    }
    intensite_de_bleu = temp / (l / 4);
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    glClearColor(0.0f, 0.0f, intensite_de_bleu, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return;
  }
}

void animationsInit(void) {
  if(!_quadId)
    _quadId = gl4dgGenQuadf();
}

void mendel_anim(){
  mendel(max);
  if(max == 50){
    etat = 0;
  }
  if(max == 3){
    etat = 1;
  }

  if(etat == 0){
    --max;

  }
  if(etat == 1){
    ++max;

  }

  }

int HSBtoRGB(float hue, float saturation, float brightness) {
               int r = 0, g = 0, b = 0;
               if (saturation == 0) {
                   r = g = b = (int) (brightness * 255.0f + 0.5f);
               } else {
                   float h = (hue - (float)floor(hue)) * 6.0f;
                   float f = h - (float)floor(h);
                   float p = brightness * (1.0f - saturation);
                   float q = brightness * (1.0f - saturation * f);
                   float t = brightness * (1.0f - (saturation * (1.0f - f)));
                   switch ((int) h) {
                   case 0:
                       r = (int) (brightness * 255.0f + 0.5f);
                       g = (int) (t * 255.0f + 0.5f);
                       b = (int) (p * 255.0f + 0.5f);
                       break;
                   case 1:
                       r = (int) (q * 255.0f + 0.5f);
                       g = (int) (brightness * 255.0f + 0.5f);
                       b = (int) (p * 255.0f + 0.5f);
                       break;
                   case 2:
                       r = (int) (p * 255.0f + 0.5f);
                       g = (int) (brightness * 255.0f + 0.5f);
                       b = (int) (t * 255.0f + 0.5f);
                       break;
                   case 3:
                       r = (int) (p * 255.0f + 0.5f);
                       g = (int) (q * 255.0f + 0.5f);
                       b = (int) (brightness * 255.0f + 0.5f);
                       break;
                   case 4:
                       r = (int) (t * 255.0f + 0.5f);
                       g = (int) (p * 255.0f + 0.5f);
                       b = (int) (brightness * 255.0f + 0.5f);
                       break;
                   case 5:
                       r = (int) (brightness * 255.0f + 0.5f);
                       g = (int) (p * 255.0f + 0.5f);
                       b = (int) (q * 255.0f + 0.5f);
                       break;
                   }
               }
               return 0xff000000 | (r << 16) | (g << 8) | (b << 0);
}





void mendel(int max){
  int height = gl4dpGetHeight();
  int width =  gl4dpGetWidth();

  int color[max];
  for(int i =0;i< max;++i){
    color[i] = HSBtoRGB(i/256.f,1,i/(i+8.f));
  }


  float nouveauReel = 0;
  float nouveauIm =0;
  float reel = 0;
  float imaginaire = 0;


  for(int ligne = 0;ligne < height;++ligne){
    for(int col = 0;col < width;++col){
        float  cReel = 1.5 * (col - width / 2) / (0.5  * width);
        float  cImaginaire = (ligne - height / 2) / (0.5 * height);
        nouveauReel = nouveauIm = reel = imaginaire = 0;

          int i = 0;
          while (nouveauReel * nouveauReel + nouveauIm * nouveauIm <= 4 && i < max) {
            reel = nouveauReel;
            imaginaire = nouveauIm;
            nouveauReel = reel * reel - imaginaire * imaginaire + cReel;
            nouveauIm = 2 * reel * imaginaire + cImaginaire;
              i++;
            }

            if (i < max){
              gl4dpSetColor(color[i]);
              gl4dpPutPixel(col, ligne);
            }

            else{
              gl4dpSetColor(RGB(0,0,0));
              gl4dpPutPixel(col, ligne);
           }

    }
}


}