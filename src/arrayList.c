/*
 * =====================================================================================
 *
 *       Filename:  arrayList.c
 *
 *    Description:  This is my practise dynamic array implementation.
 *
 *        Version:  1.0
 *        Created:  07/02/17 07:20:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "arrayList.h"

#define ARRAY_LIST_SIZE_FACTOR          2
#define ARRAY_LIST_DEFAULT_CAPBILITY  1000

struct ArrayList*
arrayListCreate(int capability, Compare cmp) {
    struct ArrayList* new = NULL;

    if(cmp == NULL)
        return NULL;

    new = (struct ArrayList *)malloc(sizeof(struct ArrayList));
    if (new == NULL)
        return NULL;

    if (capability <= 0)
        capability = ARRAY_LIST_DEFAULT_CAPBILITY;

    new->data = malloc(sizeof(void *) * capability);
    if (new->data == NULL) {
        free(new);
        return NULL;
    }

    memset(new->data, 0, sizeof(void*) * capability);
    new->size = 0;
    new->capability = capability;
    new->cmp = cmp;

    return new;
}

void 
arrayListDestroy(struct ArrayList **list) {
    if (*list == NULL)
        return;

    if ((*list)->data != NULL)
        free((*list)->data);

    free(*list);
    *list = NULL;

    return;
}

int
arrayListIsEmpty(struct ArrayList *list) {
    if (list == NULL || list->data == NULL)
        return 0;

    return list->size == 0;
}

int 
arrayListInsert(struct ArrayList* list, void* data) {
    if (list == NULL || list->data == NULL)
        return -1;

    return arrayListInsertAt(list, list->size, data);
}

int
arrayListInsertSorted(struct ArrayList* list, void *data) {
    int position = 0;

    if (list == NULL || list->data == NULL)
        return -1;

    position = list->size;
    while (position > 0) {
        if (list->cmp(list->data[position-1], data) > 0) {
            position--;
            continue;
        }
        break;
    }
    return arrayListInsertAt(list, position, data);
}

int 
arrayListDelete(struct ArrayList* list, void* data) {
    int i = 0;

    if (list == NULL || list->data == NULL || data == NULL)
        return -1;

    while (i < list->size) {
        if (list->cmp(list->data[i], data) != 0) {
            i++;
            continue;
        }
        arrayListDeleteAt(list, i);
    }

    return 0;
}

int
arrayListInsertAt(struct ArrayList* list, int index, void* data) {
    int tmp = 0;
    void* new = NULL;

    if (list == NULL || list->data == NULL || index < 0 || index > list->size)
        return -1;

    if (list->size >= list->capability) {
        new = malloc(sizeof(void *) * list->capability * ARRAY_LIST_SIZE_FACTOR);
        if (new == NULL)
            return -1;
        memcpy(new, list->data, (list->size * sizeof(void*)));
        free(list->data);
        list->data= new;
        list->capability *= ARRAY_LIST_SIZE_FACTOR;
    }

    tmp = list->size;
    while(tmp > index) {
        list->data[tmp] = list->data[tmp-1];
        tmp--;
    }

    list->data[index] = data;
    list->size++;
    return 0;
}

int 
arrayListDeleteAt(struct ArrayList* list, int index) {
    void* new = NULL;

    if (list == NULL || list->data == NULL || index < 0 || list->size == 0)
        return -1;

    memmove(&list->data[index], &list->data[index+1], sizeof(void *) * (list->size-index-1));
    list->size--;

    if (list->capability > ARRAY_LIST_DEFAULT_CAPBILITY && list->size < list->capability / ARRAY_LIST_SIZE_FACTOR) {
        new = malloc(sizeof(void *) * (list->capability / ARRAY_LIST_SIZE_FACTOR));
        if (new == NULL)
            return 0;

        memcpy(new, list->data, list->size);
        free(list->data);
        list->data = new;
        list->capability /= ARRAY_LIST_SIZE_FACTOR;
    }

    return 0;
}

void* 
arrayListGetAt(struct ArrayList* list, int index) {
    if (list == NULL || list->data == NULL || index < 0 || index >= list->size)
        return NULL;

    return list->data[index];
}

int
arrayListClear(struct ArrayList *list) {
    void* new = NULL;

    if (list == NULL || list->data == NULL)
        return -1;

    new = malloc(sizeof(void *) * ARRAY_LIST_DEFAULT_CAPBILITY);
    if (new == NULL) {
        return -1;
    }

    free(list->data);
    list->data = new;
    list->capability = ARRAY_LIST_DEFAULT_CAPBILITY;
    list->size = 0;

    return 0;
}
