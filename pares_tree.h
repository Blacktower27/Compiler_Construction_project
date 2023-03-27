#pragma once
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>
#include"symbol_table.h"

typedef struct tree_node
{
	char name[50];
	int numOfChild;
	struct hash_node* idattr;
	struct tree_node* child[15];
	enum type t;
}tree_node;

tree_node* create_Terminal_Node(char name[50],struct hash_node* idattr);

tree_node* create_Nonterminal_Node(int numOfChild, tree_node* child[15], char name[50], enum type t);

void print_Tree(char* prefix, tree_node* node, bool inFirst);

enum type type_Checking(int rule, tree_node* child[15]);