#ifndef APP_H
#define APP_H

#include <complex>
#include <vector>

using std::complex;
using std::vector;

struct AppState {
  /*
   * container for state variables of the app
   */
  vector<complex<double>> signal;
  vector<complex<double>> coefficients;
  vector<complex<double>> approx_trace;

  int nb_coeffs = 5; // ddefault amount of vects to start with
  double rotating_t =
      0.0; // a global time: implies vectos positions r.exp(i a(t) )
  double delta = 0.0;
  int is_rotating = 0;
  int show_original_image = 1;
  int pre_plot_trace = 1;
  int show_vectors = 0;
  int timer_msecs = 5;
  int show_text = 1;
};

void registerAppCallbacks(AppState &state);
void renderFrame(AppState &state);
void handleKeyboard(unsigned char key, int x, int y, AppState &state);
void updateVectorPosition(int value, AppState &state);

#endif
