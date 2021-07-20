#ifndef __SNAKE_H__
#define __SNAKE_H__

#include<stdio.h>
#include<Windows.h>
#include<conio.h>
//#include"graph.h"


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

enum DIRECTION{ UP = 1, LEFT, DOWN, RIGHT };	//方向枚举
typedef enum DIRECTION DIR;



//蛇身结点
typedef struct snakeNode
{
	struct snakeNode*	_pre; //指向下一个结点
	struct snakeNode*	_next; //指向下一个结点
	enum DIRECTION		_dir;	//当前节点的方向
	SHORT _x;
	SHORT _y;
}SNode,*pSNode;

//蛇信息
typedef struct snake
{
	pSNode _pHead;	//头
	pSNode _pTail;	//尾
	pSNode _pNeck;	//脖子
	int _length;	//长度
	int _speed;		//速度
	DIR _dir;		//运动方向
}Snake,*pSnake;

//地图信息
typedef struct AreaInfo
{
	SHORT _Aleft;	//左边界
	SHORT _Aright;	//左边界
	SHORT _Aup;		//左边界
	SHORT _Adown;	//左边界
	SHORT _Fx;		//食物坐标
	SHORT _Fy;		//食物坐标
	SHORT _ate;		//吃下一个食物
	pSNode _FNode;	//食物
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
//打印主菜单
int print_menu();
void clear_word();



extern Area area;
extern pSnake pSnk;



#endif //__SNAKE_H__
