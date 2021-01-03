//
// Created by uwu on 11/25/2020.
//

#include "math.h"
#include <math.h>
#define PI 3.14159265358979323846
double pitch(short relative) {
    return BASE_TUNE*(double)pow(2.0, (float)relative/12.0);
}

double sinewave(double s, double freq, double phase) {
    return sin(2.0*PI*freq*s+phase);
}