#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

typedef union sFLOAT {
    float asFloat;
    long int asInteger;
} UnitedFLOAT;

int menu();                                               //Прототип функции Главного меню
int enterNum(int first,
             int last);                                   //Прототип функции ввода целочисленных значений в диапазоне
void output(UnitedFLOAT source,
            UnitedFLOAT processed, int count, int key);   //Прототип функции вывода мантиссы в двоичном виде
long int leftShift(long int num, int k);                  //Прототип функции циклического сдвига
void messages(int messageId);                             //Прототип функции вывода сообщения

int main() {
    system("mode con cols=80 lines=20");
    UnitedFLOAT source, processed;
    int menuItem, count;
    bool init = false, processing = false;
    system("chcp 1251");
    do {
        switch (menuItem = menu()) {
            case 0: //Справка
                puts("Программа делает циклический сдвиг влево в мантиссе числа");
                puts("с 19 по 11 биты, отсчёт битов начинается с нуля, область изменённых битов отделена пробелами");
                break;
            case 1: //Ввод числа
                system("cls");
                puts("Введите число с плавающей точкой, точность записи: 6 разрядов после точки");
                puts("Число вводится в формате X.Y - где X,Y произвольные числа");
                puts("Важно! Если ввести запятую вместо точки, числа после запятой теряются");
                printf("Введите число - ");
                scanf("%f", &source.asFloat);
                fflush(stdin);
                printf("Введите число сдвигов от 0 до 32767 - ");
                count = enterNum(-1, INT_MAX);
                count = count % 8;
                init = true;
                processing = false;
                messages(1);
                break;
            case 2: //Вывод исходных данных
                if (init) {
                    system("cls");
                    output(source, processed, count, 0);
                    system("pause");
                } else {
                    messages(2);
                }
                break;
            case 3: //Обработка
                if (init) {
                    processed.asInteger = leftShift(source.asInteger, count);
                    processing = true;
                    messages(5);
                } else
                    messages(2);
                break;
            case 4:  //Вывод результата
                if (init)
                    if (processing) {
                        system("cls");
                        output(source, processed, count, 1);
                        system("pause");
                    } else
                        messages(3);
                else
                    messages(2);
                break;
            case 5: //Выход
                messages(4);
                break;
            default:
                messages(7);
        }
    } while (menuItem != 5);

    return 0;
}

//*****************************************************************************************
//Функция меню
int menu() {
    int Q;
    system("cls");
    puts("Главное меню");
    puts("0 - Справка");
    puts("1 - Ввод числа");
    puts("2 - Вывод исходных данных");
    puts("3 - Обработка");
    puts("4 - Вывод результата");
    puts("5 - Выход");
    printf("Введите номер пункта - ");
    scanf("%d", &Q);
    fflush(stdin);
    return Q;
}

//*****************************************************************************************
//Функция вывода символа и кода символа
void output(UnitedFLOAT source, UnitedFLOAT processed, int count, int key) {
    printf("Количество сдвигов - %d\n", count);
    printf("Исходное число - %.6f\n", source.asFloat);
    printf("Следующие числа в двоичном представлении\n");
    printf("Знак - %ld, Порядок - ", (source.asInteger >> 31) & 0x00000001);
    for (int i = 30; i >= 23; i--)
        printf("%ld", source.asInteger >> i & 0x01);
    printf(" Мантисса - ");
    for (int i = 22; i >= 0; i--) {
        if (i == 19 || i == 11)
            printf(" ");
        printf("%ld", source.asInteger >> i & 0x000001);
    }
    if (key) {
        puts("");
        printf("Сформированное число - %.6f\n", processed.asFloat);
        printf("Следующие числа в двоичном представлении\n");
        printf("Знак - %d, Порядок - ", (processed.asInteger >> 31) & 0x00000001);
        for (int i = 30; i >= 23; i--)
            printf("%ld", processed.asInteger >> i & 0x01);
        printf(" Мантисса - ");
        for (int i = 22; i >= 0; i--) {
            if (i == 19 || i == 11)
                printf(" ");
            printf("%ld", processed.asInteger >> i & 0x000001);
        }
    }
    puts("");
}

//*****************************************************************************************
//Функция обработки
long int leftShift(long int n, int k) {
    return (((n & 0xFF000) << k | n >> (8 - k)) & 0xFF000) | (n & 0xFFF00FFF);
}

//*****************************************************************************************
//Функция ввода целочисленных переменных в диапазоне
int enterNum(int first, int last) {
    int num;
    bool check_num, check_all;
    char str[4];
    const char numbers[] = "0123456789";
    do {
        check_all = true;
        check_num = false;
        scanf("%s", &str);
        fflush(stdin);
        for (int i = 0; str[i] != '\0' && check_all; i++) {
            for (int j = 0; numbers[j] != '\0' && !check_num; j++)
                if (str[i] == numbers[j] || str[i] == '\0')
                    check_num = true;
            if (check_num)
                check_num = false;
            else
                check_all = false;
        }
        if (check_all)
            num = atoi(str);
        else
            printf("В строку попало что-то кроме числа, повторите ввод:\n");
        if ((num < first || num > last) && check_all)
            printf("Возможно вы ошиблись при вводе?\nВведите число от %d до %d\nПовторите ввод: ", first, last);
    } while (num < first || num > last || !check_all);
    return num;
}

//*****************************************************************************************
//Функция вывода сообщений пользователю
void messages(int messageId) {
    system("cls");
    switch (messageId) {
        case 1:
            puts("Данные введёны успешно");
            break;
        case 2:
            puts("Исходные данные не введены, выберите 1 пункт меню для ввода");
            break;
        case 3:
            puts("Мантисса не обработана, выберите 3 пункт меню для обработки");
            break;
        case 4:
            puts("До новых встреч!");
            break;
        case 5:
            puts("Данные обработаны успешно");
            break;
        case 7:
            puts("Что-то пошло не так, повтороите ввод");
            break;
    }
    system("pause");
}
