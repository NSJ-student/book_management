#include "book.h"


void Book_Insert(Book ** stHead, Book * stTemp)
{
	Book * stSeeker;
	Book * stHelp;

	if (0 == stHead)                         //전달된 인자 검사
	{
		printf("Insert:: Error. No Linked List(stHead)\n"); //에러 메세지 출력후 종료
		return;
	}

	if (0 == stTemp)                         //전달된 인자 검사
	{
		printf("Insert:: Error. No Linked List(stTemp)\n"); //에러 메세지 출력후 종료
		return;
	}

	stTemp->stNext = 0;

	if (0 == (*stHead))
	{
		(*stHead) = stTemp;
		return;
	}
	if (0 > strcmp(stTemp->book, (*stHead)->book))
	{
		(stTemp->stNext) = *stHead;
		(*stHead) = stTemp;
		return;
	}

	stHelp = stSeeker = *stHead;     //각 변수 초기화

	while (0 != stSeeker)               //삽입 위치 검색'만'한다/ Seeker가 마지막에 도달할때까지 반복
	{
		if (0 > strcmp(stTemp->book, stSeeker->book))  //삽입위치 정의 Code
		{
			break;
		}
		//삽입위치 찾지 못했을 경우
		stHelp = stSeeker;               //Help는 Seeker가 변하기전의 주소를 가지고 있어야한다
		stSeeker = (stSeeker->stNext);   //들어갈 자리를 찾는 code
	}
	
	(stTemp->stNext) = (stSeeker);
	(stHelp->stNext) = stTemp;

	return;
}
void Book_Delete(Book ** stHead, Book * stTemp, Header * stHeader)
{
	Book * stDelete;

	if (0 == stTemp)
	{
		printf(" Delete:: Can't find target\n\n");
		return;
	}
	if (0 == stHead)
	{
		printf(" Delete:: No Linked List\n\n");
		return;
	}

	if ((Book *)-1 == stTemp)
	{
		stDelete = *stHead;
		*stHead = stDelete->stNext;
		free(stDelete);
	}
	else
	{
		stDelete = stTemp->stNext;

		stTemp->stNext = stDelete->stNext;
		free(stDelete);
	}

	stHeader->iNum--;
	printf(" Delete Completely\n\n");
}
Book * Book_Search(Book * stHead, char * cBook)
{
	if (0 == stHead)                         //전달된 인자 검사
	{
		printf("Search:: No Linked List\n"); //에러 메세지 출력후 종료
		return 0;
	}

	if (0 == strcmp(cBook, stHead->book))
	{
		return stHead;
	}
	
	while (0 != stHead)
	{
		if (0 == strcmp(cBook, stHead->book))
		{
			return stHead;
		}

		stHead = (stHead->stNext);
	}
	
	printf("\n Search:: [%s] doesn't exist\n\n", cBook);

	return 0;
}

Book * Book_Delete_Search(Book * stHead, char * cBook)
{
	Book * stSeeker;

	if (0 == stHead)						//전달된 인자 검사
	{
		printf("Delete:: No Linked List\n");	//에러 메세지 출력후 종료
		return 0;
	}
	stSeeker = stHead;

	while (0 != stSeeker)
	{
		if (0 == strcmp(cBook, stSeeker->book))
		{
			break;
		}
		stHead = stSeeker;
		stSeeker = (stSeeker->stNext);
	}

	if ( 0 == stSeeker)
	{
		printf("\n Delete:: [%s] doesn't exist\n\n", cBook);

		return 0;
	}
	if (stSeeker == stHead)
	{
		return (Book *)-1;
	}

	return stHead;
}

void Book_Free(Book * head)
{
	Book * Temp = 0;
	while (0 != head)
	{
		Temp = head->stNext;
		free(head);
		head = Temp;
	}

	return;
}
void Book_Save(Book * stHead, Header * stHeader)
{
	int iFd;

	if (0 == stHead)
	{
		printf("Save:: Error. No Linked List(stHead)\n");
		return;
	}
	iFd = open(FILE_DB, O_CREAT | O_RDWR | O_TRUNC | O_BINARY, 0644);

	if (iFd < 0)
	{
		printf("Save:: Error. File Create\n");
		return;
	}

	write(iFd, stHeader, sizeof(Header));
	while (0 != stHead)
	{
		write(iFd, stHead, sizeof(Book)-4);
		stHead = stHead->stNext;
	}

	close(iFd);

	printf("Save completely!\n");
}

void Book_Load(Book ** stHead, Header * stHeader)
{
	int iFd;
	int iRet;
	int i;
	Book * stTemp;

	if (0 == stHead)
	{
		printf("Load:: Error. stHead\n");
		return;
	}
	iFd = open(FILE_DB, O_RDONLY | O_BINARY);

	if (iFd < 0)
	{
		printf("Load:: book.db doesn't exist.\n");

		iFd = open(FILE_DB, O_CREAT | O_RDWR | O_TRUNC | O_BINARY, 0644);
		if (iFd < 0)
		{
			printf("Load:: Error. book.db create failure.\n");
			return;
		}

		stHeader->iNum = 0;
		for (i = 0; i < 30; i++)
			stHeader->cDummy[i] = '*';

		close(iFd);

		printf("Load:: Create new book.db\n");

		return;
	}

	iRet = read(iFd, stHeader, sizeof(Header));
	if (sizeof(Header) != iRet)
	{
		printf("Load:: Error. No header in book.db\n");

		stHeader->iNum = 0;
		for (i = 0; i < 30; i++)
			stHeader->cDummy[i] = '*';

		return;
	}

	while (1)
	{
		stTemp = malloc(sizeof(Book));     //동적할당을 받는다

		if (0 == stTemp)                  //동적할당 실패시 NULL반환.
		{
			printf("Load:: Error. No Memory Available(malloc)\n");  //에러 메세지 출력후 종료
			break;
		}

		iRet = read(iFd, stTemp, sizeof(Book)-4);

		if (sizeof(Book)-4 != iRet)
		{
			free(stTemp);
			break;
		}

		Book_Insert(stHead, stTemp);
	}


	close(iFd);

	printf("Load completely!\n");
}


