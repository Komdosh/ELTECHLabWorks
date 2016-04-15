#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

typedef struct stWood
  {
    char Deck[10];                                            //Дерево корпуса
    char Neck[10];                                            //Дерево грифа
  } WOOD;

typedef struct stGuitars
  {
    char Name[10];                                            //Название гитары
    int Strings;                                              //Кол-во струн
    int Year;                                                 //Год производства
    WOOD Wood;                                                //Дерево
  } GUITARS;

typedef struct stList
  {
    GUITARS Guitars;                                          //Структура с информационными полями
    struct stList *next;                                      //Следующий элемент
    struct stList *prev;                                      //Предыдущий элемент
  } sLIST;

typedef sLIST* LIST;                                          //Указатель на элемент списка

void menu();                                                  //Прототип функции Главного меню
void messages(int Key);                                       //Прототип функции вывода сообщения
void enterMenu(LIST* list);                                   //Прототип функции подменю ввода элементов
int enterNum(int first, int last);                            //Прототип функции ввода целочисленных значений в диапазоне
void outputMenu(LIST list);                                   //Прототип функции подменю вывода
void outputList(LIST list, int Key);                          //Прототип функции вывода списка
LIST addNth(LIST list, LIST temp, int n);                     //Прототип функции добавления n-го элемента
LIST enterField();                                            //Прототип функции ввода инф. полей
void enterWord(char* str);                                    //Прототип функции ввода слова
void fr(LIST *list);                                          //Прототип функции освобождения списка
const char* fileName(int Key);                                //Прототип функции ввода имени файла
int recordFile(LIST list, const char* name);                  //Прототип функции записи в файл
LIST readFile(const char* name);                              //Прототип функции чтения файла
LIST getElem(LIST list, int Key, int n);                      //Прототип функции нахождения элементов
int count(LIST list);                                         //Прототип функции подсчёта количества элементов

int main()
  {
   system("mode con cols=80 lines=20");
   LIST list=NULL;
   int Q;
   system("chcp 1251");
   do
    {
     menu();
     switch (Q=enterNum(1, 4))
      {
       case 1:
              enterMenu(&list);
              break;
       case 2:
              outputMenu(list);
              break;
       case 3:
              messages(8);
              break;
      }
    }
   while(Q!=3);
   fr(&list);
   return 0;
  }
//*****************************************************************************************
//Функция меню
void menu()
  {
   system("cls");
   puts("Главное меню");
   puts("1 - Добавление элементов в список");
   puts("2 - Вывод списка");
   puts("3 - Выход");
   printf("Введите номер пункта - ");
  }
//*****************************************************************************************
//Функция подменю добавления элементов
void enterMenu(LIST* list)
 {
   LIST temp;
   int Q;
   do
   {
    system("cls");
    puts("Меню добавления элементов");
    puts("1 - Добавить элемент в начало списка");
    puts("2 - Добавить элемент в конец списка");
    puts("3 - Добавить элемент на выбранную позицию");
    puts("4 - Открыть список из файла");
    puts("5 - Вернуться в главное меню");
    printf("Введите номер пункта - ");
    switch(Q=enterNum(1,5))
     {
       case 1:
               temp=enterField();
              *list=addNth(*list, temp, 0);
              messages(11);
              break;
       case 2:
              if(*list)
                {
                 temp=enterField();
                 *list=addNth(*list, temp, count(*list));
                 messages(11);
                }
               else
                 messages(3);
               break;
       case 3:
              if(*list)
                if(count(*list)>1)
                  {
                   temp=enterField();
                   printf("Введите номер позиции, куда вставить элемент (от %d до %d): ", 2, (count(*list)>2)?count(*list)-1:count(*list));
                   *list=addNth(*list, temp, enterNum(2, count(*list))-1);
                   messages(11);
                  }
                 else
                   messages(12);
               else
                 messages(3);
               break;
      case 4:
             if(*list)
               {
                system("cls");
                puts("Текущий список будет удалён, продолжить?");
                puts("Для продолжения нажмите Enter, для отмены нажмите любую другую клавишу");
                if(getch()=='\n')
                  {
                   fr(list);
                   *list=readFile(fileName(2));
                  }
               }
             else
               *list=readFile(fileName(2));
             if(*list)
               messages(15);
             else
               messages(17);
             break;
      }
   }
  while(Q!=5);
 }
