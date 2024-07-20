#include <stdio.h>

#define MAX_POS_Y 25
#define MAX_POS_X 80

int fPScore = 0;
int sPScore = 0;

void cross_and_toe_display(int flag);
int f_board_key(char key, int fRStart, int fREnd, int min_pos_y, int max_pos_y);
int second_board_key(char key, int sRStart, int sREnd, int min_pos_y, int max_pos_y);

int main(void) {
    while (1) {
        int flag = 1;
        cross_and_toe_display(flag);
    }
}

void cross_and_toe_display(int flag) {
    // Позиции ракеток
    int fRStart = 5;
    int fREnd = 7;
    int firstRacketX = 3;
    int sRStart = 17;
    int sREnd = 19;
    int secondRacketX = 76;

    char vertical = '|';
    char horizontal = '-';
    char space = ' ';
    char point = '*';

    int pointX = 39;
    int pointY = 12;
    int pointSpeedX = 1;
    int pointSpeedY = 1;

    int min_pos_y = 1;
    char pole[MAX_POS_Y][MAX_POS_X];

    while (flag) {
        // Очистка экрана
        printf("\033[0d\033[2J");

        // Инициализация поля
        for (int i = 0; i < MAX_POS_Y; i++) {
            for (int j = 0; j < MAX_POS_X; j++) {
                if (j == 0 || j == MAX_POS_X - 1) {
                    pole[i][j] = vertical;
                } else if (i == 0 || i == MAX_POS_Y - 1) {
                    pole[i][j] = horizontal;
                } else {
                    pole[i][j] = space; // Инициализация пространства
                }
            }
        }

        // Установка положения точки
        pole[pointY][pointX] = point;

        // Отображение ракеток
        for (int i = fRStart; i <= fREnd; i++) {
            pole[i][firstRacketX] = vertical;
        }
        for (int i = sRStart; i <= sREnd; i++) {
            pole[i][secondRacketX] = vertical;
        }

        // Логика движения точки
        if (pointY == 23 || pointY == 1) {
            pointSpeedY *= -1; // Разворот по Y
        }

        if (pointX == 79) {
            fPScore++;
            if (fPScore == 20) {
                printf("Win First player!\n");
                break;
            }
            flag = 0; // Выход
        }

        if (pointX == 0) {
            sPScore++;
            if (sPScore == 20) {
                printf("Win Second player!\n");
                break;
            }
            flag = 0; // Выход
        }

        if ((sRStart <= pointY && pointY <= sREnd && pointX == secondRacketX - 1)) {
            pointSpeedX = -1;
        }
        if (fRStart <= pointY && pointY <= fREnd && pointX == firstRacketX + 1) {
            pointSpeedX = 1;
        }

        // Вывод игрового поля
        for (int i = 0; i < MAX_POS_Y; i++) {
            for (int j = 0; j < MAX_POS_X; j++) {
                printf("%c", pole[i][j]);
            }
            printf("\n");
        }

        // Печать очков
        printf("Points First player: %d\n", fPScore);
        printf("Points Second player: %d\n", sPScore);

        // Чтение ввода
        char key = getchar();

        // Движение первой ракетки
        if (f_board_key(key, fRStart, fREnd, min_pos_y, MAX_POS_Y) == -1) {
            fRStart--;
            fREnd--;
        } else if (f_board_key(key, fRStart, fREnd, min_pos_y, MAX_POS_Y) == 1) {
            fRStart++;
            fREnd++;
        }

        // Движение второй ракетки
        if (second_board_key(key, sRStart, sREnd, min_pos_y, MAX_POS_Y) == -1) {
            sRStart--;
            sREnd--;
        } else if (second_board_key(key, sRStart, sREnd, min_pos_y, MAX_POS_Y) == 1) {
            sRStart++;
            sREnd++;
        }

        // Перемещение точки
        pointX += pointSpeedX;
        pointY += pointSpeedY;
    }
}

int f_board_key(char key, int fRStart, int fREnd, int min_pos_y, int max_pos_y) {
    if (key == 'a' && fRStart > min_pos_y)
        return -1; // Вверх
    if (key == 'z' && fREnd < max_pos_y - 2)
        return 1; // Вниз
    return 0; // Нет движения
}

int second_board_key(char key, int sRStart, int sREnd, int min_pos_y, int max_pos_y) {
    if (key == 'k' && sRStart > min_pos_y)
        return -1; // Вверх
    if (key == 'm' && sREnd < max_pos_y - 2)
        return 1; // Вниз
    return 0; // Нет движения
}