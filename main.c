#include "book.h"

int main(void)
{
	Book * Head = 0;
	Header stHeader;
	unsigned int iCmd;

	Book_Load(&Head, &stHeader);

	while (1)
	{
		Menu();
		iCmd = Input();

		switch (iCmd)
		{
			case 1: 	Book_Insert_Control(&Head, &stHeader);
					break;
					
			case 2: 	Book_Print(Head, stHeader.iNum);
					break;
					
			case 3: 	Book_Search_Control(Head);
					break;
					
			case 4: 	Book_Delete_Control(&Head, &stHeader);
					break;
					
			case 5: 	Book_Save(Head, &stHeader);
					Book_Free(Head);
					break;
					
			default: 	break;
		}
		
		if (iCmd == 5)
		{
			break;
		}
	}

	return 0;
}
