#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<time.h>
#define  MAP_WIDTH 15 //地图的宽
#define  MAP_HEIGHT 15 //地图的高
#define random(x) (rand()%x)
// 移动方向
typedef enum
{
   UP=0, DOWN, LEFT, RIGHT
}DIRECTION;
// 每一截身体
typedef struct body{
   struct body *pre;    //前面
   struct body *next;   //后面
   int x,y;           // 位置
}SnakeBody;
// 地图
char map[MAP_HEIGHT][MAP_WIDTH];
// 蛇头 蛇尾
SnakeBody *head, *tail;
// 蛇头当前的方向
DIRECTION dir = DOWN;
int bGameOver = 0;// 游戏结束标志
void generateFood();
void resetMap();
// 初始化 蛇出生的位置
void init()
{
   srand((int)time(0));//随机种子

   resetMap();

   head = (SnakeBody *)malloc(sizeof(SnakeBody));
   (*head).pre = NULL;
   (*head).x = 8;
   (*head).y = 8;

   tail = (SnakeBody *)malloc(sizeof(SnakeBody));
   (*tail).pre = head;
   (*tail).x = 8;
   (*tail).y = 9;
   (*tail).next = NULL;

   (*head).next = tail;

   map[head->y][head->x] = 'O';
   map[tail->y][tail->x] = 'o';

   generateFood();
}
void release()
{

}
void resetMap()
{
   int row,col;
   for(row = 0; row < MAP_HEIGHT; ++row)
   {
      for(col = 0; col < MAP_WIDTH; ++col)
      {
         map[row][col] = ' ';
      }
   }
}
// 蛇的移动
void move()
{
   int x = (*head).x, y = (*head).y;
   switch (dir)
   {
      case UP:
         ++y;
         if(y > MAP_HEIGHT)bGameOver = 1;
         break;
               case DOWN:
         --y;
         if(y < 0)bGameOver = 1;
         break;
      case LEFT:
         --x;
         if(x < 0)bGameOver = 1;
         break;
      case RIGHT:
         ++x;
         if(x > MAP_WIDTH)bGameOver = 1;
         break;
   
      default:
         break;
   }

   if(bGameOver)
   {
      printf("hit the wall!\n");
   }else
   {
      char nextC = map[y][x];
      switch(nextC)
      {
         case ' ':{
            map[tail->y][tail->x] = ' ';
            map[head->y][head->x] = 'o';
            map[y][x] = 'O';

            SnakeBody *newHead = tail;
            newHead->x = x;
            newHead->y = y;

            tail = (*tail).pre;
            (*tail).next = NULL;
            (*newHead).pre = NULL;
            (*newHead).next = head;
            (*head).pre = newHead;
            head = newHead;
         }break;
         
         case '#':{
            map[y][x] = 'O';
            map[head->y][head->x] = 'o';

            SnakeBody *newHead = (SnakeBody *)malloc(sizeof(SnakeBody));
            newHead->x = x;
            newHead->y = y;
            newHead->pre = NULL;
            newHead->next = head;
            head->pre = newHead;
            head = newHead;

            generateFood();
         }break;

         case 'O':
         case 'o':{
            bGameOver = 1;
            printf("killed by your self!\n");
         }break;
         default :
            bGameOver = 1;
            printf("error!\n");
            break;
      }
   }
}
// 绘制整个场景
void draw()
{
   system("cls");//绘制之前先清屏

   // 有一个绘制顺序
   int row,col;
   for(row = MAP_HEIGHT - 1; row >= 0; --row)
   {
      for(col = 0; col < MAP_WIDTH; ++col)
      {
         putchar(map[row][col]);
               }
      putchar('\n');
   }
}
// 处理键盘输入
void handleInput()
{
   if(kbhit())// 按键检测
   {
      int ch;
      if(ch=getch() == 0xE0)// 是不是方向键
      {
         switch(ch=getch())
         {
            case 72:  dir = UP; break;
            case 80:  dir = DOWN; break;
            case 75:  dir = LEFT; break;
            case 77:  dir = RIGHT; break;
            default:
               break;
         }
      }
   }
}
// 产生食物
void generateFood()
{
   while(1)
   {
      int x = random(MAP_WIDTH);
      int y = random(MAP_HEIGHT);
      char c = map[y][x];
      if(c == ' ')
      {
         map[y][x] = '#';
         break;
      }
   }
}
int main()
{
   init();

   for(;;)
   {
      draw();

      Sleep(1000);

      handleInput();

      move();

      if(bGameOver)break;
   }

   release();

   system("pause");

   return 0;
}
