//
// Created by uwu on 11/25/2020.
//

#ifndef CSAUND_MACROS_H
#define CSAUND_MACROS_H
#ifdef LITTLE_ENDIAN
#define make_2_string(binary) {(char)(binary>>8), (char)(binary)}
#define make_4_string(binary) {(char)(binary>>24), (char)(binary>>16), (char)(binary>>8), (char)(binary)}
#else
#define make_2_string(binary) {(char)(binary), (char)(binary>>8)}
#define make_4_string(binary) {(char)(binary), (char)(binary>>8), (char)(binary>>16), (char)(binary>>24)}
#endif
#endif //CSAUND_MACROS_H
