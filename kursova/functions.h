#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

// структура на един елемент - маршрут
typedef struct NODE
{
    char start_point[20];
    char end_point[20];
    float duration;
    float distance;

    struct NODE * next;
} NODE;

// прототипи на функциите
NODE* create_list(void);
NODE* create_node(NODE* root, NODE info);
void printList(NODE* root);
void printEntry(NODE* temp);
void change_entry(NODE* root);
NODE * add_new(NODE* root);
void findFastestRoute(NODE* root);
void findShortestRoute(NODE* root);
NODE* delete_node(NODE* root);
void exitProgramm(NODE* root);

#endif // FUNCTIONS_H_INCLUDED
