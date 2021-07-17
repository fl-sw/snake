#ifndef __SNAKE_H__
#define __SNAKE_H__

#include<stdio.h>
#include<Windows.h>
#include<conio.h>


#define HEIGHTBOARD		40
#define WIDTHBOARD		100
#define BOARDMARK		"[]"
#define SNAKEHEADMARK	"#"
#define SNAKEBODYMARK	"*"
#define FOODMARK		"@"

//--------------------------------------------------------------------------------------------------------------------------------------

#define DEFAULTLENGTH 5
#define DEFAULTSPEED 2
#define DEFAULTDIRECTION 2

enum DIRECTION{ UP = 1, LEFT, DOWN, RIGHT };	//����ö��
typedef enum DIRECTION DIR;



//������
typedef struct snakeNode
{
	struct snakeNode*	_pre; //ָ����һ�����
	struct snakeNode*	_next; //ָ����һ�����
	enum DIRECTION		_dir;	//��ǰ�ڵ�ķ���
	SHORT _x;
	SHORT _y;
}SNode,*pSNode;

//����Ϣ
typedef struct snake
{
	pSNode _pHead;	//ͷ
	pSNode _pTail;	//β
	pSNode _pNeck;	//����
	int _length;	//����
	int _speed;		//�ٶ�
	DIR _dir;		//�˶�����
}Snake,*pSnake;

//��ͼ��Ϣ
typedef struct AreaInfo
{
	SHORT _Aleft;	//��߽�
	SHORT _Aright;	//��߽�
	SHORT _Aup;		//��߽�
	SHORT _Adown;	//��߽�
	SHORT _Fx;		//ʳ������
	SHORT _Fy;		//ʳ������
	SHORT _ate;		//����һ��ʳ��
	pSNode _FNode;	//ʳ��
}Area,pArea;

int run();
void start();
void first_snk_and_fd();
int get_rand_num(char c);
pSnake init_first_snake();

///-------------------------------------------------------------------



void set_cursor_pos(SHORT x, SHORT y);
void print_a_mark(SHORT x, SHORT y, char* c);
void print_a_snake();
void print_board();
void print_words();
//��ӡ���˵�
int print_menu();
void clear_word();



extern Area area;
extern pSnake pSnk;



#endif //__SNAKE_H__
