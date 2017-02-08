/*
 * =====================================================================================
 *
 *       Filename:  arrayList.h
 *
 *    Description:  A test ArrayList implementation.
 *
 *        Version:  1.0
 *        Created:  07/02/17 09:03:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

typedef int (*Compare)(void* a, void* b);

struct ArrayList {
    int size;
    int capability;
    int element_size;
    Compare cmp;
    void **data;
};
struct ArrayList* arrayListCreate(int capability, Compare cmp); 
void arrayListDestrory(struct ArrayList **list); 
int arrayListClear(struct ArrayList* list);
int arrayListIsEmpty(struct ArrayList *list); 
int arrayListInsert(struct ArrayList* list, void* data); 
int arrayListInsertSorted(struct ArrayList* list, void *data); 
int arrayListDelete(struct ArrayList* list, void* data);
int arrayListInsertAt(struct ArrayList* list, int index, void* data); 
int arrayListDeleteAt(struct ArrayList* list, int index);
void* arrayListGetAt(struct ArrayList* list, int index); 
#endif /* __ARRAY_LIST_H__ */
