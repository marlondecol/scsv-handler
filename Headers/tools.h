#ifndef _TOOLS_H
#define _TOOLS_H



#include <stdio.h>
#include <wchar.h>



void clear();

int openFile(FILE **file, char *filename, char *mode);

wchar_t *replace(wchar_t *str, wchar_t tirar, wchar_t colocar);

void waitKey();



#endif