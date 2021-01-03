//
// Created by uwu on 11/26/2020.
//

#ifndef CSAUND_INSTRUMENT_H
#define CSAUND_INSTRUMENT_H

#include "storage.h"

/*
 * Instrument provides API for creating tones.
 * Tones are stored in internal Bag struct, which provides a map function.
 *
 * Instrument provides API for sampling tones.
 * Tones from b are bag_mapped to instrument_tone
 * then this is summed (reduced).
 *
 * There is a function provided to clean-up Bag.
 * Tones which are finished are bag_deleted - ptr is set to NULL.
 */

typedef struct {
    double origin;
    double freq;
    double length; // -1 for indefinite
} Tone;

typedef struct {
    double (*mod)(double, double); // absolute, relative
    double (*offset)(double, double); // abs, rel
    double (*wave)(double, double, double); // abs, freq, phase

    Tone* (*make_tone)(double, int);

    Bag b;
} Instrument;

Instrument make_instrument(double (*wave)(double, double, double),
                           double (*mod)(double, double),
                           double (*offset)(double, double),
                           Tone* (*make_tone)(double, int));
double instrument_sample(Instrument* i, double x); // wave*mod+offset
short instrument_cleanup(Instrument* i, double t);
void instrument_play(Instrument* i, double t, int relative);

#endif //CSAUND_INSTRUMENT_H
