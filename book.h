#ifndef __BOOK_H__
#define __BOOK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <errno.h>

#define FILE_DB  "book.db"

#pragma pack(1)

typedef struct _header {
	int iNum;
	char cDummy[30];
} Header;

typedef struct _book {
	char book[30];
	char author[15];
	char publisher[10];
	char price[10];
	char year[5];
	char cSlash;
	struct _book * stNext;
} Book;

#pragma pack(4)


// Model

void Book_Insert(Book **, Book *);
void Book_Delete(Book **, Book *, Header *);

Book * Book_Search(Book * stHead, char * cBook);
Book * Book_Delete_Search(Book * stHead, char * cBook);

void Book_Free(Book *);

void Book_Save(Book *, Header *);
void Book_Load(Book **, Header *);


// View

void Menu(void);
unsigned int Input(void);

void Book_Init(Book *);	// 삽입을 위해 책 정보를 받아온다
void Book_Info(const char *, int , char *, int);

void Book_Print(Book *, int);
void Book_Search_Print(Book *);


//Controller


void Book_Insert_Control(Book **, Header *);	// Insert
void Book_Make_Node(Book **);

void Book_Search_Control(Book * stHead);
void Book_Delete_Control(Book ** stHead, Header * stHeader);


#endif /* __BOOK_H__ */
