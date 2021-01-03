//
// Created by uwu on 11/26/2020.
//

#ifndef CSAUND_STORAGE_H
#define CSAUND_STORAGE_H

#include <stdlib.h>
#include <string.h>

// Empty item is assigned NULL ptr
typedef struct {
    unsigned short size;
    unsigned short elements;
    void** items;
} Bag;

Bag make_bag(int init_size);
unsigned short bag_insert(Bag* b, void* ptr);
unsigned short bag_delete(Bag* b, unsigned short index);
//void* bag_map(Bag* b, void* (*func)(void* item));

#endif //CSAUND_STORAGE_H
