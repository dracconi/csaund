//
// Created by uwu on 11/25/2020.
//

#ifndef CSAUND_MATH_H
#define CSAUND_MATH_H

// Tuned for A4=440Hz
// C4=A4/2^(9/12)

#define BASE_TUNE 261.63

// Relative is relative 1/12th note
// Example
// C4=0
// A4=9
// C3=-12
double pitch(short relative);

double sinewave(double s, double freq, double phase);

#endif //CSAUND_MATH_H
