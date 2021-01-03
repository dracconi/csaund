//
// Created by uwu on 11/25/2020.
//

#ifndef CSAUND_DETACHED_H
#define CSAUND_DETACHED_H

typedef enum DetachedFlags {
    D_STOPPED,
    D_RUNNING
} DetachedFlags;

// A detached function state
typedef struct DetachedState {
    double origin;
    double (*func)(double);
    char flags;
} DetachedState;

double detached(DetachedState ds, double t);

#endif //CSAUND_DETACHED_H
