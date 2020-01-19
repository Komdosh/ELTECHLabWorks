#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

typedef struct stWood {
    char Deck[10];
    char Neck[10];
} WOOD;

typedef struct stGuitars {
    char Name[10];
    int Strings;
    int Year;
    WOOD Wood;
} GUITARS;

void Help();

int Menu();

GUITARS *alloc_memory(GUITARS *mGuitars, int Count);

GUITARS *enter(GUITARS *, int *);

GUITARS *enter_struct(GUITARS *, int);

int enter_num(char *, int, int);

GUITARS *processing(GUITARS *, int, int *, int);

void output_struct(GUITARS *, int);

void Messages(int);

GUITARS *freeStructure(GUITARS *);

GUITARS *processing_menu(GUITARS *, int, int *);

int main() {
    GUITARS *mGuitars = NULL, *NewGuitars = NULL;
    int menuItem, Count = 0, NewCount = 0;
    bool CheckOfProcess = false;
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do {
        menuItem = Menu();
        switch (menuItem) {
            case 1:
                Help();
                break;
            case 2:
                mGuitars = freeStructure(mGuitars);
                NewGuitars = freeStructure(NewGuitars);
                NewCount = Count = 0;
                mGuitars = enter(mGuitars, &Count);
                Messages(3);
                CheckOfProcess = false;
                break;
            case 3:
                if (Count)
                    output_struct(mGuitars, Count);
                else
                    Messages(1);
                break;
            case 4:
                CheckOfProcess = true;
                if (Count) {
                    NewCount = 0;
                    NewGuitars = freeStructure(NewGuitars);
                    NewGuitars = processing_menu(mGuitars, Count, &NewCount);
                    if (NewCount)
                        Messages(5);
                    else
                        Messages(6);
                } else
                    Messages(1);
                break;
            case 5:
                if (Count)
                    if (CheckOfProcess)
                        if (NewCount)
                            output_struct(NewGuitars, NewCount);
                        else
                            Messages(6);
                    else
                        Messages(2);
                else
                    Messages(1);
                break;
            case 6:
                Messages(8);
                break;
            default:
                Messages(7);
        }
    } while (menuItem != 6);
    freeStructure(mGuitars);
    freeStructure(NewGuitars);
    return 0;
}

//*****************************************************************************************
//Функция справка
void Help() {
    system("cls");
    puts("\n\n  Данная программа предназначена для организации структуры и обработки данных.");
    puts(" Выборка составляется из гитар до выбранного года производства.");
    puts(" Если возникли проблемы обращайтесь, пожалуйста, на электронную почту:");
    puts(" komdosh@gelezo2.ru\n");
    system("pause");
}

//*****************************************************************************************
//Функция меню
int Menu() {
    int Q;
    system("cls");
    puts("Главное меню");
    puts("1 - Справка");
    puts("2 - Ввод данных в структуру");
    puts("3 - Вывод исходных данных");
    puts("4 - Обработка данных");
    puts("5 - Вывод результата");
    puts("6 - Выход");
    printf("Введите номер пункта - ");
    scanf("%d", &Q);
    printf("\n");
    fflush(stdin);
    return Q;
}

//*****************************************************************************************
//Функция выделения памяти
GUITARS *alloc_memory(GUITARS *mGuitars, int Count) {
    mGuitars = (GUITARS *) realloc(mGuitars, Count * sizeof(GUITARS));
    return mGuitars;
}

//*****************************************************************************************
//Функция ввода данных
GUITARS *enter(GUITARS *mGuitars, int *Count) {
    int Q;
    do {
        (*Count)++;
        mGuitars = alloc_memory(mGuitars, *Count);
        system("cls");
        mGuitars = enter_struct(mGuitars, *Count);
        puts("Добавить объект? Введите 1 для продолжения, 2 для завершения ввода.");
        scanf("%d", &Q);
        fflush(stdin);
    } while (Q != 2);
    return mGuitars;
}

//*****************************************************************************************
//Функция ввода данных в поля
GUITARS *enter_struct(GUITARS *mGuitars, int Count) {
    printf("Введите марку %d гитары (не более 10 символов): ", Count);
    do {
        gets(mGuitars[Count - 1].Name);
        fflush(stdin);
        if (strlen(mGuitars[Count - 1].Name) > 10)
            printf("Возможно вы ошиблись при вводе?\n(кол-во символов не больше 10)\nПовторите ввод: ");
    } while (strlen(mGuitars[Count - 1].Name) > 10);
    mGuitars[Count - 1].Strings = enter_num("количество струн", 1, 20);
    mGuitars[Count - 1].Year = enter_num("год производства", 1899, 2015);
    printf("Введите название дерева грифа (не более 10 символов): ");
    do {
        gets(mGuitars[Count - 1].Wood.Neck);
        fflush(stdin);
        if (strlen(mGuitars[Count - 1].Wood.Neck) > 10)
            printf("Возможно вы ошиблись при вводе?\n(кол-во символов не больше 10)\nПовторите ввод: ");
    } while (strlen(mGuitars[Count - 1].Wood.Neck) > 10);
    printf("Введите название дерева корпуса (не более 10 символов): ");
    do {
        gets(mGuitars[Count - 1].Wood.Deck);
        fflush(stdin);
        if (strlen(mGuitars[Count - 1].Wood.Deck) > 10)
            printf("Возможно вы ошиблись при вводе?\n(кол-во символов не больше 10)\nПовторите ввод: ");
    } while (strlen(mGuitars[Count - 1].Wood.Deck) > 10);
    return mGuitars;
}

