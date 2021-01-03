cmake_minimum_required(VERSION 3.17)
project(csaund C)

set(CMAKE_C_STANDARD 99)

add_executable(csaund main.c wav.h wav.c synth/math.h synth/math.c macros.h synth/pipeline.h synth/detached.h synth/detached.c synth/piano.c synth/piano.h primitives/instrument.c primitives/instrument.h primitives/storage.c primitives/storage.h)