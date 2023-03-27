#include"symbol_table.h"

Node *first(){
	Node *current;
	current = (Node *)malloc(sizeof(Node));
	current->line=-1;		
	return current;
}
	
Node *add(char* attr, char* tok, int line, Node* preivous){
	Node *current;	
	current = (Node *)malloc(sizeof(Node));
	current->line=line;
	current->pNext = NULL;
	current->idattr = NULL;
		
    for(int i = 0; i <= strlen(attr); i++){
		current->attr[i] = *(attr + i);
	}
	for(int i = 0; i <= strlen(tok); i++){
		*((current->tok) + i) = *(tok + i);
	}
	
	preivous->pNext=current;
	return current;
}

Node* addid(char* attr, char* tok, int line, Node* preivous, hash_node* node) {
	Node* current;
	current = (Node*)malloc(sizeof(Node));
	current->line = line;
	current->pNext = NULL;

	for (int i = 0; i <= strlen(attr); i++) {
		current->attr[i] = *(attr + i);
	}
	for (int i = 0; i <= strlen(tok); i++) {
		*((current->tok) + i) = *(tok + i);
	}

	current->idattr = node;
	preivous->pNext = current;
	return current;
}

int DispList(Node *head)
{
    Node *p = head;
    while(p != NULL)
    {
		if(p->line == -1){
			p = p->pNext;
			continue;
		}
		if(p->tok[0] == 'l' && p->tok[1] == 'e'){
			printf("Error: \"");
			for(int i = 0; i <= strlen(p->attr); i++){
				printf("%c", p->attr[i]);
			}
			printf("\" is not a lexeme in line %d.\n", p->line);
			return -1;
		}
		printf("-------\n");
		printf("Line: ");
        printf("%d\n",p->line);
		printf("Token: ");
        for(int i = 0; i <= strlen(p->tok); i++){
			printf("%c", p->tok[i]);
		}
		printf("\n");
		printf("Attribute: ");
		if(p->tok[0] == 'I' && p->tok[1] == 'd'){				//If it is a identifier, print the address
			printf("%d", p->idattr);
		}
		else{
			for(int i = 0; i <= strlen(p->attr); i++){
				printf("%c", p->attr[i]);
			}
		}
		printf("\n-------\n\n");
        p = p->pNext;
    }
	return 0;
}

//first(int line,char* lex,char*attr)
//while(){
//		next=add(lex,atr,line,next);
//

int hash(char* s) {
	int key = 0;
	while (*s)
		key = key * 131 + (*s++);
	return (key % 101);
}

void Display_symbol_table(hash_node table[101], int occupy[101]) {
	printf("\nSymbol table:\n");
	hash_node* a;
	for (int i = 0; i < 101; i++){
		if (occupy[i] != -1) {
			a = &table[i];
			while (a != NULL){
				printf("\n----------\n");
				printf("Variable name: ");
				printf("%s\n", a->s);
				printf("Variable type: ");
				print_type(a->t);
				printf("\n");
				a = a->next;
				printf("----------\n");
			}
		}
	}
}

void print_type(enum type t) {
	switch (t)
	{
	case integer:
		printf("interger");
		break;
	case boolean:
		printf("boolean");
		break;
	case type_error:
		printf("type_error");
		break;
	case _void:
		printf("void");
		break;
	case statement:
		printf("statement");
		break;
	case lit:
		printf("lit");
		break;
	case null:
		printf("null");
		break;
	default:
		break;
	}
}
