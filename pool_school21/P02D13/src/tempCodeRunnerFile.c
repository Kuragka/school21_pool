    char** field2;
    field2 = calloc_matrix(WIDTH + 1, HEIGHT);  // Выделяем пямять для предыдущего состояния
    copy_matrix(field, field2);

    int neighbors;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            neighbors = get_count_of_neighbors(field2, col, row);  // Считываем соседей в старой конфигурации
            if (field2[row][col] == CELL)  // считываем живых в старом состоянии
                dead_or_life(field, col, row, neighbors);  // убиваем клетки в новом состоянии
            if (neighbors == 3)
                field[row][col] = CELL;  // оставляем в живых в новом состоянии согласно старому состоянию
        }
    }

    free(field2);  // очищаем память
}

void draw_world(char** field) {
    printf("\e[1;1H\e[2J");
    for (int row = 0; row < HEIGHT; row++) {
        printf("%s\n", field[row]);
    }
}

int input() {
    char button;
    int rtn = 0;
    if (scanf("%c", &button) == EOF) rtn = 2;  // ловим нажатие Ctrl + D
    if (button == ' ') rtn = 1;  // ход выполняется только при вводе пробела
    return rtn;
}

char** calloc_matrix(int width, int height) {
    char** matrix = (char**) calloc(height + width * height, sizeof(char*));
    char* arrays = (char*) (matrix + height);
    for (int row = 0; row < height; row++) {
        matrix[row] = &arrays[row * width];
    }
    return matrix;
}

#define FIGURES_SIZE 5

void add_figure(char** field, char** figure, int x0, int y0) {
    int x, y;
    for (int i = 0; i < FIGURES_SIZE; i++) {
        for (int j = 0; j < FIGURES_SIZE; j++) {
            x = correctX(x0 + j);
            y = correctY(y0 + i);
            field[y][x] = figure[i][j];
        }
    }
}

// !!! Выделяется память !!! Не забыть очистить после исползования функций !!!
char** get_glider() {
    char** glider = calloc_matrix(FIGURES_SIZE, FIGURES_SIZE);
    clear_matrix(glider, FIGURES_SIZE, FIGURES_SIZE);
    glider[0][1] = CELL;
    glider[1][2] = CELL;
    glider[2][0] = CELL;
    glider[2][1] = CELL;
    glider[2][2] = CELL;
    return glider;
}

char** get_house() {
    char** house = calloc_matrix(FIGURES_SIZE, FIGURES_SIZE);
    clear_matrix(house, FIGURES_SIZE, FIGURES_SIZE);

    house[0][1] = CELL;
    house[1][0] = CELL;
    house[1][1] = CELL;
    house[1][2] = CELL;

    return house;
}

char** get_five() {
    char** five = calloc_matrix(FIGURES_SIZE, FIGURES_SIZE);
    clear_matrix(five, FIGURES_SIZE, FIGURES_SIZE);

    five[0][1] = CELL;
    five[0][2] = CELL;
    five[1][0] = CELL;
    five[1][1] = CELL;
    five[2][1] = CELL;

    return five;
}

char** get_frog() {
    char** frog = calloc_matrix(FIGURES_SIZE, FIGURES_SIZE);
    clear_matrix(frog, FIGURES_SIZE, FIGURES_SIZE);

    frog[0][1] = CELL;
    frog[0][2] = CELL;
    frog[0][3] = CELL;
    frog[1][0] = CELL;
    frog[1][1] = CELL;
    frog[1][2] = CELL;

    return frog;
}

char** get_spaceshipL() {
    char** spaceshipL = calloc_matrix(FIGURES_SIZE, FIGURES_SIZE);
    clear_matrix(spaceshipL, FIGURES_SIZE, FIGURES_SIZE);

    spaceshipL[0][3] = CELL;
    spaceshipL[1][4] = CELL;
    spaceshipL[2][0] = CELL;
    spaceshipL[2][4] = CELL;
    spaceshipL[3][1] = CELL;
    spaceshipL[3][2] = CELL;
    spaceshipL[3][3] = CELL;
    spaceshipL[3][4] = CELL;

    return spaceshipL;
}
