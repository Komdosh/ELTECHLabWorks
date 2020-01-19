#include <stdio.h>

#include <locale.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "RUS");
    const int n = 30;
    int firstArray[n][n], secondArray[n][n], row, column;
    int rowCount = 0, columnCount = 0;
    int isTransportable, menuItem, arrayIsEntered = 0, check_2 = 0, resultColumns = 0;
    do {
        printf("\n");
        puts("Главное меню");
        puts("1 - Ввод матрицы");
        puts("2 - Показать введённую матрицу");
        puts("3 - Обработка исходной матрицы ");
        puts("4 - Показать обработанную матрицу");
        puts("5 - Выход");
        printf("Введите номер пункта - ");
        scanf("%d", &menuItem);
        printf("\n");
        switch (menuItem) {
            case 1: //Ввод матрицы
                printf("Введите кол-во строк массива (целые положительные числа от 1 до %d)\n", n);
                do {
                    scanf("%d", &rowCount);
                    if (rowCount < 1 || rowCount > n)
                        printf("Кол-во строк, целые положительные числа, от 1 до %d! Введите кол-во повторно!\n", n);
                } while (rowCount < 1 || rowCount > n);
                printf("Введите кол-во столбцов массива (целые положительные числа от 1 до %d)\n", n);
                do {
                    scanf("%d", &columnCount);
                    if (columnCount < 1 || columnCount > n)
                        printf("Кол-во столбцов, целые положительные числа, от 1 до %d! Введите кол-во повторно!\n", n);
                } while (columnCount < 1 || columnCount > n);
                for (row = 0; row < rowCount; row++) {
                    printf("Введите элементы %d строки массива через пробел\n", row + 1);
                    for (column = 0; column < columnCount; column++) {
                        scanf("%d", &firstArray[row][column]);
                    }
                }
                arrayIsEntered = 1;
                break;
            case 2: //Вывод матрицы
                if (arrayIsEntered == 1) {
                    printf("Контрольный вывод элементов массива\n");
                    for (row = 0; row < rowCount; printf("\n"), row++)
                        for (column = 0; column < columnCount; printf("%5d", firstArray[row][column]), column++);
                } else
                    printf("Для начала введите матрицу, выбрав 1 пункт в меню!\n");
                break;
            case 3: //Обработка матрицы
                check_2 = 1;
                if (arrayIsEntered == 1)
                    for (resultColumns = column = 0; column < columnCount; column++) {
                        for (row = 0, isTransportable = 1; row < rowCount - 1 && isTransportable == 1; row++)
                            isTransportable = (firstArray[row][column] <= firstArray[row + 1][column]) ? 1 : 0;
                        if (isTransportable == 1) {
                            for (row = 0; row < rowCount; secondArray[row][resultColumns] = firstArray[row][column], row++);
                            resultColumns++;
                        }
                    }
                if (arrayIsEntered != 1)
                    printf("Для начала введите матрицу, выбрав 1 пункт в меню!\n");
                else if (resultColumns != 0)
                    printf("Результат сформирован\n");
                else
                    printf("Результат не может быть сформирован\n");
                break;
            case 4: //Вывод обработанной матрицы
                if (resultColumns != 0) {
                    printf("Вывод обработанного массива:\n");
                    for (row = 0; row < rowCount; printf("\n"), row++)
                        for (column = 0; column < resultColumns; printf("%5d", secondArray[row][column]), column++);
                } else if (arrayIsEntered != 1)
                    printf("Для начала введите матрицу, выбрав 1 пункт в меню!\n");
                else if (check_2 != 1)
                    printf("Результат не сформирован\n");
                else
                    printf("Результат не может быть сформирован\n");
                break;
            case 5: //Выход
                puts("До новых встреч.");
                puts("Если возникли вопросы или проблемы обращайтесь на электронную почту: ");
                puts("komdosh@yandex.ru");
                system("pause");
                break;
            default:
                printf("Что-то пошло не так, введите пункт меню повторно\n");
        }
    } while (menuItem != 5);
    return 0;
}

