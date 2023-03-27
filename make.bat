gcc lexer.c -c
gcc symbol_table.c -c
gcc parser.c -c
gcc pares_tree.c -c
gcc sgcc.c lexer.o symbol_table.o parser.o pares_tree.o -g -o sgcc.exe
sgcc