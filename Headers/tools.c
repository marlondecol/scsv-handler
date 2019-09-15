#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>



#include "tools.h"



void clear() {
	wprintf(L"\e[H\e[2J");
}



int openFile(FILE **file, char *filename, char *mode) {
	*file = fopen(filename, mode);

	return !(file == NULL || *file == NULL);
}



wchar_t *replace(wchar_t *str, wchar_t tirar, wchar_t colocar) {
	for (int i = 0; i < (int) wcslen(str); i++)
		if (str[i] == tirar)
			str[i] = colocar;
	
	return str;
}



void waitKey() {
	wprintf(L"\n  Pressione ENTER para continuar...");
	getchar();
}