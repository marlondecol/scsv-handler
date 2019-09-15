#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>



#include "list.h"
#include "student.h"



struct node {
	int id;
	Student *student;
	Node *prev, *next;
};



List *lsCreate() {
	List *list = (List*) malloc(sizeof(List));

	if (list != NULL)
		*list = NULL;

	return list;
}



void lsDestroy(List *list) {
	if (list != NULL) {
		Node *node;

		while ((*list) != NULL) {
			node = *list;
			*list = (*list)->next;

			free(node);
		}

		free(list);
	}
}



int lsAddBegin(List *list, Student *student) {
	if (list == NULL)
		return 0;

	Node *node = (Node*) malloc(sizeof(Node));

	if (node == NULL)
		return 0;

	node->student = student;
	node->prev = NULL;
	node->next = *list;

	if (*list != NULL)
		(*list)->prev = node;
	
	*list = node;

	return 1;
}



int lsAddEnd(List *list, Student *student) {
	if (list == NULL)
		return 0;

	Node *node = (Node*) malloc(sizeof(Node));

	if (node == NULL)
		return 0;

	node->student = student;
	node->next = NULL;

	if (*list == NULL) {
		node->prev = NULL;
		*list = node;
	} else {
		Node *aux = *list;

		while (aux->next != NULL)
			aux = aux->next;

		aux->next = node;
		node->prev = aux;
	}

	return 1;
}



int lsAddSorted(List *list, Student *student) {
	if (list == NULL)
		return 0;

	Node *node = (Node*) malloc(sizeof(Node));

	if (node == NULL)
		return 0;

	node->student = student;

	if (lsIsEmpty(list)) {
		node->prev = NULL;
		node->next = NULL;
		
		*list = node;
	} else {
		Node *atual = *list;
		Node *prev;
		
		// Encaixa o nó na primeira ocorrência do nome do aluno...
		while (
			atual != NULL
			&& wcscmp(stGetName(student), stGetName(atual->student)) > 0
		) {
			prev = atual;
			atual = atual->next;
		}
		
		// ... e, enquanto o nome dos próximos alunos ainda for igual, ordena pela disciplina.
		while (
			atual != NULL
			&& wcscmp(stGetSubject(student), stGetSubject(atual->student)) >= 0
			&& wcscmp(stGetName(student), stGetName(atual->student)) == 0
		) {
			prev = atual;
			atual = atual->next;
		}

		// Inserção no início.
		if (atual == *list) {
			node->prev = NULL;
			(*list)->prev = node;
			node->next = (*list);
			*list = node;
		// Inserção no meio ou no final.
		} else {
			node->next = prev->next;
			node->prev = prev;
			prev->next = node;

			// Inserção no meio.
			if (atual != NULL)
				atual->prev = node;
		}
	}

	return 1;
}



int lsDelFirst(List *list) {
	if (lsIsEmpty(list))
		return 0;
	
	Node *node = *list;

	*list = node->next;

	if (node->next != NULL)
		node->next->prev = NULL;
	
	free(node);

	return 1;
}



int lsDelLast(List *list) {
	if (lsIsEmpty(list))
		return 0;
	
	Node *node = *list;
	
	while (node->next != NULL)
		node = node->next;
	
	if (node->prev == NULL)
		*list = node->next;
	else
		node->prev->next = NULL;
	
	free(node);

	return 1;
}



int lsDelById(List *list, int id) {
	if (list == NULL || id < 0)
		return 0;
	
	Node *node = *list;

	while (node != NULL && node->id != id)
		node = node->next;

	if (node == NULL)
		return 0;
	
	if (node->prev == NULL)
		*list = node->next;
	else
		node->next->prev = node->prev;
	
	if (node->next != NULL)
		node->next->prev = node->prev;
	
	free(node);

	return 1;
}



Node *lsGetPrevNode(Node *node) {
	if (node == NULL)
		return NULL;

	return node->prev;
}



Node *lsGetNextNode(Node *node) {
	if (node == NULL)
		return NULL;

	return node->next;
}



Student *lsGetStudent(List *list, Node *node) {
	if (lsIsEmpty(list))
		return NULL;
	
	if (node == NULL)
		return NULL;

	return node->student;
}



Student *lsGetFirstStudent(List *list) {
	if (lsIsEmpty(list))
		return NULL;
	
	return (*list)->student;
}



Student *lsGetLastStudent(List *list) {
	if (lsIsEmpty(list))
		return NULL;
	
	Node *node = *list;

	while (node->next != NULL)
		node = node->next;

	if (node == NULL)
		return NULL;
	
	return node->student;
}



Student *lsGetStudentById(List *list, int id) {
	if (list == NULL || id < 0)
		return NULL;
	
	Node *node = *list;

	while (node != NULL && node->id != id)
		node = node->next;

	if (node == NULL)
		return NULL;
	
	return node->student;
}



int lsIsEmpty(List *list) {
	return (list == NULL || *list == NULL);
}



int lsLength(List *list) {
	if (list == NULL)
		return 0;

	int length = 0;

	Node *node = *list;

	while (node != NULL) {
		node = node->next;
		length++;
	}

	return length;
}