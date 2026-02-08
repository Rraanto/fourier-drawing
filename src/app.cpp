#include "app.h"

#include <GL/glut.h>

#include <cstdio>
#include <cstdlib>

#include "fourier.h"
#include "utils.h"

#define GAP 25

namespace {
AppState *g_state = nullptr;

void displayCallback() {
  if (g_state != nullptr) {
    renderFrame(*g_state);
  }
}

void keyboardCallback(unsigned char key, int x, int y) {
  if (g_state != nullptr) {
    handleKeyboard(key, x, y, *g_state);
  }
}

void timerCallback(int value) {
  if (g_state != nullptr) {
    updateVectorPosition(value, *g_state);
  }
}
} // namespace

void registerAppCallbacks(AppState &state) {
  g_state = &state;
  glutDisplayFunc(displayCallback);
  glutKeyboardFunc(keyboardCallback);
  glutTimerFunc(state.timer_msecs, timerCallback, 0);
  glutPostRedisplay();
}

void renderFrame(AppState &state) {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);
  if (state.show_original_image) {
    plotSignal(state.signal);
  }

  glColor3f(0.2, 0.2, 0.2);
  plotAxis(-1000, 1000, -1000, 1000);

  glColor3f(0.0, 0.8, 0.6);
  if (state.show_text) {
    double gap = GAP;
    double left = -250.0;
    double right = 250.0;
    double top = 400;
    void *font = GLUT_BITMAP_HELVETICA_18;
    char tmp[128];

    snprintf(tmp, sizeof(tmp), "signal de depart contenant: %d points",
             (int)state.signal.size());
    printText(right, top, font, tmp);

    snprintf(tmp, sizeof(tmp), "N = %d", state.nb_coeffs);
    printText(left, top, font, tmp);

    snprintf(tmp, sizeof(tmp), "r: activer rotation (%d)", state.is_rotating);
    printText(left, top - gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "j/k: ajouter/reduire coefficients");
    printText(left, top - 2 * gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "o: afficher original (%d)",
             state.show_original_image);
    printText(left, top - 3 * gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "t: afficher approximation (%d)",
             state.pre_plot_trace);
    printText(left, top - 4 * gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "v: afficher epicycles (%d)",
             state.show_vectors);
    printText(left, top - 5 * gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "s/f: ralentir/accelerer");
    printText(right, top - gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "RPS %d", 1000 / state.timer_msecs);
    printText(right, top - 2 * gap, font, tmp);

    snprintf(tmp, sizeof(tmp), "h: afficher/masquer aide");
    printText(right, top - 3 * gap, font, tmp);
  }

  if (state.show_vectors) {
    renderVectors(state.coefficients, state.rotating_t);
  }

  if (state.pre_plot_trace) {
    plotSignal(state.approx_trace);
  }

  glFlush();
}

void handleKeyboard(unsigned char key, int x, int y, AppState &state) {
  (void)x;
  (void)y;

  switch (key) {
  case 'r':
    state.is_rotating = state.is_rotating ? 0 : 1;
    glutPostRedisplay();
    break;
  case 'j':
    state.nb_coeffs = (state.nb_coeffs > 5) ? state.nb_coeffs - 5 : 5;
    state.coefficients = tdf(state.signal, state.nb_coeffs);
    state.approx_trace = computePoints(state.signal, state.coefficients);
    glutPostRedisplay();
    break;
  case 'k':
    state.nb_coeffs = state.nb_coeffs + 5;
    state.coefficients = tdf(state.signal, state.nb_coeffs);
    state.approx_trace = computePoints(state.signal, state.coefficients);
    glutPostRedisplay();
    break;
  case 'o':
    state.show_original_image = state.show_original_image ? 0 : 1;
    glutPostRedisplay();
    break;
  case 't':
    state.pre_plot_trace = state.pre_plot_trace ? 0 : 1;
    glutPostRedisplay();
    break;
  case 'v':
    state.show_vectors = state.show_vectors ? 0 : 1;
    glutPostRedisplay();
    break;
  case 'f':
    if (state.timer_msecs - 100 <= 0) {
      state.timer_msecs = 1;
    } else {
      state.timer_msecs = state.timer_msecs - 5;
    }
    glutPostRedisplay();
    break;
  case 's':
    state.timer_msecs = state.timer_msecs + 5;
    break;
  case 'h':
    state.show_text = state.show_text ? 0 : 1;
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  }
}

void updateVectorPosition(int value, AppState &state) {
  (void)value;
  glutTimerFunc(state.timer_msecs, timerCallback, 1);
  if (state.is_rotating) {
    state.rotating_t = state.rotating_t + state.delta;
    glutPostRedisplay();
  }
}
