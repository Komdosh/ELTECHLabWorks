#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>

int Menu(); //Прототип функции меню
int enterMatrixSizeByAxis(const char *);    //Прототип функции ввода размеров матрицы
int **matrixItemsEnter(int, int);   //Прототип функции ввода матрицы sourceMatrix
void printMatrix(int, int, int **); //Прототип функции вывода матрицы
int **setupMatrix(int, int, int **, int *); //Прототип функции формирования матрицы resultMatrix
void freeMatrix(int **, int);   //Прототип функции освобождения памяти

int main(void) {
    setlocale(LC_ALL, "RUS");
    int **sourceMatrix = NULL, **resultMatrix = NULL;
    int rows = 0, col = 0;
    int menuItem;
    int matrixEntered = 0, matrixProcessed = 0, resultMatrixColumns = 0;
    const char *help_enter = "Для начала введите матрицу, выбрав 1 пункт в меню!\n";
    do {
        menuItem = Menu();  //Меню
        switch (menuItem) {
            case 1: //Ввод матрицы
                system("cls");
                freeMatrix(sourceMatrix, rows); //Освобождение памяти исходной матрицы, если есть
                freeMatrix(resultMatrix, rows); //Освобождение памяти сформированной матрицы, если есть
                rows = enterMatrixSizeByAxis("строк"); //Ввод кол-ва строк
                col = enterMatrixSizeByAxis("столбцов");   //Ввод кол-ва столбцов
                sourceMatrix = matrixItemsEnter(rows, col);   //Ввод матрицы
                matrixEntered = 1;
                resultMatrixColumns = matrixProcessed = 0;
                break;
            case 2: //Вывод матрицы
                system("cls");
                if (matrixEntered) {
                    printf("Контрольный вывод элементов массива\n");
                    printMatrix(rows, col, sourceMatrix);    //Вывод исходной матрицы
                } else {
                    printf("%s", help_enter);
                }
                system("pause");
                break;
            case 3: //Обработка матрицы
                system("cls");
                matrixProcessed = 1;
                if (matrixEntered) {
                    resultMatrix = setupMatrix(rows, col, sourceMatrix,
                                               &resultMatrixColumns);  //Обработка исходной матрицы
                    if (resultMatrixColumns)
                        printf("Результат сформирован\n");
                    else
                        printf("Результат не может быть сформирован\n");
                } else {
                    printf("%s", help_enter);
                }
                system("pause");
                break;
            case 4: //Вывод сформированной матрицы
                system("cls");
                if (matrixEntered != 1) {
                    printf("%s", help_enter);
                } else if (matrixProcessed != 1) {
                    printf("Результат не сформирован\n");
                } else if (resultMatrixColumns) {
                    printf("Вывод сформированной матрицы:\n");
                    printMatrix(rows, resultMatrixColumns, resultMatrix);   //Вывод сформированной матрицы
                } else {
                    printf("Результат не может быть сформирован\n");
                }
                system("pause");
                break;
            case 5:                         //Выход
                system("cls");
                puts("До новых встреч.");
                puts("Если возникли вопросы или проблемы обращайтесь, пожалуйста, на электронную почту: ");
                puts("komdosh@yandex.ru");
                system("pause");
                break;
            default:
                printf("Что-то пошло не так, введите пункт меню повторно\n");
                system("pause");
        }
    } while (menuItem != 5);
    freeMatrix(sourceMatrix, rows);
    freeMatrix(resultMatrix, rows);
    return 0;
}

//*****************************************************************************************
//Функция Меню
int Menu() {
    int menuItem;
    system("cls");
    puts("Главное меню");
    puts("1 - Ввод матрицы");
    puts("2 - Показать введённую матрицу");
    puts("3 - Обработка исходной матрицы ");
    puts("4 - Показать обработанную матрицу");
    puts("5 - Выход");
    printf("Введите номер пункта - ");
    scanf("%d", &menuItem);
    printf("\n");
    return menuItem;
}

//*****************************************************************************************
//Функция ввода размеров матрицы
int enterMatrixSizeByAxis(const char *str) {
    int num;
    printf("Введите кол-во %s массива (целые положительные числа)\n", str);
    do {
        scanf("%d", &num);
        if (num <= 0) {
            printf("Кол-во %s это целые положительные числа, Введите кол-во повторно!\n", str);
        }
    } while (num <= 0);
    return num;
}

//*****************************************************************************************
//Функция ввода матрицы sourceMatrix
int **matrixItemsEnter(int rows, int cols) {
    int row, col, **matrix;
    matrix = (int **) malloc(rows * sizeof(int *));
    for (row = 0; row < rows; row++) {
        *(matrix + row) = (int *) malloc(cols * sizeof(int));
        printf("Введите элементы %d строки массива через пробел\n", row + 1);
        for (col = 0; col < cols; col++) {
            scanf("%d", &matrix[row][col]);
        }
    }
    return matrix;
}

//*****************************************************************************************
//Функция вывода матрицы
void printMatrix(int rows, int cols, int **mas) {
    for (int row = 0; row < rows; printf("\n"), row++) {
        for (int col = 0; col < cols; col++) {
            printf("%5d", mas[row][col]);
        }
    }
}

//*****************************************************************************************
//Функция формирования матрицы resultMatrix
int **setupMatrix(int rows, int cols, int **mas, int *resultMatrixColumns) {
    int row, col, resRow, resultColumns, **resultMatrix = NULL;
    resultMatrix = (int **) malloc(rows * sizeof(int *));
    for (row = 0; row < rows; row++) {
        *(resultMatrix + row) = NULL;
    }
    for (resultColumns = col = 0; col < cols; col++) {
        for (row = 0, resRow = 1; row < rows - 1 && resRow == 1; row++)
            resRow = (mas[row][col] <= mas[row + 1][col]) ? 1 : 0;
        if (resRow) {
            for (row = 0; row < rows; row++) {
                if (!*(resultMatrix + row))
                    *(resultMatrix + row) = (int *) realloc(*(resultMatrix + row), (resultColumns + 1) * sizeof(int));
                *(*(resultMatrix + row) + resultColumns) = *(*(mas + row) + col);
            }
            resultColumns++;
        }
    }
    *resultMatrixColumns = resultColumns;
    return resultMatrix;
}

//*****************************************************************************************
//Функция освобождения памяти
void freeMatrix(int **matrix, int rows) {
    if (matrix != NULL) {
        for (int row = 0; row < rows; row++)
            free(*(matrix + row));
        free(matrix);
        matrix = NULL;
    }
}
