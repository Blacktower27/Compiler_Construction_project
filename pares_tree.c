#include"pares_tree.h"

tree_node* create_Terminal_Node(char name[50], hash_node* idattr) {
	tree_node* node;
	node = (tree_node*)malloc(sizeof(tree_node));
	node->numOfChild = 0;
	memset(node->child, 0, 15);
	for (int i = 0; i <= strlen(name); i++)
		node->name[i] = name[i];
	node->idattr = idattr;
	node->t = null;
	return node;
}

tree_node* create_Nonterminal_Node(int numOfChild, tree_node* child[15], char name[50], enum type t) {
	tree_node* node;
	node = (tree_node*)malloc(sizeof(tree_node));
	node->numOfChild = numOfChild;
	memset(node->child, 0, 15);
	for (int i = 0; i < numOfChild; i++)
		node->child[i] = child[i];
	for (int i = 0; i <= strlen(name); i++)
		node->name[i] = name[i];
	node->idattr = NULL;
	node->t = t;
	return node;
}

void print_Tree(char* prefix, tree_node* node, bool hasNext) {
	char a[5];
	char b[5];
	a[0] = ' ';
	b[0] = '|';
	for (int i = 1; i < 4; i++) {
		a[i] = ' ';
		b[i] = ' ';
	}
	a[4] = '\0';
	b[4] = '\0';
	if (node != NULL) {
		printf("%s", prefix);
		printf("|---");
		printf("%s", node->name);
		if(node->t != null && node->t != statement && node->t != _void){
			printf(" [");
			print_type(node->t);
			printf("]");
		}
		printf("\n");
		char* c = (char*)malloc(strlen(a) + strlen(prefix) + 1);
		int index = 0;
		for (int i = 0; i < strlen(prefix); i++){
			*(c + i) = prefix[i];
			index++;
		}
		if (hasNext) {
			for (int i = 0; i < strlen(a); i++){
				*(c + index + i) = b[i];
			}
		}
		else {
			for (int i = 0; i < strlen(b); i++) {
				*(c + index + i) = a[i];
			}
		}
		*(c + strlen(a) + strlen(prefix)) = '\0';
		for (int i = 0; i < node->numOfChild; i++){
			if (node->numOfChild - i > 1)
				hasNext = 1;
			else
				hasNext = 0;
			print_Tree(c, node->child[i], hasNext);
		}
	}
}

enum type type_Checking(int rule, tree_node* child[15]){
	switch (rule){
	case 1:
		return statement;
		break;
	case 2:
		return statement;
		break;
	case 3:
		return statement;
		break;
	case 4:
		child[1]->idattr->t = integer;
		return _void;
		break;
	case 5:
		child[1]->idattr->t = boolean;
		return _void;
		break;
	case 6:
		if (child[0]->idattr->t == child[2]->t)
			return _void;
		else if (child[0]->idattr->t == integer)
			return _void;
		return type_error;
		break;
	case 7:
	case 8:
	case 10:
	case 11:
		if (child[0]->t == child[2]->t || child[2]->t == boolean)
			return integer;
		return type_error;
		break;
	case 9:
	case 12:
		return child[0]->t;
		break;
	case 13:
		return child[1]->t;
		break;
	case 14:
		return child[0]->idattr->t;
		break;
	case 15:	//F->lit
		if (child[0]->name[0] == 'b' && child[0]->name[1] == 'o')
			return boolean;
		else
			return integer;
		break;
	case 16:
	case 17:
	case 18:
	case 19:
		return statement;
		break;
	case 20:
	case 21:
		if (child[2]->t == boolean)
			return child[5]->t;
		return type_error;
		break;
	case 22:
	case 24:
		if (child[0]->t == boolean && child[2]->t == boolean)
			return boolean;
		return type_error;
		break;
	case 23:
	case 25:
		return child[0]->t;
		break;
	case 26:
		if (child[1]->t == boolean)
			return boolean;
		return type_error;
		break;
	case 27:
	case 29:
		return child[0]->t;
		break;
	case 28:
		return child[1]->t;
		break;
	case 30:
		if (child[0]->idattr->t == integer)
			return boolean;
		return type_error;
		break;
	case 31:
		if (child[0]->idattr->t == boolean && child[2]->t == boolean)
			return boolean;
		return type_error;
		break;
	case 32:
		return boolean;
		break;
	default:
		return type_error;
		break;
	}
}
