#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include"lexer.h"
#include"symbol_table.h"
#include"parser.h"
#include"pares_tree.h"

//char source[50000]; //The string read in
char* line_source[5000];

int main(int argc, char* argv[]){	
	char ch;
	char* source = (char*)malloc(sizeof(char) * 50000);
	memset(source, 0, 50000);
    
	FILE *fp;            /*The file pointer*/
	int i = 0;   

	//'\n'newline,[]comment ,'/t'''space 
	if ((fp = fopen("sample.txt", "r")) == NULL)
	{
		printf("Can not find the file.\n");
		exit(0);
	}
	else {
		while (!feof(fp))
		{
			fscanf(fp, "%c", &ch);

		if (ch == '\t') {//skip/t
			source[i] = ' ';			
			i++;
				while (1)
				{
					if (EOF == fscanf(fp, "%c", &ch) || ch != '\t')break;
				}
			}
		
		if (ch == ' ') {//skip space''
			source[i] = ch;			
			i++;
				while (1)
				{
					if (EOF == fscanf(fp, "%c", &ch) || ch != 32)
						break;
				}
			}
		if (ch =='['){//skip commnt
			while (1)
				{
					if (EOF == fscanf(fp, "%c", &ch) || ch == ']')break;
				}
			fscanf(fp, "%c", &ch);//delete []
		}
	
		//sample input
		source[i] = ch;			
		i++;
		
	}
		source[i - 1] = '\0';	
    }
	//printf("%s", source);
	char attr[50];
	char tok[50];
	char lex[50];
	int len;
	char* s;
	int line = 1;
	s = source;

	Node* table = first();
	Node* n = table;

	int occupy[101];
	memset(occupy, 0, 101);
	int value;
	hash_node* hash_table;
	hash_table = (hash_node*)malloc(sizeof(hash_node) * 101);

	for (int i = 0; i < 101; i++){
		occupy[i] = -1;
		hash_table[i].next = NULL;
	}
	while(*s != 0){
		
		while(*s == '\n'){
			line++;
			s++;
		}
		if(*s == '\0')
			break;
		len = next_token(s, attr, tok, lex);
		if(len == -1){
			s = s + 1;
			continue;
		}
		
		if (tok[0] == 'I' && tok[1] == 'd') {
			value = hash(lex);
			if (occupy[value] == -1) {
				strcpy(hash_table[value].s, lex);
				occupy[value] = 1;
				s = s + len;						//Change the position of the pointer
				n = addid(attr, tok, line, n, &hash_table[value]);		//Add the token into the symbol table
			}
			else {
				hash_node* a;
				hash_node* b;
				a = &hash_table[value];
				while (a != NULL) {
					if (strcmp(a->s, lex) == 0) {
						s = s + len;						//Change the position of the pointer
						n = addid(attr, tok, line, n, a);		//Add the token into the symbol table
						break;
					}
					b = a;
					a = a->next;
					if (a == NULL) {
						a = (hash_node*)malloc(sizeof(hash_node));
						a->next = NULL;
						strcpy(a->s, lex);
						s = s + len;						//Change the position of the pointer
						n = addid(attr, tok, line, n, a);		//Add the token into the symbol table
					}
				}
			}
			continue;
		}
		s = s + len;						//Change the position of the pointer
		n = add(attr, tok, line, n);		//Add the token into the symbol table
	}
	printf("table\n");
	if (DispList(table) == -1)
		return 0;
	free(source);
	tree_node* tree;
	Display_symbol_table(hash_table, occupy);
	tree = parsing(table);
	if(tree != NULL){
		Display_symbol_table(hash_table, occupy);
		printf("\nParesing tree:\n");
		print_Tree("", tree, false);
	}
	printf("\nFinish\n");
    return 0;
}