//*****************************************************************************************
//Функция добавления n-го элемента
LIST addNth(LIST list, LIST temp, int n)
  {
    if(!n)
     {
       if(list)
         list->prev = temp;
       temp->next = list;
       temp->prev = NULL;
       list = temp;
       return temp;
     }
    else
     {
      list = getElem(list, 2, n);
      if(list->next)
       {
        temp->next = list->next;
        temp->prev = list;
        list->next->prev = temp;
       }
      else
       {
        temp->next = NULL;
        temp->prev = list;
       }
      list->next = temp;
      return getElem(list, 0, 0);
     }
  }
//****************************************************************************************
//Функция ввода данных в поля
LIST enterField()
  {
   system("cls");
   LIST list=(LIST)malloc(sizeof(sLIST));
   printf("Введите марку гитары (кол-во символов от 1 до 10): ");
   enterWord(list->Guitars.Name);
   printf("Введите количество струн (от %d до %d): ", 1, 20);
   list->Guitars.Strings=enterNum(1, 20);
   //list->Guitars.Strings=1;
   printf("Введите год производства (от %d до %d): ", 1899, 2015);
   //list->Guitars.Year=enterNum(1899, 2015);
   list->Guitars.Year=200;
   printf("Введите название дерева грифа (кол-во символов от 1 до 10): ");
   enterWord(list->Guitars.Wood.Neck);
   printf("Введите название дерева корпуса (кол-во символов от 1 до 10): ");
   enterWord(list->Guitars.Wood.Deck);
   return list;
  }
//*****************************************************************************************
//Функция ввода слова
void enterWord(char* str)
  {
    do
     {
      //gets(str);
      strcpy(str, "Something");
      fflush(stdin);
      if(strlen(str)<1 || strlen(str)>10)
      printf("Возможно вы ошиблись при вводе?\n(кол-во символов от 1 до 10)\nПовторите ввод: ");
     }
    while(strlen(str)<1 || strlen(str)>10);
  }
//*****************************************************************************************
//Функция ввода целочисленных переменных в диапазоне
int enterNum(int first, int last)
  {
   int num;
   bool check_num, check_all;
   char str[4];
   const char numbers[]="0123456789";
   do
    {
     check_all=true;
     check_num=false;
     scanf("%s", &str);
     fflush(stdin);
     for(int i=0; str[i]!='\0' && check_all; i++)
       {
        for(int j=0; numbers[j]!='\0' && !check_num; j++)
          if(str[i]==numbers[j] || str[i]=='\0')
            check_num=true;
        if(check_num)
          check_num=false;
        else
          check_all=false;
       }
     if(check_all)
       num=atoi(str);
     else
       printf("В строку попало что-то кроме числа, повторите ввод:\n");
     if((num < first || num > last) && check_all)
       printf("Возможно вы ошиблись при вводе?\nВведите число от %d до %d\nПовторите ввод: ", first, last);
    }
   while(num < first || num > last || !check_all);
   return num;
  }
//*****************************************************************************************
//Функция освобождения памяти
void fr(LIST *list)
  {
   if(*list)
     {
      for(;(*list)->next; (*list)=(*list)->next, free((*list)->prev));
      free(*list);
      (*list)=NULL;
     }
  }
//*****************************************************************************************
//Функция ввода названия файла
const char* fileName(int Key)
 {
    system("cls");
    char name[10], *temp;
    switch(Key)
    {
     case 1:
             puts("Задайте имя файла");
             puts("Если такой файл не существует, он будет создан, иначе - перезаписан");
             break;
     case 2:
             puts("Введите имя файла");
             break;
     }
    printf("Имя файла - ");
    enterWord(name);
    temp=(char*)malloc(strlen(name)*sizeof(char));
    strcpy(temp, name);
    return temp;
 }
//*****************************************************************************************
//Функция записи в файл
int recordFile(LIST list, const char* name)
  {
   FILE* file;
   system("cls");
   if(file=fopen(name,"w"))
     {
      while(list)
       {
        fwrite(&(list->Guitars),sizeof(list->Guitars),1,file);
        list=list->next;
       }
      fclose(file);
      return 0;
     }
   else
     return 1;
  }
