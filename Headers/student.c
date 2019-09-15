#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "student.h"



struct student {
	wchar_t name[LEN_NAME];
	wchar_t subject[LEN_SUBJECT];
	float grade;
};



Student *stCreate(wchar_t *name, wchar_t *subject, float grade) {
	Student *student = (Student*) malloc(sizeof(Student));

	if (student != NULL) {
		wcscpy(student->name, name);
		wcscpy(student->subject, subject);
		student->grade = grade;
	}
	
	return student;
}



void stDestroy(Student *student) {
	free(student);
}



void stGet(Student *student, wchar_t *name, wchar_t *subject, float *grade) {
	wcscpy(name, student->name);
	wcscpy(subject, student->subject);
	*grade = student->grade;
}



wchar_t *stGetName(Student *student) {
	return student->name;
}



wchar_t *stGetSubject(Student *student) {
	return student->subject;
}



float stGetGrade(Student *student) {
	return student->grade;
}



void stSet(Student *student, wchar_t *name, wchar_t *subject, float grade) {
	wcscpy(student->name, name);
	wcscpy(student->subject, subject);
	student->grade = grade;
}



void stSetName(Student *student, wchar_t *name) {
	wcscpy(student->name, name);
}



void stSetSubject(Student *student, wchar_t *subject) {
	wcscpy(student->subject, subject);
}



void stSetGrade(Student *student, float grade) {
	student->grade = grade;
}



void stPrint(Student *student) {
	wprintf(L"%ls tirou %4.1f na disciplina %ls.\n", student->name, student->grade, student->subject);
}