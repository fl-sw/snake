#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include"snake.h"



//设置光标位置
void set_cursor_pos(SHORT x, SHORT y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(handle, ord);

	//设置控制台大小
	SMALL_RECT rc = { 0, 0, WIDTHBOARD + 1, HEIGHTBOARD };
	SetConsoleWindowInfo(handle, TRUE, &rc);

	//设置光标不可见
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = FALSE; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

//打印一个符号
void print_a_mark(SHORT x, SHORT y, char* c)
{
	set_cursor_pos(x, y);
	printf(c);
	if (!strcmp(c,FOODMARK))
	{
		area._Fx = x;
		area._Fy = y;
		area._FNode = (pSNode)malloc(sizeof(SNode));
		if (NULL != area._FNode)
		{
			memset(area._FNode, sizeof(SNode), 0);
		}
	}
}

//打印矩形边框
void print_board()
{
	set_cursor_pos(0, 0);
	for (SHORT x = 0; x <= WIDTHBOARD; x += 2)	//上下横排两行
	{
		print_a_mark(x, 0, BOARDMARK);
		print_a_mark(x, HEIGHTBOARD, BOARDMARK);
	}

	for (SHORT y = 0; y <= HEIGHTBOARD; y++)	//左右竖直两行
	{
		print_a_mark(0, y, BOARDMARK);
		print_a_mark(WIDTHBOARD, y, BOARDMARK);
	}
}

//打印菜单中的字
void print_word()
{
	char* menu1 = "********************************";
	char* menu2 = "****      Retro Snaker      ****";
	char* menu3 = "****                        ****";
	char* menu4 = "****        1.start         ****";
	char* menu5 = "****        2.help          ****";
	char* menu6 = "****        3.quit          ****";
	char* arr[9] = { menu1, menu2, menu3, menu4, menu5, menu6, menu3, menu1, menu1 };

	SHORT x = WIDTHBOARD / 3;
	SHORT y = HEIGHTBOARD / 3;
	for (int i = 0; i < 9; i++)
	{
		set_cursor_pos(x, y + i);
		printf("%s", arr[i]);
	}
}
//打印菜单中的字
void clear_word()
{
	char* menu1 = "                                ";
	SHORT x = WIDTHBOARD / 3;
	SHORT y = HEIGHTBOARD / 3;
	for (int i = 0; i < 9; i++)
	{
		set_cursor_pos(x, y + i);
		printf("%s", menu1);
	}
}

void print_a_snake()
{
	pSNode pTemp = pSnk->_pHead;
	print_a_mark(pTemp->_x, pTemp->_y, SNAKEHEADMARK);
	pTemp = pTemp->_next;
	while (pTemp!=NULL)
	{
		print_a_mark(pTemp->_x, pTemp->_y, SNAKEBODYMARK);
		pTemp = pTemp->_next;
		if (pTemp == pSnk->_pTail)
			pTemp = NULL;
	}
}

//打印主菜单
int print_menu()
{
	system("cls");
	print_board();
	print_word();
	char c = '0';
	do{
		c = _getch();
	} while (c < '1' || '3' < c);
	return (int)c - '0';
}

//--------------------------------------------------------------------------------------------------------------------------------------

int get_rand_num(char c)
{
	int a;
	srand((unsigned)time(NULL));
	a = rand();
	return c == 'x' ? (a%(WIDTHBOARD-4))+2 : (a%(HEIGHTBOARD-2))+1;
}
void first_snk_and_fd()
{
	int x = get_rand_num('x');
	int y = get_rand_num('y');
	print_a_mark(x, y, FOODMARK);
	print_a_snake(init_first_snake());
}
void print_a_fd()
{
	int again = 0;
	int x = 0;
	int y = 0;
	pSNode pTemp = pSnk->_pHead;
	do{
		x = get_rand_num('x');
		y = get_rand_num('y');
		if (x == area._Fx && y == area._Fy)
			again = 1;
		while (!pTemp)
		{
			if (x == pTemp->_x && y == pTemp->_y)
				again = 1;
			pTemp = pTemp->_next;
		}
	} while (again);
	print_a_mark(x, y, FOODMARK);
}

pSnake init_first_snake()
{
	pSnk = 0;
	pSnk = (pSnake)malloc(sizeof(Snake));
	if (pSnk)
	{
		memset(pSnk, 0, sizeof(Snake));
	}

	SNode(*arr)[DEFAULTLENGTH] = (SNode(*)[DEFAULTLENGTH])malloc(sizeof(SNode)*DEFAULTLENGTH);
	if (NULL != arr)
	{
		memset(arr, 0, sizeof(SNode)*DEFAULTLENGTH);
	}
	pSNode pTemp = NULL;
	for (int i=0; i < DEFAULTLENGTH; i++)
	{
		pTemp = arr[i];
		pTemp->_dir = LEFT;
		if (i < DEFAULTLENGTH -1)
			pTemp->_next = arr[i + 1];
		else
			pTemp->_next = arr[0];
		if (i > 0)
			pTemp->_pre = arr[i - 1];
		else
			pTemp->_pre = arr[DEFAULTLENGTH - 1];
		pTemp->_x = WIDTHBOARD / 2 + i;
		pTemp->_y = HEIGHTBOARD / 3 * 2;
		if (NULL != pTemp->_next)
			pTemp = pTemp->_next;
	}
	pSnk->_dir = LEFT;
	pSnk->_length = DEFAULTLENGTH;
	pSnk->_pHead = arr[0];
	pSnk->_pNeck = NULL;
	pSnk->_pTail = pTemp;
	pSnk->_speed = DEFAULTSPEED;
	return pSnk;
}

void start()
{
	int in = 0;
	int out = 0;
	first_snk_and_fd();
	int iDir = pSnk->_pHead->_dir;
	while (1)
	{
		if (_kbhit())
		{
			in = _getch();
			if (in == 27 || in == ' ')
			{
				getchar();
			}
			if (in == 'w' || in == 'a' || in == 's' || in == 'd')
			{
				iDir = in;
			}
		}
		out = run(iDir);
		if (out == 1)
		{
			getchar();
		}
		Sleep(1000/pSnk->_speed);
	}
}

int run(iDir)
{

	//如果蛇头和食物重合
	if (pSnk->_pHead->_x == area._Fx && pSnk->_pHead->_y == area._Fy)
	{
		area._ate = 1;
	}
	//碰壁
	if (pSnk->_pHead->_x <= area._Aleft || pSnk->_pHead->_x >= area._Aright ||
		pSnk->_pHead->_y <= area._Aup   || pSnk->_pHead->_y >= area._Adown   )
	{
		return 1;
	}

	if (area._ate == 0)
	{
		//把尾巴拿走
		print_a_mark(pSnk->_pTail->_x, pSnk->_pTail->_y, " ");
		pSnk->_pNeck = pSnk->_pTail;
		pSnk->_pTail = pSnk->_pTail->_pre;
		pSnk->_pTail->_next = pSnk->_pHead;
	}
	else
	{
		//把食物吃掉
		pSnk->_pNeck = area._FNode;
		area._FNode = NULL;
	}
	//把拿到的食物或者尾巴，变成第二个头
	pSnk->_pNeck->_dir = pSnk->_pHead->_dir;
	pSnk->_pNeck->_next = pSnk->_pHead->_next;
	pSnk->_pNeck->_pre = pSnk->_pHead;
	pSnk->_pNeck->_x = pSnk->_pHead->_x;
	pSnk->_pNeck->_y = pSnk->_pHead->_y;
	//用第一个头指向第二个头，让第二个头变成脖子
	pSnk->_pHead->_dir = iDir;
	pSnk->_pHead->_next = pSnk->_pNeck;
	pSnk->_pHead->_pre = pSnk->_pTail;
	//判断下一个蛇头应该在哪里，更新坐标
	switch (iDir)
	{
	case UP:
		pSnk->_pHead->_x;
		pSnk->_pHead->_y--;
		break;
	case LEFT:
		pSnk->_pHead->_x--;
		pSnk->_pHead->_y;
		break;
	case DOWN:
		pSnk->_pHead->_x;
		pSnk->_pHead->_y++;
		break;
	case RIGHT:
		pSnk->_pHead->_x++;
		pSnk->_pHead->_y;
		break;
	default:
		printf("error");
		break;
	}
	//打印新头，脖子(食物被新头覆盖了，尾巴被打成空格了，就不再处理了）
	print_a_mark(pSnk->_pHead->_x, pSnk->_pHead->_y, SNAKEHEADMARK);
	print_a_mark(pSnk->_pHead->_next->_x, pSnk->_pHead->_next->_y, SNAKEBODYMARK);
	//如果食物被吃了，蛇变长，再生成一个食物
	if (area._ate == 1)
	{
		pSnk->_dir = pSnk->_pHead->_dir;
		pSnk->_length++;
		pSnk->_speed++;
		print_a_fd();
		area._ate = 0;
	}
	return 0;
}