//*****************************************************************************************
//Функция чтения файла
LIST readFile(const char* name)
  {
   LIST list=NULL, temp;
   FILE* file;
   system("cls");
   if(!(file=fopen(name,"r")))
     return NULL;
   while(!feof(file))
    {
     temp=(LIST)malloc(sizeof(sLIST));
     fread(&(temp->Guitars),sizeof(temp->Guitars),1,file);
     if(!list)
       list=addNth(list, temp, 0);
     else
       list=addNth(list, temp, count(list));
    }
   temp=getElem(list, 1, 0);
   if(!temp->prev)
     list = NULL;
   else
     temp->prev->next = NULL;
   free(temp);
   fclose(file);
   return getElem(list,0,0);
  }
//*****************************************************************************************
//Функция подменю вывода
void outputMenu(LIST list)
  {
   system("cls");
   if(list)
    {
     puts("Меню вывода списка");
     puts("1 - Вывести список на экран");
     puts("2 - Сохранить список в файл");
     puts("3 - Вернуться в главное меню");
     switch(enterNum(1,3))
      {
       case 1:
              system("cls");
              puts("Список с начала или с конца?");
              puts("1 - С начала");
              puts("2 - С конца");
              printf("Введите номер пункта (от %d до %d): ", 1, 2);
              outputList(list, enterNum(1,2)-1);
              break;
       case 2:
              if(!recordFile(list, fileName(1)))
                messages(14);
              else
                messages(18);
              break;
      }
    }
   else
     messages(9);
  }
//*****************************************************************************************
//Функция вывода данных
void outputList(LIST list, int Key)
  {
   system("mode con cols=80 lines=47");
   if(Key)
    list=getElem(list, 1, 0);
   system("cls");
   printf("================================================================================");
   printf("%12s  | %18s | %14s | %17s\n", " ", " ", " ", "Дерево:");
   printf("%12s  | %18s | %14s | %s\n", "Название", "Год производства", "Кол-во струн","_________________________");
   printf("%12s  | %18s | %14s | %11s | %6s\n", " ", " ", " ", "Корпус", "Гриф" );
   printf("================================================================================");
   while(list)
    {
     printf("%12s  | %18d | %14d | %11s | %6s ",list->Guitars.Name, list->Guitars.Year,
            list->Guitars.Strings, list->Guitars.Wood.Deck, list->
            Guitars.Wood.Neck);
     printf("\n================================================================================");
     if(list->prev && Key || list->next && !Key)
       printf("Для вывода следующего элемента нажмите любую клавишу\r");
     else
        puts("Для завершения просмотра нажмите любую клавишу");
     getch();
     list=(Key)?list->prev:list->next;
    }
   system("mode con cols=80 lines=20");
  }
//*****************************************************************************************
//Функция нахождения последнего элемента
LIST getElem(LIST list, int Key, int n)//Key: 0 - начало, 1 - конец, 2 - n-ый
  {
   for(;list->prev && Key==0; list=list->prev);
   for(;list->next && Key==1; list=list->next);
   for(int i = 1; i < n && list->next && Key==2; i++,list=list->next);
   return list;
  }
//*****************************************************************************************
//Функция подсчёта кол-ва элементов
int count(LIST list)
  {
   int Count;
   for(Count=0; list; list=list->next, Count++);
   return Count;
  }
//*****************************************************************************************
//Функция вывода сообщений пользователю
void messages(int Key)
  {
   system("cls");
   switch(Key)
    {
     case 7:
            puts("Что-то пошло не так, введите пункт меню повторно");
            break;
     case 8:
            puts("До новых встреч!");
            break;
     case 9:
            puts("Список пуст");
            puts("Для выполнения этого действия, создайте список");
            break;
     case 11:
             puts("Элемент успешно добавлен");
             puts("Для просмотра выберите пункт 'Вывод списка' -> 'Исходный список'");
             break;
     case 12:
             puts("Для того чтобы добавить элемент по позиции, необходимо наличие как минимум\n2-х элементов");
             break;
     case 14:
             puts("Список успешно записан в файл");
             break;
     case 15:
             puts("Список успешно считан с файла");
             break;
     case 17:
             puts("Файл пустой или файла с таким именем не существует");
             puts("Измените имя файла!");
             break;
     case 18:
             puts("Список не записан. Возникли проблемы с файлом, обратитесь к разработчику.");
             puts("Komdosh@gelezo2.ru");
             break;
    }
   system("pause");
  }
