#include"lexer.h"

int next_token(char* s, char* attr, char* tok, char* lex) {		//s is the source code, lex and attr are the return value of each token, return the length of lexeme.
	int i, j;			//Offset of string							
	int state = 0;		//the state of the DFA
	char ch;
	char str[5000];		//source code
	int len = 0;
	while (final_state[state] == 0) {
		ch = *s;
		state = trans_table[state][trans(ch)];
		str[len] = ch;
		len++;
		s++;
	}
	
	if(state == 49)
		return -1;

	if (final_state[state] == 1) {					//Final state
		str[len - 1] = '\0';
		strcpy(attr, str);
		strcpy(lex, str);
		
		strcpy(tok, token_return[state]);
		i = j = 0;
		
		while (*(attr + i) != '\0') {
			if (*(attr + i) != ' ') {
				*(attr + j) = *(attr + i);
				i++;
				j++;
			}
			else
				i++;
		}
		
		*(attr + j) = '\0';
		
		if (state == 2) {						//Determine whether it is a keyword.
			for (int i = 0; i < 5; i++) {
				if (strcmp(attr, *(identifier + i)) == 0){
					strcpy(tok, identifier[i]);
					str[0] = '\0';
					strcpy(attr, str);
				}
			}
		}

		return (len - 1);
	}
	else if(final_state[state] == 2){
		strcpy(tok, token_return[state]);
		str[0] = '\0';
		strcpy(attr, str);
		return (len - 1);
	}
	else {										//lex error
		if (state == 45 || state == 46)
			str[len] = '\0';
		else
			str[len - 1] = '\0';
		
		strcpy(attr, str);
		strcpy(tok, token_return[state]);
		i = j = 0;		
		while (*(attr + i) != '\0') {
			if (*(attr + i) != ' ') {
				*(attr + j) = *(attr + i);
				i++;
				j++;
			}
			else
				i++;
		}
		*(attr + j) = '\0';
		if (state == 45 || state == 46)
			return len;
		return (len - 1);
	}
}

int trans(char ch) {				//convert a char to a corresponding number

	if (64 < ch && ch < 91)
		ch = ch - 39;

	else if (96 < ch && ch < 123) // a 97->0
		ch = ch - 97;

	else if (47 < ch && ch < 58)// 0 48->52
		ch = ch + 4;
	else if (ch == '{')//  62  
		ch = 62;
	else if (ch == '}')//
		ch = 63;
	else if (ch == '(')//  
		ch = 64;
	else if (ch == ')')//  
		ch = 65;
	else if (ch == ';')//
		ch = 66;
	else if (ch == '+')//
		ch = 67;
	else if (ch == '-')//
		ch = 68;
	else if (ch == '*')//
		ch = 69;
	else if (ch == '/')//
		ch = 70;
	else if (ch == '=')//
		ch = 71;
	else if (ch == '>')//
		ch = 72;
	else if (ch == '<')//
		ch = 73;
	else if (ch == '~')//
		ch = 74;
	else if (ch == '&')//
		ch = 75;
	else if (ch == '|')//
		ch = 76;
	else if (ch == '!')//
		ch = 77;
	else if (ch == ' ' || ch == '\n')
		ch = 78;
	else
		ch = 79;
	return ch;
}