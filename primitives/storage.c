//
// Created by uwu on 11/26/2020.
//

#include "storage.h"

Bag make_bag(int init_size) {
    void** items = malloc(sizeof(void*)*init_size);
    memset(items, NULL, init_size);
    return (Bag){
            .size = init_size,
            .items = items,
            .elements = 0
    };
}

unsigned short bag_insert(Bag *bag, void* element) {
    if(bag->size == bag->elements) {
        bag->items = malloc(bag->size++ * sizeof(void *));
        bag->items[bag->size-1] = element;
        bag->elements++;
        return bag->elements;
    }
    int ix = 0;
    for (ix = 0; ix < bag->size; ix++) {
        if (bag->items[ix] == NULL) {
            bag->items[ix] = element;
            bag->elements++;
            return bag->elements;
        }
    }
}

unsigned short bag_delete(Bag *bag, unsigned short index) {
    free(bag->items[index]);
    bag->items[index] = NULL;
    bag->elements--;
    return bag->elements;
}