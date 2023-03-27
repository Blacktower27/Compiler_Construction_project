#include"parser.h"

tree_node* parsing(Node* table){
	stack_node out;
	tree_node* head = NULL;
	//Add '$' to the end of the table of tokens
	Node* a = table;
	while (a->pNext != NULL){
		a = a->pNext;
	}
	char attr[] = { '$','\0' };
	char tok[] = { '$','\0' };
	add(attr, tok, a->line, a);
	//add(attr, tok, b->line, b);
	table = table->pNext;

	printf("\nParsing\n");
	int index;
	int numOfTerminal = 0;
	int state = 0;
	int step = 1;
	int rule;
	tree_node* child[15];
	printf("Step 0:<0,\n");
	Stack s;
	CreateStack(&s, 10000);
	while (state != -1 && state != 999 && table != NULL) {
		index = trans_slr(table->tok);
		//printf("\n!!%s!!%d\n", table->tok, table->line);
		state = parsing_table_action[state][index];
		//printf("\n%d\n", state);

		if (state == -1) {								//Syntax error
			printf("Line %d:\n\t", table->line);
			DisplayError(&s, numOfTerminal);
			if (table->tok[0] == 'I' && table->tok[1] == 'd') {		//If token is id, just printing its name
				for (int i = 0; i < strlen(table->idattr->s); i++){
					printf("%c", table->idattr->s[i]);
				}
			}
			else {
				for (int i = 0; i < strlen(table->tok); i++){
					printf("%c", table->tok[i]);
				}
			}
			printf("\nSyntax error!\n");
			break;
		}

		if (state == 999) {								//accept
			stack_node* current;
			current = (stack_node*)malloc(sizeof(stack_node));
			current->state = state;
			for (int i = 0; i <= strlen(table->tok); i++) {
				current->token[i] = table->tok[i];
			}
			Push(&s, *current);
			printf("Step %d:<0,", step);
			DisplayStack(&s);
			printf("\t\taccept\n");
			table = table->pNext;
			numOfTerminal = 0;
			break;
		}

		if (state <= 71) {							//shift
			numOfTerminal++;
			stack_node* current;
			current = (stack_node*)malloc(sizeof(stack_node));
			current->state = state;
			for (int i = 0; i <= strlen(table->tok); i++){
				current->token[i] = table->tok[i];
			}
			if (table->tok[0] == 'I' && table->tok[1] == 'd') {		//If token is id, store its symbol table address
				for (int i = 0; i <= strlen(table->idattr->s); i++) {
					current->id[i] = table->idattr->s[i];
				}
				current->t_node = create_Terminal_Node(current->token, table->idattr);	//Create a tree node
			}
			else if (table->tok[0] == 'L' && table->tok[1] == 'i') {
				current->id[0] = '\0';
				if (atoi(table->attr) == 0 || atoi(table->attr) == 1) {
					strcpy(current->token, "boolean");
				}
				else {
					strcpy(current->token, "integer");
				}
				current->t_node = create_Terminal_Node(current->token, NULL);		//Create a tree node
			}
			else {												//Other token
				current->id[0] = '\0';
				current->t_node = create_Terminal_Node(current->token, NULL);		//Create a tree node
			}
			Push(&s, *current);
			printf("Step %d:<0,", step);
			DisplayStack(&s);
			printf("\t\tshift\n");
			table = table->pNext;
			//another = another->pNext;
		}

		else {										//reduce
			rule = state - 71;			//Get the index of rule
			char terminal[2];
			terminal[0] = rules[rule][0];		//Get terminal
			terminal[1] = '\0';
			for (int i = nofr[rule] - 1; i >= 0; i--) {		//Pop out elements in the stack to reduce
				Pop(&s, &out);
				child[i] = out.t_node;
			}
			if (IsEmpty(&s)) 
				state = parsing_table_goto[0][trans_slr(terminal)];
			else {								//Get the state after the reduce
				Top(&s, &out);
				state = parsing_table_goto[out.state][trans_slr(terminal)];
			}
			stack_node* current;
			current = (stack_node*)malloc(sizeof(stack_node));
			current->state = state;
			for (int i = 0; i < 2; i++) {
				current->token[i] = terminal[i];
			}
			current->t_node = create_Nonterminal_Node(nofr[rule], child, terminal, type_Checking(rule, child));		//Create a tree node
			if (current->state == 1)
				head = current->t_node;
			Push(&s, *current);
			printf("Step %d:<0,", step);
			DisplayStack(&s);
			printf("\t\treduce ");
			for (int i = 0; i <= strlen(rules[rule]); i++){
				printf("%c", rules[rule][i]);
			}
			printf("\n");
			numOfTerminal = 0;
		}
		step++;
	}
	return head;
}

