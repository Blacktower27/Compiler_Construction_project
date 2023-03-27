#pragma once
#include<stdio.h>
#include<string.h>
#include<malloc.h>

enum type { integer, boolean, type_error, _void, statement, lit, null };

//each symbol has three elements, value, atrribute,line
typedef struct Node
{
	int line;// line in the txt file 
	char attr[50];
	char tok[50];
	struct hash_node* idattr;
	struct Node * pNext;
}Node;//NODE==struct Node，PNODE==struct Node *

//Hash_table
typedef struct hash_node {
	char s[50];
	struct hash_node* next;
	enum type t;
}hash_node;

int hash(char* s);

void Display_symbol_table(hash_node table[101], int occupy[101]);

Node* first();

Node *add(char* attr, char* tok, int line, Node* preivous);

Node* addid(char* attr, char* tok, int line, Node* preivous, hash_node* node);

int DispList(Node *head);

void print_type(enum type t);
