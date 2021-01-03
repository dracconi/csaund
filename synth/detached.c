//
// Created by uwu on 11/25/2020.
//

#include "detached.h"
#include "piano.h"

double detached(DetachedState ds, double t) {
    if (ds.flags == D_RUNNING)
        return ds.func(t-ds.origin);
    return 0.0;
}
