#define _CRT_SECURE_NO_WARNINGS
#include "snake.h"

// 隐藏光标，使游戏界面更美观
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 初始化墙壁
void initWall(void) {
    // 上边界和下边界
    for (int j = 0; j <= WIDE; j++) {
        printf("-");
    }
    printf("\n");

    // 中间区域和左右边界
    for (int i = 0; i < HIGH; i++) {
        printf("|");  // 左边界
        for (int j = 1; j < WIDE; j++) {
            printf(" ");  // 游戏区域
        }
        printf("|\n");  // 右边界
    }

    // 下边界
    for (int j = 0; j <= WIDE; j++) {
        printf("-");
    }
    printf("\n");
}

// 初始化蛇
void initSnake(void) {
    snake.size = 2;
    snake.body[0].X = 10;  // 蛇头位置
    snake.body[0].Y = 10;
    snake.body[1].X = 9;   // 第一节身体
    snake.body[1].Y = 10;
}

// 初始化食物
void initFood(void) {
    do {
        food.X = rand() % (WIDE - 2) + 1;  // 确保在游戏区域内
        food.Y = rand() % HIGH;
    } while (checkFoodOnSnake());
}

// 检查食物是否生成在蛇身上
int checkFoodOnSnake(void) {
    for (int i = 0; i < snake.size; i++) {
        if (snake.body[i].X == food.X && snake.body[i].Y == food.Y) {
            return 1;  // 食物在蛇身上
        }
    }
    return 0;  // 食物位置有效
}

// 初始化游戏界面
void initUI(void) {
    COORD coord = { 0 };

    // 绘制蛇
    for (int i = 0; i < snake.size; i++) {
        coord.X = snake.body[i].X;
        coord.Y = snake.body[i].Y + 1;  // +1是因为第一行是上边界
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        if (i == 0) {
            putchar('@');  // 蛇头
        }
        else {
            putchar('*');  // 蛇身
        }
    }

    // 清除上一帧的蛇尾
    coord.X = lastX;
    coord.Y = lastY + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar(' ');

    // 绘制食物
    coord.X = food.X;
    coord.Y = food.Y + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar('#');

    // 显示分数
    coord.X = 0;
    coord.Y = HIGH + 2;  // 显示在边界下方
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("当前得分: %d  ", score);

    // 将光标移动到不干扰游戏的位置
    coord.X = 0;
    coord.Y = HIGH + 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 游戏主循环
void playGame(void) {
    char key = 'd';  // 初始方向向右
    HideCursor();    // 隐藏光标

    while (1) {
        // 记录当前尾部位置，用于后续清除
        lastX = snake.body[snake.size - 1].X;
        lastY = snake.body[snake.size - 1].Y;

        // 处理按键输入
        if (_kbhit()) {
            key = _getch();
            // 根据按键改变方向，防止180度反向移动
            switch (key) {
            case 'w':
            case 'W':
                if (ky != 1) {  // 不在向下移动时才能向上
                    kx = 0;
                    ky = -1;
                }
                break;
            case 's':
            case 'S':
                if (ky != -1) {  // 不在向上移动时才能向下
                    kx = 0;
                    ky = 1;
                }
                break;
            case 'a':
            case 'A':
                if (kx != 1) {  // 不在向右移动时才能向左
                    kx = -1;
                    ky = 0;
                }
                break;
            case 'd':
            case 'D':
                if (kx != -1) {  // 不在向左移动时才能向右
                    kx = 1;
                    ky = 0;
                }
                break;
            case 'q':
            case 'Q':  // 退出游戏
                system("cls");
                printf("游戏已退出！最终得分: %d\n", score);
                return;
            }
        }

        // 移动蛇身，从尾部开始移动
        for (int i = snake.size - 1; i > 0; i--) {
            snake.body[i].X = snake.body[i - 1].X;
            snake.body[i].Y = snake.body[i - 1].Y;
        }

        // 移动蛇头
        snake.body[0].X += kx;
        snake.body[0].Y += ky;

        // 检测是否撞墙
        if (snake.body[0].X <= 0 || snake.body[0].X >= WIDE ||
            snake.body[0].Y < 0 || snake.body[0].Y >= HIGH) {
            system("cls");
            printf("撞到墙壁了！游戏结束！最终得分: %d\n", score);
            return;
        }

        // 检测是否撞到自己
        for (int i = 1; i < snake.size; i++) {
            if (snake.body[0].X == snake.body[i].X &&
                snake.body[0].Y == snake.body[i].Y) {
                system("cls");
                printf("撞到自己了！游戏结束！最终得分: %d\n", score);
                return;
            }
        }

        // 检测是否吃到食物
        if (snake.body[0].X == food.X && snake.body[0].Y == food.Y) {
            initFood();
            snake.size++;
            score += 10;
            // 新的尾部位置不需要清除，所以恢复lastX和lastY
            lastX = snake.body[snake.size - 1].X;
            lastY = snake.body[snake.size - 1].Y;
        }

        // 刷新界面
        system("cls");
        initWall();
        initUI();

        // 控制游戏速度，分数越高速度越快
        Sleep(150 - score / 10);
        if (Sleep < 50) Sleep(50);  // 最低速度限制
    }
}

int main(void) {
    srand((unsigned int)time(NULL));  // 初始化随机数种子

    initSnake();    // 初始化蛇
    initFood();     // 初始化食物

    system("cls");  // 清屏
    initWall();     // 绘制墙壁
    initUI();       // 绘制蛇和食物

    printf("欢迎来到贪吃蛇游戏！\n");
    printf("使用WASD键控制方向，Q键退出游戏\n");
    printf("按任意键开始游戏...\n");
    _getch();       // 等待用户按键开始

    playGame();     // 开始游戏主循环

    system("pause");
    return EXIT_SUCCESS;
}