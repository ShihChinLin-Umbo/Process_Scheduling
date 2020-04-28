#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"

HEAP_NODE* insert_node_sjf(HEAP_NODE* head, Process p, int priority, int index){
	HEAP_NODE *new;
	if(head == NULL){
		head = (HEAP_NODE *)malloc(sizeof(HEAP_NODE));
		head->p = p;
		head->priority = priority;
		head->index = index;
		head->size = 0;
		head->left = NULL;
		head->right = NULL;
		head->parent = NULL;
		return head;
	}
	if(head->left == NULL){
		new = (HEAP_NODE *)malloc(sizeof(HEAP_NODE));
		new->p = p;
		new->priority = priority;
		new->index = index;
		new->size = 0;
		new->left = NULL;
		new->right = NULL;
		new->parent = head;
		head->left = new;
		head->size++;
		return new;
	}
	if(head->right == NULL){
		new = (HEAP_NODE *)malloc(sizeof(HEAP_NODE));
		new->p = p;
		new->priority = priority;
		new->index = index;
		new->size = 0;
		new->left = NULL;
		new->right = NULL;
		new->parent = head;
		head->right = new;
		head->size++;
		return new;
	}
	if(head->left->size <= head->right->size){
		head->size++;
		new = insert_node_sjf(head->left, p, priority, index);
	}
	else{
		head->size++;
		new = insert_node_sjf(head->right, p, priority, index);
	}
	return new;
}

void swap_node_sjf(HEAP_NODE* a, HEAP_NODE* b){
	int temp_size;
	temp_size = a->size;
	a->size = b->size;
	b->size = temp_size;

	HEAP_NODE *temp;
	temp = (HEAP_NODE *)malloc(sizeof(HEAP_NODE));
	temp->left = a->left;
	temp->right = a->right;

	if(a == b->left){
		a->left = b;
		a->right = b->right;
		if(a->right != NULL)
			a->right->parent = a;
	}
	else{
		a->left = b->left;
		if(a->left != NULL)
			a->left->parent = a;
		a->right = b;
	}
	a->parent = b->parent;

	b->left = temp->left;
	b->right = temp->right;
	free(temp);
	b->parent = a;

	if(a->parent != NULL){
		if(a->parent->left == b){
			a->parent->left = a;
		}
		else{
			a->parent->right = a;
		}
	}
	if(b->left != NULL)
		b->left->parent = b;
	if(b->right != NULL)
		b->right->parent = b;
	return;
}

HEAP_NODE* sort_node_sjf(HEAP_NODE* head, HEAP_NODE* new){
	if(new == head)
		return head;
	if(new->parent == head && (new->priority < head->priority || (new->priority == head->priority && new->index < head->index))){
		swap_node_sjf(new, head);
		return new;
	}
	if(new->priority < new->parent->priority || (new->priority == new->parent->priority && new->index < new->parent->index)){
		swap_node_sjf(new, new->parent);
		head = sort_node_sjf(head, new);
	}
	return head;
}

HEAP_NODE* up_sjf(HEAP_NODE* head, HEAP_NODE* min, int size, int left_right){
	HEAP_NODE *temp;
	temp = (HEAP_NODE *)malloc(sizeof(HEAP_NODE));
	temp->left = min->left;
	temp->right = min->right;
	temp->size = min->size;
	min->size = size - 1;
	if(left_right == 0){
		min->right = head->right;
		if(min->right != NULL)
			min->right->parent = min;
		if(temp->left == NULL && temp->right == NULL){
			min->left = NULL;
		}
		else if(temp->left == NULL){
			min->left = temp->right;
		}
		else if(temp->right == NULL){
			min->left = temp->left;
		}
		else{
			if(temp->left->priority < temp->right->priority || (temp->left->priority == temp->right->priority && temp->left->index < temp->right->index)){
				min->left = up_sjf(min, temp->left, temp->size, 0);
			}
			else{
				min->left = up_sjf(min, temp->right, temp->size, 1);
			}
		}
		if(min->left != NULL){
			min->left->parent = min;
		}
	}
	else{
		min->left = head->left;
		if(min->left != NULL)
			min->left->parent = min;
		if(temp->left == NULL && temp->right == NULL){
			min->right = NULL;
		}
		else if(temp->left == NULL){
			min->right = temp->right;
		}
		else if(temp->right == NULL){
			min->right = temp->left;
		}
		else{
			if(temp->left->priority < temp->right->priority || (temp->left->priority == temp->right->priority && temp->left->index < temp->right->index)){
				min->right = up_sjf(min, temp->left, temp->size, 0);
			}
			else{
				min->right = up_sjf(min, temp->right, temp->size, 1);
			}
		}
		if(min->right != NULL){
			min->right->parent = min;
		}
	}
	free(temp);
	return min;
}

void print_heap_sjf(HEAP_NODE *head){
	if(head == NULL)
		return;
	printf("Index: %d, Priority: %d, Size: %d\n", head->index+1, head->priority, head->size);
	printf("left\n");
	print_heap_sjf(head->left);
	printf("right\n");
	print_heap_sjf(head->right);
	return;
}

HEAP_NODE* heap_push_sjf(HEAP_NODE* head, Process p, int priority, int index){
	HEAP_NODE *new = insert_node_sjf(head, p, priority, index);
	if(head == NULL){
		head = new;
	}
	HEAP_NODE *min = sort_node_sjf(head, new);
	return min;
}

HEAP_NODE* heap_pop_sjf(HEAP_NODE* head){
	if(head == NULL)
		return NULL;

	HEAP_NODE *pop = head;
	if(head->left == NULL && head->right == NULL){
		;
	}
	else if(head->right == NULL){
		head = head->left;
	}
	else if(head->left == NULL){
		head = head->right;
	}
	else{
		if(head->left->priority < head->right->priority || (head->left->priority == head->right->priority && head->left->index < head->right->index)){
			head = up_sjf(head, head->left, head->size, 0);
		}
		else{
			head = up_sjf(head, head->right, head->size, 1);
		}
	}
	head->pop = pop;
	return head;
}