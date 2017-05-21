#include "book.h"

void Book_Make_Node(Book ** stTemp)
{
	*stTemp = malloc(sizeof(Book));     //�����Ҵ��� �޴´�
	if (0 == *stTemp)                  //�����Ҵ� ���н� NULL��ȯ.
	{
		printf("Make_Node:: Error. malloc\n");  //���� �޼��� ����� ����
		return;
	}
	Book_Init(*stTemp);               //�����Ҵ� �������� ������ �Է�
}

void Book_Insert_Control(Book ** stHead, Header * stHeader)
{
	Book * stTemp;

	Book_Make_Node(&stTemp);
	Book_Insert(stHead, stTemp);
	stHeader->iNum++;
}
void Book_Search_Control(Book * stHead)
{
	Book * stTemp;
	char cBook[30];

	if (0 == stHead)
	{
		printf("Find:: No Linked List\n\n");
		return;
	}
	
	Book_Info(" BOOK: ", 7, cBook, sizeof(cBook));
	stTemp = Book_Search(stHead, cBook);

	if (0 == stTemp)
	{
		return;
	}

	Book_Search_Print(stTemp);
}
void Book_Delete_Control(Book ** stHead, Header * stHeader)
{
	Book * stSearch;
	char cBook[30];
	
	if (0 == *stHead)
	{
		printf("Find:: No Linked List\n\n");
		return;
	}

	Book_Info(" BOOK: ", 7, cBook, sizeof(cBook));
	stSearch = Book_Delete_Search(*stHead, cBook);
	Book_Delete(&stHead, stSearch, &stHeader);
}

