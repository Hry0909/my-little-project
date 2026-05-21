#ifndef __SNAKE_H__
#define __SNAKE_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<Windows.h> 


#define WIDE 60
#define HIGH 20

struct BODY {
    int X;
    int Y;
};

struct SNAKE {
    struct BODY body[WIDE * 20];
    int size;
}snake;

struct FOOD {
    int X;
    int Y;
}food;

int score = 0;
int kx = 1;  // 初始方向向右
int ky = 0;
int lastX;
int lastY;

void initSnake(void);
void initFood(void);
void initUI(void);
void playGame(void);
void initWall(void);
int checkFoodOnSnake(void);  // 检查食物是否在蛇身上

#endif
