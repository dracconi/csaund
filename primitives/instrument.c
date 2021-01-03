//
// Created by uwu on 11/26/2020.
//

#include "instrument.h"

Instrument make_instrument(double (*wave)(double, double, double),
                           double (*mod)(double, double),
                           double (*offset)(double, double),
                           Tone* (*make_tone)(double, int)) {
    return (Instrument){
        .wave = wave,
        .mod = mod,
        .offset = offset,
        .make_tone = make_tone,
        .b = make_bag(16)
        };
}

void instrument_play(Instrument* i, double t, int relative) {
    Tone* tone = i->make_tone(t, relative);
    bag_insert(&(i->b), tone);
}

short instrument_cleanup(Instrument* i, double t) {
    int ix = i->b.elements;
    short jx = 0;
    short removed = 0;
    while (ix > 0) {
        if (i->b.items[jx] != NULL) {
            Tone* tone = (Tone*)(i->b.items[jx]);
            if (tone->length < t - tone->origin) {
                bag_delete(&i->b, jx);
                removed++;
            }
            ix--;
        }
        jx++;
    }
    return removed;
}

double tone_sample(Instrument* i, Tone tone, double t) {
    if (t-tone.origin <= tone.length) {
        return i->wave(t, tone.freq, t - tone.origin) * i->mod(t, t - tone.origin) + i->offset(t, t - tone.origin);
    } else {
        return 0.0;
    }
}

double instrument_sample(Instrument* i, double t) {
    int ix = i->b.elements;
    short jx = 0;
    double sum = 0.0;
    while (ix > 0) {
        if (i->b.items[jx] != NULL) {
            Tone* tone = (Tone*)(i->b.items[jx]);
            sum = sum + tone_sample(i, *tone, t);
            ix--;
        }
        jx++;
    }
    return sum;
}