int trans_slr(char* ch) {
	if (strcmp(ch, "&&") == 0)
		return 0;
	else if (strcmp(ch, "(") == 0) // 
		return 1;
	else if (strcmp(ch, ")") == 0)// 0 
		return 2;
	else if (strcmp(ch, "*") == 0)//  62  
		return 3;
	else if (strcmp(ch, "+") == 0)//
		return 4;
	else if (strcmp(ch, "-") == 0)//  
		return 5;
	else if (strcmp(ch, "/") == 0)//  
		return 6;
	else if (strcmp(ch, ";") == 0)//
		return 7;
	else if (strcmp(ch, "<~") == 0)//
		return 8;
	else if (strcmp(ch, "=") == 0)//
		return 9;
	else if (strcmp(ch, ">") == 0)//
		return 10;
	else if (strcmp(ch, "bool") == 0)//
		return 11;
	else if (strcmp(ch, "Idenfier") == 0)//
		return 12;
	else if (strcmp(ch, "else") == 0)
		return 13;
	else if (strcmp(ch, "if") == 0)
		return 14;
	else if (strcmp(ch, "!") == 0)
		return 15;
	else if (strcmp(ch, "int") == 0)
		return 16;
	else if (strcmp(ch, "Literal") == 0)
		return 17;
	else if (strcmp(ch, "while") == 0)
		return 18;
	else if (strcmp(ch, "{") == 0)
		return 19;
	else if (strcmp(ch, "||") == 0)
		return 20;
	else if (strcmp(ch, "}") == 0)
		return 21;
	else if (strcmp(ch, "$") == 0)
		return 22;
	else if (strcmp(ch, "A") == 0)
		return 0;
	else if (strcmp(ch, "B") == 0)
		return 1;
	else if (strcmp(ch, "C") == 0)
		return 2;
	else if (strcmp(ch, "D") == 0)
		return 3;
	else if (strcmp(ch, "E") == 0)
		return 4;
	else if (strcmp(ch, "F") == 0)
		return 5;
	else if (strcmp(ch, "L") == 0)
		return 6;
	else if (strcmp(ch, "P") == 0)
		return 7;
	else if (strcmp(ch, "Q") == 0)
		return 8;
	else if (strcmp(ch, "R") == 0)
		return 9;
	else if (strcmp(ch, "S") == 0)
		return 10;
	else if (strcmp(ch, "T") == 0)
		return 11;
	else if (strcmp(ch, "U") == 0)
		return 12;
	else if (strcmp(ch, "V") == 0)
		return 13;
}

//function of the stack
//This part is from Data struct lab3
bool CreateStack(Stack* stack, int size) {
	if (size <= 0)													//if size less than 0, create fall
		return false;
	stack->values = (stack_node*)malloc(sizeof(stack_node) * size);
	stack->top = -1;
	stack->maxTop = size - 1;
	return true;
}

bool IsEmpty(Stack* stack) {
	return stack->top == -1;										//if top == -1, it means that the stack is empty and then return true
}

bool IsFull(Stack* stack) {
	return stack->top == stack->maxTop;								//if top == maxTop, it means that the stack is full and then return true
}

bool Top(Stack* stack, stack_node* x) {
	if (IsEmpty(stack))
		return false;                                               //if the stack is empty, then the stack has not a top, so return false
	else {
		*x = stack->values[stack->top];
		return true;
	}
}

bool Push(Stack* stack, stack_node x) {
	if (IsFull(stack))
		return false;												//if the stack is full, the stack can not push more elements
	else {
		stack->top++;
		stack->values[stack->top] = x;
		return true;
	}
}

bool Pop(Stack* stack, stack_node* x) {
	if (IsEmpty(stack))												//if the stack is empty, the stack can not pop any elements
		return false;
	else {
		*x = stack->values[stack->top];
		stack->top--;
		return true;
	}
}

void DisplayStack(Stack* stack) {
	for (int i = 0; i <= stack->top; i++){
		if (stack->values[i].token[0] == '$') {
			printf("$");
			break;
		}
		printf("\033[4m");
		for (int j = 0; j <= strlen((stack->values[i]).token); j++) {
			printf("%c", (stack->values[i]).token[j]);
		}
		printf(", %d", (stack->values[i]).state);
		printf("\033[m");
		printf(", ");
	}
}

void DisplayError(Stack* stack, int num) {
	for (int i = num; i > 0; i--){
		if ((stack->values[(stack->top) - i + 1]).token[0] == 'I' && (stack->values[(stack->top) - i + 1]).token[1] == 'd') {
			for (int j = 0; j <= strlen((stack->values[(stack->top) - i + 1]).id); j++) {
				printf("%c", (stack->values[(stack->top) - i + 1]).id[j]);
			}
		}
		else{
			for (int j = 0; j <= strlen((stack->values[(stack->top) - i + 1]).token); j++) {
				printf("%c", (stack->values[(stack->top) - i + 1]).token[j]);
			}
		}
		printf(" ");
	}
}

void DestroyStack(Stack* stack) {
	free(stack);
}
