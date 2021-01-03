//
// Created by uwu on 11/25/2020.
//

#ifndef CSAUND_PIANO_H
#define CSAUND_PIANO_H

#include "detached.h"

// relative
// origin
typedef struct Note {
    short relative;
    DetachedState ds;
} Note;

double play_note(Note* n, double t);

// currently_playing notes => Note[]
// synthesis function =>
// ramp function =>
typedef struct Piano {
    Note notes[13];
} Piano;

double play_piano(Piano* p, double t);
Piano make_piano();
Note make_note(short relative);

void play_key(Piano* p, short key, double t);
double ramp(double t);
#endif //CSAUND_PIANO_H
