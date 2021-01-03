#include <stdio.h>
#include <stdlib.h>

#include "wav.h"
#include "synth/math.h"
#include "macros.h"
#include "synth/pipeline.h"
#include <math.h>

#include "primitives/instrument.h"

#define PLAYERS_N 1

typedef struct {
    short left_duration;
    short ix; // local index
    short jx; // global index
    Instrument i;
} Player;

typedef struct {
    int len;
    void* elements;
} Array;

Array Score[] = {
};

typedef struct {
    short length; // In 32ths
    short pitch; // if all 16 are set pause
} Interval;

Interval parse_note(char data) {
    char len = data&0x0f;
    char lmod = (len&0b1100)>>2;
    short length = (len&0b0011);
    char pitch = (data&0xf0)>>4;
    short rp = 0;
    if (pitch == 0) {
        rp = (short)0xff;
    } else {
        rp = (short)(pitch)-3;
    }
    return (Interval){
            .length = (32.0/pow(2.0, length))*(2-1.0/pow(2.0, lmod)),
            .pitch = rp
    };
}

double pipeline(PipelineState* ps, int sn) {
    Player *pls = (Player*)*(ps->dev);
    double x = (double)sn/44100;
    if (sn % 7350 == 0) {
        int index = 0;
        for (index=0; index<PLAYERS_N; index++) {
            Player player = *(pls+index);
            instrument_cleanup(&player.i, x);
            if (player.left_duration == 0) {
                if (rand()>0.6) {
                    if (player.jx-1 < sizeof(Score))
                        player.jx++;
                }
                Interval interval = parse_note(*((char*)(Score[player.jx].elements) + player.ix));
                if (interval.pitch != 0xff)
                    instrument_play(&player.i, x, interval.pitch);
                player.left_duration = interval.length;
                player.ix = (player.ix+1) % Score[player.jx].len;
            } else {
                player.left_duration--;
            }
            *(pls+index) = player;
        }
    }

    int index = 0;
    double sum = 0.0;
    for (index=0; index<PLAYERS_N; index++) {
        sum += instrument_sample(&((pls+index)->i), x);
    }

    return sum;
}

double modifier(double a, double r) {
    if (r<=0.1) {
        return 10 * r;
    }
    else if (r<=0.5) {
        return 1;
    } else if (r<=0.8) {
        return -(10.0/3)*r+2.6666;
    } else {
        return 0;
    }
}

double offset(double a, double r) {
    return 0.0;
}

double piano_wave(double x) {
    double a = fmod(x, 1.0);
    if (a <= 0.1632) {
        return -100*pow(a-0.1, 2) + 1;
    } else if (a <= 0.4576) {
        return 0.6;
    } else if (a <= 0.6882) {
        return 50*pow(a-0.625, 2)-0.8;
    } else if (a <= 0.8367) {
        return -0.6;
    } else if (a <= 1.0) {
        return 100*pow(a-0.9, 2)-1;
    }
}

Tone* make_tone(double origin, int relative) {
    Tone* t = (Tone*)malloc(sizeof(Tone));
    *t = (Tone){
        .origin = origin,
        .length = 1,
        .freq = pitch(relative)
    };
    return t;
}

double pianowave(double t, double freq, double phase) {
    return piano_wave(freq*t+phase);
}


int main() {
    printf("Hello, World!\n");

    /*
     * Notes are in binary format
     *
     * <pitch><length>LSB
     *
     * Length
     * 2^-x    Representation
     * 1      0x0
     * 2      0x1
     * 3      0x2
     * 4      0x3
     * ...
     * bxx000000
     *  ^^--- modifier (dotting)
     * 0 none
     * 1 dot
     * 2 double dot
     * 3 triple dot
     *
     * Pitch relative
     * pause    0x0
     * -3       0x1
     * -2       0x2
     * -1       0x3
     * 0 (C4)   0x4
     * 1        0x5
     * 2        0x6
     * 3        0x7
     * 4        0x8
     * 5        0x9
     * 6        0xa
     * 7        0xb
     * 8        0xc
     * 9        0xd
     * 10       0xe
     * 11       0xf
     * 12 (C5)
     */


    Score[0] = (Array){
        .len = 4,
        .elements = (char[]){0x62,0x62,0x62,0x02}
    };
    Score[1] = (Array){
        .len = 3,
        .elements = (char[]){0x63,0x73,0x62}
    };

    FILE* f = fopen("test.wav", "wb");
    WAV wav = {
            .sample_rate = 44100,
            .sample_size = 16,
            .samples_written = 0,
            .fd = f
    };
    int index = 0;
    Player players[PLAYERS_N];
    for (index = 0; index<PLAYERS_N; index++) {
        players[index] = (Player){
          .ix = 0,
          .jx = 0,
          .left_duration = 0
        };
        Instrument pinstr = make_instrument(&pianowave, &modifier, &offset, &make_tone);
        players[index].i = pinstr;
    }
    void** dev = (void**)malloc(sizeof(void*)*1);
    *dev = &players;

    PipelineState ps = (PipelineState){
        .dev = dev
    };

    wav_create(&wav);

    double samples = 44100.0*20;
    int i;
    for (i=0; i<samples; i++) {
        double sine = pipeline(&ps, i);
        signed short write = floor(12800*sine);
        char sample[4] = make_2_string(write);
        sample[2] = sample[0];
        sample[3] = sample[1];
        wav_writeSample(&wav, sample);
    }

    wav_finalize(&wav);

    fclose(f);

    return 0;
}
