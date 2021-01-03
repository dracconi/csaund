//
// Created by uwu on 11/25/2020.
//

#include <stdio.h>

#ifndef CSAUND_WAV_H
#define CSAUND_WAV_H

struct WAV {
    unsigned int sample_rate;
    short channel_num;
    short block_align;
    short sample_size;
    long samples_written;
    FILE* fd;
};

typedef struct WAV WAV;

int wav_create(WAV* ptr);
int wav_writeSample(WAV* ptr, char* sample);
int wav_finalize(WAV* ptr);

#endif //CSAUND_WAV_H
