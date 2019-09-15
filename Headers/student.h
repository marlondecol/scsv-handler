#ifndef _STUDENT_H
#define _STUDENT_H



#define LEN_NAME 15
#define LEN_SUBJECT 30



typedef struct student Student;



Student *stCreate(wchar_t *name, wchar_t *subject, float grade);

void stDestroy(Student *student);

void stGet(Student *student, wchar_t *name, wchar_t *subject, float *grade);

wchar_t *stGetName(Student *student);

wchar_t *stGetSubject(Student *student);

float stGetGrade(Student *student);

void stSet(Student *student, wchar_t *name, wchar_t *subject, float grade);

void stSetName(Student *student, wchar_t *name);

void stSetSubject(Student *student, wchar_t *subject);

void stSetGrade(Student *student, float grade);

void stPrint(Student *student);



#endif