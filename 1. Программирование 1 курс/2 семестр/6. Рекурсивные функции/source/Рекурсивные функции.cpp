#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

void help();                                                  //Прототип функции справка
void menu();                                                  //Прототип функции Главного меню
int
enterNum(int first, int last);                            //Прототип функции ввода целочисленных значений в диапазоне
unsigned long long processing(int num);                       //Прототип функции вычисления факториала
void messages(int Key);                                       //Прототип функции вывода сообщения

int main() {
    system("mode con cols=80 lines=20");
    int menuItem, sourceNum = 0;
    unsigned long long result = 0;
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do {
        menu();
        switch (menuItem = enterNum(1, 6)) {
            case 1: //Справка
                help();
                break;
            case 2: //Ввод числа
                system("cls");
                puts("Введите целое число от 1 до 65");
                printf("Введите число - ");
                sourceNum = enterNum(1, 65);
                messages(1);
                break;
            case 3: //Вывод исходного числа
                if (sourceNum) {
                    system("cls");
                    printf("Исходное число - %d\n", sourceNum);
                    system("pause");
                } else
                    messages(2);
                break;
            case 4:
                if (sourceNum) {
                    result = processing(sourceNum);
                    messages(5);
                } else
                    messages(2);
                break;
            case 5:
                if (result) {
                    system("cls");
                    printf("Факториал числа - %d = %llu\n", sourceNum, result);
                    system("pause");
                } else
                    messages(3);
                break;
            case 6:
                messages(4);
                break;
        }
    } while (menuItem != 6);
    return 0;
}

//*****************************************************************************************
//Функция справка
void help() {
    system("cls");
    puts("\n\n  Данная программа предназначена для вычисления факториала.");
    puts(" Если возникли проблемы обращайтесь, пожалуйста, на электронную почту:");
    puts(" komdosh@yandex.ru\n");
    system("pause");
}

//*****************************************************************************************
//Функция меню
void menu() {
    system("cls");
    puts("Главное меню");
    puts("1 - Справка");
    puts("2 - Ввод числа");
    puts("3 - Вывод исходного числа");
    puts("4 - Вычислить факториал числа");
    puts("5 - Вывод результата");
    puts("6 - Выход");
    printf("Введите номер пункта - ");
}

//*****************************************************************************************
//Функция вычисления факториала
unsigned long long processing(int num) {
    if (!num)
        return 1;
    else
        return num * processing(num - 1);
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
void messages(int Key) {
    system("cls");
    switch (Key) {
        case 1:
            puts("Число введено успешно");
            puts("Для просмотра выберите 3 пункт меню");
            break;
        case 2:
            puts("Исходное число не введёно, выберите 1 пункт меню для ввода");
            break;
        case 3:
            puts("Число не обработано, выберите 4 пункт меню для обработки");
            break;
        case 4:
            puts("До новых встреч!");
            break;
        case 5:
            puts("Число успешно обработано");
            puts("Для просмотра результата выберите 5 пункт меню");
            break;
    }
    system("pause");
}
