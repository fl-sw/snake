#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include"snake.h"



//���ù��λ��
void set_cursor_pos(SHORT x, SHORT y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ord;
	ord.X = x;
	ord.Y = y;
	SetConsoleCursorPosition(handle, ord);

	//���ÿ���̨��С
	SMALL_RECT rc = { 0, 0, WIDTHBOARD + 1, HEIGHTBOARD };
	SetConsoleWindowInfo(handle, TRUE, &rc);

	//���ù�겻�ɼ�
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = FALSE; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}

//��ӡһ������
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

//��ӡ���α߿�
void print_board()
{
	set_cursor_pos(0, 0);
	for (SHORT x = 0; x <= WIDTHBOARD; x += 2)	//���º�������
	{
		print_a_mark(x, 0, BOARDMARK);
		print_a_mark(x, HEIGHTBOARD, BOARDMARK);
	}

	for (SHORT y = 0; y <= HEIGHTBOARD; y++)	//������ֱ����
	{
		print_a_mark(0, y, BOARDMARK);
		print_a_mark(WIDTHBOARD, y, BOARDMARK);
	}
}

//��ӡ�˵��е���
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
//��ӡ�˵��е���
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

//��ӡ���˵�
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

	//�����ͷ��ʳ���غ�
	if (pSnk->_pHead->_x == area._Fx && pSnk->_pHead->_y == area._Fy)
	{
		area._ate = 1;
	}
	//����
	if (pSnk->_pHead->_x <= area._Aleft || pSnk->_pHead->_x >= area._Aright ||
		pSnk->_pHead->_y <= area._Aup   || pSnk->_pHead->_y >= area._Adown   )
	{
		return 1;
	}

	if (area._ate == 0)
	{
		//��β������
		print_a_mark(pSnk->_pTail->_x, pSnk->_pTail->_y, " ");
		pSnk->_pNeck = pSnk->_pTail;
		pSnk->_pTail = pSnk->_pTail->_pre;
		pSnk->_pTail->_next = pSnk->_pHead;
	}
	else
	{
		//��ʳ��Ե�
		pSnk->_pNeck = area._FNode;
		area._FNode = NULL;
	}
	//���õ���ʳ�����β�ͣ���ɵڶ���ͷ
	pSnk->_pNeck->_dir = pSnk->_pHead->_dir;
	pSnk->_pNeck->_next = pSnk->_pHead->_next;
	pSnk->_pNeck->_pre = pSnk->_pHead;
	pSnk->_pNeck->_x = pSnk->_pHead->_x;
	pSnk->_pNeck->_y = pSnk->_pHead->_y;
	//�õ�һ��ͷָ��ڶ���ͷ���õڶ���ͷ��ɲ���
	pSnk->_pHead->_dir = iDir;
	pSnk->_pHead->_next = pSnk->_pNeck;
	pSnk->_pHead->_pre = pSnk->_pTail;
	//�ж���һ����ͷӦ���������������
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
	//��ӡ��ͷ������(ʳ�ﱻ��ͷ�����ˣ�β�ͱ���ɿո��ˣ��Ͳ��ٴ����ˣ�
	print_a_mark(pSnk->_pHead->_x, pSnk->_pHead->_y, SNAKEHEADMARK);
	print_a_mark(pSnk->_pHead->_next->_x, pSnk->_pHead->_next->_y, SNAKEBODYMARK);
	//���ʳ�ﱻ���ˣ��߱䳤��������һ��ʳ��
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
