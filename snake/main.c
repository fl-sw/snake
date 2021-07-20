#include<Windows.h>
#include"snake.h"
//#include"graph.h"

Area area;
pSnake pSnk;
void game()
{
	int select = print_menu();
	switch (select)
	{
	case 1:
	{
		clear_word();
		start();
	}
		break;
	case 2:
		printf("usage");
		break;
	case 3:
		return;
	default:
		break;
	}
}
int main()
{
	area._Aleft		= strlen(BOARDMARK);
	area._Aright	= WIDTHBOARD - strlen(BOARDMARK);
	area._Aup		= 1;
	area._Adown		= HEIGHTBOARD - 1;
	area._Fx		= area._Aleft;
	area._Fy		= area._Aup;
	area._ate		= 0;
	area._FNode		= NULL;
	game();
	//system("pause");
	getchar();

	return 0;
}
