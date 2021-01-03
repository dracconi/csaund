//
// Created by uwu on 11/25/2020.
//

#include "wav.h"
#include "macros.h"

#define m_fwrite(fd, s) fwrite(s, sizeof(char), sizeof(s)-1, fd)


int wav_create(WAV* ptr) {
    m_fwrite(ptr->fd, "RIFF0000WAVEfmt 0000\1\0\2\0");
    const char sample_rate[] = make_4_string(ptr->sample_rate);
    fwrite(sample_rate, sizeof(unsigned int), 1, ptr->fd);
    const char byte_rate[] = make_4_string(ptr->sample_rate*2*ptr->sample_size/8);
    fwrite(byte_rate, sizeof(unsigned int), 1, ptr->fd);
    const char block_align[] = make_2_string(2*ptr->sample_size/8);
    fwrite(block_align, sizeof(short), 1, ptr->fd);
    const char sample_size[] = make_2_string(ptr->sample_size);
    fwrite(sample_size, sizeof(short), 1, ptr->fd);
    m_fwrite(ptr->fd, "data0000");

    return 0;
}

int wav_writeSample(WAV* ptr, char* sample) {
    fwrite(sample, sizeof(char), 2*ptr->sample_size/8, ptr->fd);
    ptr->samples_written++;
}

int byte_length(WAV* ptr) {
    return ptr->samples_written * 2 * ptr->sample_size / 8;
}

int wav_finalize(WAV* ptr) {
    fseek(ptr->fd, 4, SEEK_SET);
    const char byte_len[] = make_4_string(byte_length(ptr)-8+44);
    fwrite(byte_len, sizeof(char), 4, ptr->fd);
    fseek(ptr->fd, 16, SEEK_SET);
    const char byte_len_fmt[] = make_4_string(16);
    fwrite(byte_len_fmt, sizeof(char), 4, ptr->fd);
    fseek(ptr->fd, 40, SEEK_SET);
    const char byte_len_data[] = make_4_string(byte_length(ptr));
    fwrite(byte_len_data, sizeof(char), 4, ptr->fd);
}

