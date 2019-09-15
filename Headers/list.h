#ifndef _LIST_H
#define _LIST_H



#include "student.h"



typedef struct node Node;

typedef Node *List;



List *lsCreate();

void lsDestroy(List *list);

int lsAddBegin(List *list, Student *student);

int lsAddEnd(List *list, Student *student);

int lsAddSorted(List *list, Student *student);

int lsDelFirst(List *list);

int lsDelLast(List *list);

int lsDelById(List *list, int id);

Node *lsGetPrevNode(Node *node);

Node *lsGetNextNode(Node *node);

Student *lsGetStudent(List *list, Node *node);

Student *lsGetFirstStudent(List *list);

Student *lsGetLastStudent(List *list);

Student *lsGetStudentById(List *list, int id);

int lsIsEmpty(List *list);

int lsLength(List *list);



#endif