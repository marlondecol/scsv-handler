#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>



#include "Headers/list.h"
#include "Headers/student.h"
#include "Headers/tools.h"



#define SIZE_FILENAME 200
#define SIZE_LINEBUFFER 200



void fillList(List **students, FILE *file) {
	*students = lsCreate();

	wchar_t *store, line[SIZE_LINEBUFFER];

	while (fgetws(line, SIZE_LINEBUFFER, file)) {
		if ((int) line[0] == 65279)
			memmove(line, line + 1, sizeof(line));

		wchar_t *name = wcstok(line, L";", &store);
		wchar_t *subject = wcstok(NULL, L";", &store);
		wchar_t *grade = wcstok(NULL, L";", &store);

		replace(grade, L',', L'.');

		lsAddSorted(*students, stCreate(name, subject, wcstof(grade, NULL)));
	}
}



int main() {
	setlocale(LC_ALL, "C.UTF-8");
	
	FILE *file = NULL;
	char filename[SIZE_FILENAME];

	List *students = NULL;

	int opt;

	while (1) {
		clear();

		wprintf(L"\n  Escolha uma opção:\n\n");

		wprintf(L"  [1] Selecionar arquivo\n");
		wprintf(L"  [2] Ler e exibir o arquivo\n");
		wprintf(L"  [3] Calcular média das disciplinas\n");
		wprintf(L"  [4] Calcular média dos alunos\n");
		wprintf(L"  [5] Inserir um registro\n");
		wprintf(L"  [0] Sair\n\n");

		wprintf(L"  Sua opção: ");
		scanf("%d%*c", &opt);

		if (opt == 0)
			break;
		else if (opt == 1) {
			clear();

			wprintf(L"\n  Pode ser usado tanto caminho relativo quanto absoluto.\n");
			wprintf(L"\n  Informe o nome do arquivo: ");
			
			fgets(filename, SIZE_FILENAME, stdin);
			int len = (int) strlen(filename);
			if (len && filename[len - 1] == '\n') filename[len - 1] = '\0';

			if (!openFile(&file, filename, "r")) {
				wprintf(L"\n  Erro ao abrir o arquivo para leitura!\n");
				waitKey();

				continue;
			}

			fillList(&students, file);
			fclose(file);

			wprintf(L"\n  Arquivo selecionado!\n");

			waitKey();
		} else if (opt == 2) {
			clear();

			if (lsIsEmpty(students)) {
				wprintf(L"\n  Nenhum arquivo foi selecionado!\n");
				wprintf(L"\n  Escolha a opção [1] do menu para selecionar um arquivo.\n");

				waitKey();

				continue;
			}

			char lenMaxId[12];
			sprintf(lenMaxId, "%d", lsLength(students));

			int lenToUse = 2; if (strlen(lenMaxId) > 2) lenToUse = strlen(lenMaxId);

			wprintf(L"\n  %*s | %-*s | %-*s | %4s", lenToUse, "ID", LEN_NAME, "NOME", LEN_SUBJECT, "DISCIPLINA", "NOTA");
			
			wprintf(L"\n -");
			for (int i = 0; i < lenToUse; i++) wprintf(L"-");
			wprintf(L"-+-");
			for (int i = 0; i < LEN_NAME; i++) wprintf(L"-");
			wprintf(L"-+-");
			for (int i = 0; i < LEN_SUBJECT; i++) wprintf(L"-");
			wprintf(L"-+------\n");

			Node *node = *students;

			while (node != NULL) {
				wprintf(
					L"  %*d | %-15ls | %-30ls | %4.1f\n",
					lenToUse,
					lsGetNodeId(node),
					stGetName(lsGetStudent(students, node)),
					stGetSubject(lsGetStudent(students, node)),
					stGetGrade(lsGetStudent(students, node))
				);

				node = lsGetNextNode(node);
			}

			free(node);

			wprintf(L"\n  Total de registros: %d\n", lsLength(students));

			waitKey();
		} else if (opt == 3) {
			clear();

			if (lsIsEmpty(students)) {
				wprintf(L"\n  Nenhum arquivo foi selecionado!\n");
				wprintf(L"\n  Escolha a opção [1] do menu para selecionar um arquivo.\n");

				waitKey();

				continue;
			}

			Node *node = *students;

			int length = lsLength(students);
			int pos = 0;

			wchar_t names[length][LEN_NAME];

			while (node != NULL) {
				wchar_t *name = stGetName(lsGetStudent(students, node));

				int mustAdd = 1;
				
				for (int i = 0; i < length; i++)
					if (!wcscmp(name, names[i])) {
						mustAdd = 0;
						break;
					}
				
				if (mustAdd) {
					wcscpy(names[pos], name);
					pos++;

					node = *students;

					continue;
				}

				node = lsGetNextNode(node);
			}

			wchar_t aux[LEN_NAME];

			for (int i = 1; i < pos; i++)
				for (int j = 0; j < pos - 1; j++)
					if (wcscmp(names[j], names[j + 1]) > 0) {
						wcscpy(aux, names[j]);
						wcscpy(names[j], names[j + 1]);
						wcscpy(names[j + 1], aux);
					}

			wprintf(L"\n  %-*s | %5s\n", LEN_NAME, "NOME", "MÉDIA");
			wprintf(L" -"); for (int i = 0; i < LEN_NAME; i++) wprintf(L"-"); wprintf(L"-+-------\n");

			float totalAvg = 0.0;

			for (int i = 0; i < pos; i++) {
				node = *students;

				float sum = 0.0;
				int grades = 0;

				while (node != NULL) {
					if (!wcscmp(stGetName(lsGetStudent(students, node)), names[i])) {
						sum += stGetGrade(lsGetStudent(students, node));
						grades++;
					}
					
					node = lsGetNextNode(node);
				}

				float avg = roundf((sum / grades) * 100) / 100;
				totalAvg += avg;

				wprintf(L"  %-*ls | %5.2f\n", LEN_NAME, names[i], avg);
			}

			totalAvg /= pos;

			wprintf(L" -"); for (int i = 0; i < LEN_NAME; i++) wprintf(L"-"); wprintf(L"-+-------\n");
			wprintf(L"  %-*ls | %5.2f\n", LEN_NAME, L"Total geral", totalAvg);

			free(node);

			wprintf(L"\n  Total de estudantes: %d\n", pos);

			waitKey();
		} else if (opt == 4) {
			clear();

			if (lsIsEmpty(students)) {
				wprintf(L"\n  Nenhum arquivo foi selecionado!\n");
				wprintf(L"\n  Escolha a opção [1] do menu para selecionar um arquivo.\n");

				waitKey();

				continue;
			}

			Node *node = *students;

			int length = lsLength(students);
			int pos = 0;

			wchar_t subjects[length][LEN_SUBJECT];

			while (node != NULL) {
				wchar_t *subject = stGetSubject(lsGetStudent(students, node));

				int mustAdd = 1;
				
				for (int i = 0; i < length; i++)
					if (!wcscmp(subject, subjects[i])) {
						mustAdd = 0;
						break;
					}
				
				if (mustAdd) {
					wcscpy(subjects[pos], subject);
					pos++;

					node = *students;

					continue;
				}

				node = lsGetNextNode(node);
			}

			wchar_t aux[LEN_SUBJECT];

			for (int i = 1; i < pos; i++)
				for (int j = 0; j < pos - 1; j++)
					if (wcscmp(subjects[j], subjects[j + 1]) > 0) {
						wcscpy(aux, subjects[j]);
						wcscpy(subjects[j], subjects[j + 1]);
						wcscpy(subjects[j + 1], aux);
					}

			wprintf(L"\n  %-*s | %5s\n", LEN_SUBJECT, "DISCIPLINA", "MÉDIA");
			wprintf(L" -"); for (int i = 0; i < LEN_SUBJECT; i++) wprintf(L"-"); wprintf(L"-+-------\n");

			float totalAvg = 0.0;

			for (int i = 0; i < pos; i++) {
				node = *students;

				float sum = 0.0;
				int grades = 0;

				while (node != NULL) {
					if (!wcscmp(stGetSubject(lsGetStudent(students, node)), subjects[i])) {
						sum += stGetGrade(lsGetStudent(students, node));
						grades++;
					}
					
					node = lsGetNextNode(node);
				}

				// Arredonda a média para o mais próximo.
				float avg = roundf((sum / grades) * 100) / 100;
				totalAvg += avg;

				wprintf(L"  %-*ls | %5.2f\n", LEN_SUBJECT, subjects[i], avg);
			}

			totalAvg /= pos;

			wprintf(L" -"); for (int i = 0; i < LEN_SUBJECT; i++) wprintf(L"-"); wprintf(L"-+-------\n");
			wprintf(L"  %-*ls | %5.2f\n", LEN_SUBJECT, L"Total geral", totalAvg);

			free(node);

			wprintf(L"\n  Total de disciplinas: %d\n", pos);

			waitKey();
		} else if (opt == 5) {
			clear();

			if (lsIsEmpty(students)) {
				wprintf(L"\n  Nenhum arquivo foi selecionado!\n");
				wprintf(L"\n  Escolha a opção [1] do menu para selecionar um arquivo.\n");

				waitKey();

				continue;
			}
			
			int len;
			
			wprintf(L"\n  Informe o nome do aluno: ");
			char name[LEN_NAME];
			fgets(name, LEN_NAME, stdin);
			len = (int) strlen(name);
			if (len && name[len - 1] == '\n') name[len - 1] = '\0';
			
			wprintf(L"  Informe a disciplina:    ");
			char subject[LEN_SUBJECT];
			fgets(subject, LEN_SUBJECT, stdin);
			len = (int) strlen(subject);
			if (len && subject[len - 1] == '\n') subject[len - 1] = '\0';
			
			wprintf(L"  Informe sua nota:        ");
			float grade;
			scanf("%f%*c", &grade);
			
			if (!openFile(&file, filename, "a")) {
				wprintf(L"\n  Erro ao abrir o arquivo para escrita!\n");
				waitKey();

				continue;
			}

			char line[SIZE_LINEBUFFER];
			snprintf(line, SIZE_LINEBUFFER, "\n%s;%s;%.1f", name, subject, grade);

			if (!fputs(line, file)) {
				wprintf(L"\n  Não foi possível escrever a linha no arquivo!\n");
				waitKey();

				continue;
			}

			fclose(file);
			
			if (!openFile(&file, filename, "r")) {
				wprintf(L"\n  Erro ao abrir o arquivo para leitura!\n");
				waitKey();

				continue;
			}
			
			fillList(&students, file);
			fclose(file);
			
			wprintf(L"\n  Registro inserido com sucesso!\n");

			waitKey();
		} else {
			wprintf(L"\n  Opção inválida!\n");

			waitKey();
		}
	}

	clear();

	wprintf(L"\n  Obrigado e até a próxima!\n");
	waitKey();

	clear();

    return 0;
}