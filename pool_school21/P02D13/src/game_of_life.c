#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <windows.h> // Для Windows
//#include <unistd.h> // Для Unix-подобных систем

#ifdef _WIN32
#include <windows.h> // Для Windows
#else
#include <unistd.h> // Для Unix-подобных систем
#endif

#define WIDTH 80
#define HEIGHT 25
#define CELL 'o'
#define DEAD_CELL ' '

char** calloc_matrix(int width, int height);
void init_world(char** field);
void update_world(char** field);
void draw_world(char** field);
int get_count_of_neighbors(char** field, int x0, int y0);
void add_figure(char** field, char figure, int x0, int y0);
char** get_glider();
char** get_house();
char** get_five();
void clear_field(char** field);
void clear_matrix(char** field, int width, int height);
void set_console_utf8();
void wait(int seconds);

char get_user_choice() {
    char choice;
    printf("Выберите фигуру:\n");
    printf("1 - Глайдер\n");
    printf("2 - Дом\n");
    printf("3 - Пятёрка\n");
    printf("4 - Выход\n");
    printf("Ваш выбор: ");
    scanf(" %c", &choice);
    return choice;
}

void init_world(char** field) {
    clear_field(field);
    
    char choice = get_user_choice();
    while (choice != '4') {
        int x = WIDTH / 2, y = HEIGHT / 2; // Начальная позиция фигуры
        switch (choice) {
            case '1':
                add_figure(field, 'g', x, y);
                break;
            case '2':
                add_figure(field, 'h', x, y);
                break;
            case '3':
                add_figure(field, 'f', x, y);
                break;
            default:
                printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
        }
        draw_world(field);
        choice = get_user_choice();
    }
}

void clear_matrix(char** field, int width, int height) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            field[row][col] = DEAD_CELL;
        }
    }
}

void clear_field(char** field) {
    clear_matrix(field, WIDTH, HEIGHT);
}

int correctX(int x) {
    if (x < 0) return x + WIDTH;
    if (x >= WIDTH) return x - WIDTH;
    return x;
}

int correctY(int y) {
    if (y < 0) return y + HEIGHT;
    if (y >= HEIGHT) return y - HEIGHT;
    return y;
}

int get_count_of_neighbors(char** field, int x0, int y0) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue; // Пропускаем саму клетку
            if (field[correctY(y0 + dy)][correctX(x0 + dx)] == CELL) {
                count++;
            }
        }
    }
    return count;
}

void dead_or_life(char** field, int x, int y, int neighbors) {
    if (neighbors < 2 || neighbors > 3) {
        field[y][x] = DEAD_CELL;
    }
}

void update_world(char** field) {
    char** field2 = calloc_matrix(WIDTH, HEIGHT);
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            field2[row][col] = field[row][col]; // Копируем текущее состояние поля
        }
    }

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            int neighbors = get_count_of_neighbors(field2, col, row);
            if (field2[row][col] == CELL) {
                dead_or_life(field, col, row, neighbors); // Изменяем исходное поле
            } else if (neighbors == 3) { // Исправлено условие для рождений
                field[row][col] = CELL;
            }
        }
    }

    free(field2);
}

void draw_world(char** field) {
    printf("\e[1;1H\e[2J"); // Очистка консоли
    for (int row = 0; row < HEIGHT; row++) {
        printf("%.*s\n", WIDTH, field[row]); // Печатаем только первые WIDTH символов
    }
}

char** calloc_matrix(int width, int height) {
    char** matrix = (char**) calloc(height, sizeof(char*));
    for (int i = 0; i < height; i++) {
        matrix[i] = (char*) calloc(width + 1, sizeof(char)); // +1 для завершающего нуля
    }
    return matrix;
}

void add_figure(char** field, char figure, int x0, int y0) {
    char** shape;
    int size = 5; // Размер фигур 5x5
    switch (figure) {
        case 'g':
            shape = get_glider();
            break;
        case 'h':
            shape = get_house();
            break;
        case 'f':
            shape = get_five();
            break;
        default:
            return;
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (shape[i][j] == CELL) {
                field[correctY(y0 + i)][correctX(x0 + j)] = CELL;
            }
        }
    }
    free(shape);
}

char** get_glider() {
    char** glider = calloc_matrix(5, 5);
    clear_matrix(glider, 5, 5);
    glider[0][1] = CELL;
    glider[1][2] = CELL;
    glider[2][0] = CELL;
    glider[2][1] = CELL;
    glider[2][2] = CELL;
    return glider;
}

char** get_house() {
    char** house = calloc_matrix(5, 5);
    clear_matrix(house, 5, 5);
    house[0][1] = CELL;
    house[1][0] = CELL;
    house[1][1] = CELL;
    house[1][2] = CELL;
    return house;
}

char** get_five() {
    char** five = calloc_matrix(5, 5);
    clear_matrix(five, 5, 5);
    five[0][1] = CELL;
    five[0][2] = CELL;
    five[1][0] = CELL;
    five[1][1] = CELL;
    five[2][1] = CELL;
    return five;
}

void wait(int seconds) {
    #ifdef _WIN32
    Sleep(seconds * 1000); // Умножаем на 1000 для перехода в миллисекунды
    #else
    sleep(seconds); // Задержка в секундах
    #endif
}

void set_console_utf8() {
#ifdef _WIN32
    // Получаем текущую кодовую страницу консоли
    DWORD dwOldMode = GetConsoleOutputCP();
    // Устанавливаем кодовую страницу на UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Проверяем, успешно ли была выполнена операция
    if (dwOldMode != CP_UTF8) {
        printf("Ошибка установки кодовой страницы консоли на UTF-8.\n");
    }
#endif
}

int main() {
    set_console_utf8(); // Установка консоли на UTF-8
    setlocale(LC_ALL, ""); // Установка локали для поддержки кириллицы
    char** field = calloc_matrix(WIDTH, HEIGHT);
    init_world(field);
    draw_world(field);

    while (1) {
        update_world(field);
        draw_world(field);
        wait(1); // Пауза в 1 секунду между обновлениями
    }

    for (int i = 0; i < HEIGHT; i++) {
        free(field[i]);
    }
    free(field);
    return 0;
}
