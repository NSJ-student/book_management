#include "book.h"

void Menu(void)
{
	printf("\n###########################################\n");
	printf(" 1. insert\n");
	printf(" 2. list\n");
	printf(" 3. search\n");
	printf(" 4. delete\n");
	printf(" 5. quit\n");
	printf("-------------------------------------------\n");

	return;
}

unsigned int Input(void)
{
	unsigned int cmd;

	while (1)
	{
		printf(" 번호를 입력하시오(1~5): ");
		scanf("%d", &cmd);
		while (getchar() != '\n');     // 버퍼를 비운다

		if ((cmd) < 1)
		{
			continue;
		}
		if ((cmd) > 5)
		{
			continue;
		}

		printf("-------------------------------------------\n");
		return cmd;
	}
}
void Book_Info(const char * ccPrint, int s_size, char * Buffer, int b_size)
{
	int iRet;
	
	while (1)
	{
		write(1, ccPrint, s_size);
		iRet = read(0, Buffer, b_size);

		if ((iRet == b_size) && (Buffer[iRet - 1] != '\n'))
		{
			while (getchar() != '\n');
			write(2, " [ Error: Too long string ]\n", 28);
			continue;
		}
		break;
	}
	
	Buffer[iRet - 1] = 0;
}

void Book_Init(Book * stTemp)
{
	if (stTemp == 0)
	{
		return;
	}

	Book_Info(" BOOK: ", 7, stTemp->book, sizeof(stTemp->book));
	Book_Info(" AUTHOR: ", 9, stTemp->author, sizeof(stTemp->author));
	Book_Info(" PUBLISHER: ", 12, stTemp->publisher, sizeof(stTemp->publisher));
	Book_Info(" PRICE: ", 8, stTemp->price, sizeof(stTemp->price));
	Book_Info(" YEAR: ", 7, stTemp->year, sizeof(stTemp->year));

	stTemp->cSlash = '/';
	stTemp->stNext = 0;
	write(1, "\n", 1);

	return;
}
void Book_Search_Print(Book * stTemp)
{
	if (0 == stTemp)
	{
		printf("Search_Print:: Can't find target\n\n");
		return;
	}

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" %-30s %-15s %-15s %-10s %-4s\n", "BOOK", "AUTHOR", "PUBLISHER", "PRICE", "YEAR");
	printf("-------------------------------------------------------------------------------\n");

	printf(" %-30s", stTemp->book);
	printf(" %-15s", stTemp->author);
	printf(" %-15s", stTemp->publisher);
	printf(" %-10s", stTemp->price);
	printf(" %-4s\n", stTemp->year);
	printf("-------------------------------------------------------------------------------\n\n");
}
void Book_Print(Book * Temp, int iNum)
{
	int iCnt = 0;

	if (0 == iNum)
	{
		printf("\n  [ ----- No Book List ----- ]\n\n");
		return;
	}

	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf(" %-30s %-15s %-15s %-10s %-4s\n", "BOOK", "AUTHOR", "PUBLISHER", "PRICE", "YEAR");
	printf("-------------------------------------------------------------------------------\n");
	while (0 != Temp)
	{
		if (iCnt == 19)
		{
			iCnt = 0;
			printf("\n %53s", "[ ...Press enter to continue... ]\n");
			getchar();
			printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			printf(" %-30s %-15s %-15s %-10s %-4s\n", "BOOK", "AUTHOR", "PUBLISHER", "PRICE", "YEAR");
			printf("-------------------------------------------------------------------------------\n");
		}

		iCnt++;

		printf(" %-30s", Temp->book);
		printf(" %-15s", Temp->author);
		printf(" %-15s", Temp->publisher);
		printf(" %-10s", Temp->price);
		printf(" %-4s\n", Temp->year);
		Temp = Temp->stNext;

	}
	printf("\n=======  Total: %3d  ==========================================================\n", iNum);
	printf(" %53s", "[ ...Press enter to continue... ]");
	getchar();

	return;
}


