#ifndef ___INTSTACK_H
#define ___INTSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
int max;
int ptr;
int *stk;
} Intstack;

int initialize (Intstack *s,int max);
int push (Intstack *s,int x);
int pop (Intstack *s,int *x);
int peek (Intstack *s,int *x);
int clear (Intstack *s);
int capacity (const Intstack *s);
int size (const Intstack *s);
int is_empty (const Intstack *s);
int is_full (const Intstack *s);
int search (const Intstack *s,int x);
int print (const Intstack *s);
void terminate (Intstack *s);

#endif //___INTSTACK_H