//*****************************************************************************************
//Функция ввода целочисленных переменных
int enter_num(char *str, int first, int last) {
    int num;
    printf("Введите %s (от %d до %d): ", str, first, last);
    do {
        scanf("%d", &num);
        fflush(stdin);
        if (num <= first || num > last)
            printf("Возможно вы ошиблись при вводе?\nВведите число от %d до %d\nПовторите ввод: ", first, last);
    } while (num <= first || num > last);
    return num;
}

//*****************************************************************************************
//Функция подменю обработки
GUITARS *processing_menu(GUITARS *mGuitars, int Count, int *NewCount) {
    GUITARS *NewGuitars = NULL;
    int Q, temp, i;
    do {
        system("cls");
        puts("Меню поиска, выберите по какому пункту сделать выборку");
        puts("1 - Год производства");
        puts("2 - Количество струн");
        printf("Введите номер пункта - ");
        scanf("%d", &Q);
        fflush(stdin);
        switch (Q) {
            case 1:
                NewGuitars = processing(mGuitars, Count, NewCount, 1);
                break;
            case 2:
                NewGuitars = processing(mGuitars, Count, NewCount, 2);
                break;
            default:
                Messages(7);
        }
    } while (Q != 1 && Q != 2);
    return NewGuitars;
}

//*****************************************************************************************
//Функция обработки данных
GUITARS *processing(GUITARS *mGuitars, int Count, int *NewCount, int key) {
    GUITARS *NewGuitars = NULL;
    int Q, temp, i;
    if (key == 1) {

        temp = enter_num("до какого года производства выводить результаты", 1899, 2015);
        for (i = 0; i < Count; i++)
            if (mGuitars[i].Year <= temp) {
                (*NewCount)++;
                NewGuitars = alloc_memory(NewGuitars, *NewCount);
                NewGuitars[*NewCount - 1] = mGuitars[i];
            }
    } else {

        temp = enter_num("до скольки струн выводить результаты", 0, 20);
        for (i = 0; i < Count; i++)
            if (mGuitars[i].Strings == temp) {
                (*NewCount)++;
                NewGuitars = alloc_memory(NewGuitars, *NewCount);
                NewGuitars[*NewCount - 1] = mGuitars[i];
            }
    }
    return NewGuitars;
}

//*****************************************************************************************
//Функция вывода данных
void output_struct(GUITARS *mGuitars, int Count) {
    system("cls");
    printf("================================================================================");
    printf("%12s  | %18s | %14s | %17s\n", " ", " ", " ", "Дерево:");
    printf("%12s  | %18s | %14s | %s\n", "Название", "Год производства", "Кол-во струн", "_________________________");
    printf("%12s  | %18s | %14s | %11s | %6s\n", " ", " ", " ", "Корпус", "Гриф");
    printf("================================================================================");
    for (int i = 0; i < Count; i++) {
        printf("%12s  | %18d | %14d | %11s | %6s ", mGuitars[i].Name, mGuitars[i].Year, mGuitars[i].Strings,
               mGuitars[i].Wood.Deck, mGuitars[i].Wood.Neck);
        printf("\n================================================================================");
    }
    system("pause");
}

//*****************************************************************************************
//Функция вывода сообщений пользователю
void Messages(int messageId) {
    system("cls");
    switch (messageId) {
        case 1:
            puts("Сначала необходимо ввести данные.");
            break;
        case 2:
            puts("Вы ввели данные, но не обработали их.");
            puts("Вам необходимо выбрать 4 пункт меню для обработки данных.");
            break;
        case 3:
            puts("Данные введены успешно.");
            break;
        case 4:
            puts("Ошибка, данные не были введены.");
            puts("Попробуйте ввести данные повторно.");
            break;
        case 5:
            puts("Выборка из данных успешно сформирована.");
            break;
        case 6:
            puts("Выборка из данных не была сформирована.");
            puts("В исходных данных не нашлось таких результатов.");
            break;
        case 7:
            puts("Что-то пошло не так, введите пункт меню повторно.");
            break;
        case 8:
            puts("До новых встреч!");
            break;
    }
    system("pause");
}

//*****************************************************************************************
//Функция освобождения памяти
GUITARS *freeStructure(GUITARS *mGuitars) {
    if (mGuitars != NULL)
        free(mGuitars);
    return NULL;
}
