//
// Created by uwu on 11/25/2020.
//

#include "math.h"
#include "piano.h"
#include <stdlib.h>
#include <string.h>

double play_note(Note* n, double t) {
    return sinewave(t, pitch(n->relative), 0.0) * detached(n->ds, t);
}

double ramp(double t) {
    if (t<=0.1) {
        return 10 * t;
    }
    else if (t<=0.2) {
        return 1;
    } else if (t<=0.8) {
        return -(1.0/0.6)*t+4.0/3.0;
    } else {
        return 0;
    }
}

Note make_note(short relative) {
    return (Note){
      .relative = relative,
      .ds = (DetachedState){
          .origin = 0.0,
          .flags = D_STOPPED,
          .func = &ramp
      }
    };
}

double play_piano(Piano* p, double t) {
    double s = 0.0;
    int i;
    for(i=0; i<13; i++) {
        s += play_note(&p->notes[i], t);
    }
    return s;
}

Piano make_piano() {
    Piano p = (Piano){};
    int i;
    for(i=0; i<13; i++) {
        p.notes[i] = make_note(i);
    }
    return p;
}

void play_key(Piano* p, short key, double t) {
    p->notes[key].ds.origin = t;
    p->notes[key].ds.flags = D_RUNNING;
}

