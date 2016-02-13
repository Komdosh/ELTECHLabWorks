#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include<conio.h>

typedef struct stWood
  {
    char Deck[10];                                                   //Дерево корпуса
    char Neck[10];                                                   //Дерево грифа
  } WOOD;

typedef struct stGuitars 
  {
    char Name[10];                                                   //Название гитары
    int Strings;                                                     //Кол-во струн
    int Year;                                                        //Год производства
    WOOD Wood;                                                       //Дерево
  } GUITARS;

typedef struct stList
  {
    GUITARS Guitars;                                                 //Структура
    struct stList *next;                                             //След. элемент
  } LIST;


void Help();                                                          //Прототип функции справка
int Menu();                                                           //Прототип функции Главного меню
int Choose_list();                                                    //Прототип функции выбора списка
LIST* enter_menu(LIST* Guitars_list, int* Count);                     //Прототип функции подменю ввода элементов
int enter_num(int first, int last);                                   //Прототип функции ввода целочисленных значений в диапазоне
void Output_list(LIST *Guitars_list);                                 //Прототип функции вывода списка
void Add_First(LIST **Guitars_list);                                  //Прототип функции добавления 1-го элемента
void Add(LIST *Guitars_list, int n);                                  //Прототип функции добавления n-го элемента
LIST* enter_field();                                                  //Прототип функции ввода инф. полей
LIST* delete_menu(LIST* Guitars_list, int* Count);                    //Прототип функции подменю удаления элементов
void Del(LIST **Guitars_list, int n, int Key);                        //Прототип функции удаления n-го элемента
void fr(LIST **Guitars_list);                                         //Прототип функции очистка списка
LIST* sort_menu(LIST* Guitars_list);                                  //Прототип функции подменю сортировки
LIST* Sort(LIST *Guitars_list, int key);                              //Прототип функции сортировки
LIST* processing_menu(LIST *Guitars_list, int *NewCount);             //Прототип функции подменю поиска
LIST* Search(LIST *Guitars_list,int *NewCount, int key, int tempint); //Прототип функции поиска				
void Messages(int Key);                                               //Прототип функции вывода сообщения

int main()
  {
   system("mode con cols=80 lines=40");
   LIST *Guitars_list=NULL, *New_Guitars_list=NULL;
   int Q, NewCount=0, Count=0, key;
   bool Process=false; //process - был ли поиск
   setlocale(LC_ALL, "RUS");
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);
   do
    {
     Q = Menu();
     switch (Q)
      {
       case 1:
              Help();
              break;
       case 2:
              Guitars_list=enter_menu(Guitars_list, &Count);	 
              Process=false;
              break;
       case 3:
              if(Guitars_list)
                Guitars_list=delete_menu(Guitars_list, &Count);
              else
                Messages(9);
              break;
       case 4:
              if(Guitars_list)
                {
                 key=Choose_list();
                 if(key)
                   if(Process)
                     if(NewCount)
                       Output_list(New_Guitars_list); 
                     else
                       Messages(6);
                   else
                     Messages(2);
                 else
                   Output_list(Guitars_list);
                }
              else
                Messages(1);
              break;
       case 5:
              Process=true;
              if(Guitars_list)
                {
                 NewCount=0; 
                 fr(&New_Guitars_list);
                 New_Guitars_list=processing_menu(Guitars_list, &NewCount);
                 if(NewCount)
                   Messages(5);
                 else
                   Messages(6);
               }
              else
                Messages(1);
              break;
       case 6:
              if(Guitars_list)
                {
                 key=Choose_list();
                 if(key)
                   if(Process)
                     if(NewCount)
                       New_Guitars_list=sort_menu(New_Guitars_list); 
                     else
                       Messages(6);
                   else
                     Messages(2);
                 else
                   Guitars_list=sort_menu(Guitars_list);
                }
              else
                Messages(1);
              break;
       case 7:
              Messages(8);
              break;							
       default:
               Messages(7);
      }	
    }
   while (Q!=7);
   fr(&Guitars_list);
   fr(&New_Guitars_list);
   return 0;
  }
//*****************************************************************************************
//Функция справка
void Help()
  {
   system("cls");
   puts("\n\n  Данная программа предназначена для создания односвязного списка с возможностью выборки.");
   puts("  Выборка составляется из гитар до выбранного года производства или по кол-ву\n струн.");
   puts("  Если возникли проблемы обращайтесь, пожалуйста, на электронную почту:");
   puts(" komdosh@gelezo2.ru\n");
   system("pause");
  }
//*****************************************************************************************
//Функция меню
int Menu()
  {
   int Q;
   system("cls");
   puts("Главное меню");
   puts("1 - Справка");
   puts("2 - Добавить элемент в список");
   puts("3 - Удалить элемент из списка");
   puts("4 - Вывод списков");
   puts("5 - Поиск");
   puts("6 - Сортировка");		
   puts("7 - Выход");
   printf("Введите номер пункта - ");
   scanf("%d", &Q);
   printf("\n");
   fflush(stdin);
   return Q;
  }
//*****************************************************************************************
//Функция выбора списка
int Choose_list()
  {
   int key;
   puts("Для какого списка выполнить это действие?");
   puts("1 - Исходный список");
   puts("2 - Сформированный список");
   printf("Введите номер пункта (от %d до %d): ", 1, 2);
   key=enter_num(1, 2);
   return (key-1);
  }	
//*****************************************************************************************
//Функция подменю добавления элементов
LIST* enter_menu(LIST* Guitars_list, int* Count)
  {
   int Q, temp;
   do
    {
     system("cls");
     puts("Меню добавления элементов");
     puts("1 - Добавить элемент в начало списка");
     puts("2 - Добавить элемент в конец списка");
     puts("3 - Добавить элемент на выбранную позицию");
     puts("4 - Вернуться в главное меню");
     printf("Введите номер пункта - ");
     scanf("%d", &Q);
     fflush(stdin);
     switch(Q)
      {
       case 1:
              Add_First(&Guitars_list);		
              (*Count)++;
              Messages(11);
              break;
       case 2:
              if(*Count)
                {
                 Add(Guitars_list, 5678);										 			
                 (*Count)++;
                 Messages(11);
                }
              else
                Messages(3);
              break;	
       case 3: 
              if(*Count)
                {
                 if((*Count)>1)
                   {
                    printf("Введите номер позиции, куда вставить элемент (от %d до %d): ", 2, *Count);
                    temp=enter_num(2, *Count);
                    Add(Guitars_list, (temp-1));
                    (*Count)++;						
                    Messages(11);						 				
                   }
                 else		
                   Messages(13);
                }
              else
                Messages(3);
              break;
       default:
               if(Q!=4)
                 Messages(7);
      }
    }
   while(Q!=4);		
   return Guitars_list;
  }	
//*****************************************************************************************
//Функция добавления 1-го элемента
void Add_First(LIST **Guitars_list)  
  {
    LIST *temp = enter_field();
    temp->next = (*Guitars_list);
    (*Guitars_list)=temp;
  }
//*****************************************************************************************
//Функция добавления n-го элемента
void Add(LIST *Guitars_list, int n) 
  {
    LIST *temp = enter_field();
    for(int i = 1; i < n && Guitars_list->next; i++)
      Guitars_list = Guitars_list->next;  
    if(Guitars_list->next)
      temp->next = Guitars_list->next;
    else
      temp->next = NULL;
    Guitars_list->next = temp;					
  }
//*****************************************************************************************
//Функция ввода данных в поля
LIST* enter_field()
  {
   system("cls");
   LIST* Guitars_list=(LIST*)malloc(sizeof(LIST));
   printf("Введите марку гитары (кол-во символов от 1 до 10): ");
   do
    {
     //gets(Guitars_list->Guitars.Name);
     Guitars_list->Guitars.Name[0]='w';
     fflush(stdin);
     if(strlen(Guitars_list->Guitars.Name)<1 || strlen(Guitars_list->Guitars.Name)>10)
       printf("Возможно вы ошиблись при вводе?\n(кол-во символов не больше 10)\nПовторите ввод: ");
    }									 
   while(strlen(Guitars_list->Guitars.Name)<1 || strlen(Guitars_list->Guitars.Name)>10);
   printf("Введите количество струн (от %d до %d): ", 1, 20);
   Guitars_list->Guitars.Strings=enter_num( 1, 20);
   //Guitars_list->Guitars.Strings=1;
   printf("Введите год производства (от %d до %d): ", 1899, 2015);
   //Guitars_list->Guitars.Year=enter_num( 1899, 2015);
   Guitars_list->Guitars.Year=200;
   printf("Введите название дерева грифа (кол-во символов от 1 до 10): ");
   do
    {
     //gets(Guitars_list->Guitars.Wood.Neck);
     Guitars_list->Guitars.Wood.Neck[0]='w';
     fflush(stdin);
     if(strlen(Guitars_list->Guitars.Wood.Neck)<1 || strlen(Guitars_list->Guitars.Wood.Neck)>10)
       printf("Возможно вы ошиблись при вводе?\n(кол-во символов от 1 до 10)\nПовторите ввод: ");
    }									 
   while(strlen(Guitars_list->Guitars.Wood.Neck)<1 || strlen(Guitars_list->Guitars.Wood.Neck)>10);
   printf("Введите название дерева корпуса (кол-во символов от 1 до 10): ");
   do
    {
     //gets(Guitars_list->Guitars.Wood.Deck);
     Guitars_list->Guitars.Wood.Deck[0]='q';
     fflush(stdin);
     if(strlen(Guitars_list->Guitars.Wood.Deck)<1 || strlen(Guitars_list->Guitars.Wood.Deck)>10)
     printf("Возможно вы ошиблись при вводе?\n(кол-во символов от 1 до 10)\nПовторите ввод: ");
    }									 
   while(strlen(Guitars_list->Guitars.Wood.Deck)<1 || strlen(Guitars_list->Guitars.Wood.Deck)>10);
   return Guitars_list;
  }
//*****************************************************************************************
//Функция ввода целочисленных переменных в диапазоне
int enter_num(int first, int last)
  {
   int num;
   bool check_num, check_all;
   char str[5];
   const char numbers[]="0123456789";
   do
    {	
     check_all=true;
     check_num=false;
     scanf("%s", &str);
     fflush(stdin);
     for(int i=0; str[i]!='\0' && check_all && str[i]!='\n'; i++)
       {
        for(int j=0; numbers[j]!='\0' && !check_num; j++)
          if(str[i]==numbers[j] || str[i]=='\n')
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
//Функция подменю удаления элементов	
LIST* delete_menu(LIST* Guitars_list, int* Count)
  {
   int Q,temp;
   do
    {
     system("cls");
     puts("Меню удаления элементов");
     puts("1 - Удалить первый элемент в списке");
     puts("2 - Удалить последний элемент в списке");
     puts("3 - Удалить элемент по его позиции");
     puts("4 - Очистить список");
     puts("5 - Вернутся в главное меню");
     printf("Введите номер пункта - ");
     scanf("%d", &Q);
     fflush(stdin);
     switch(Q)
      {
       case 1:
              if(Guitars_list)	
                {
                 Del(&Guitars_list, 0, 0);
                 (*Count)--;
                 Messages(10);	
                }
              else
                Messages(9);	
              break;
       case 2:
              if(Guitars_list)	
                {
                 Del(&Guitars_list, 0, 1);
                 (*Count)--;	
                 Messages(10);	
                }
              else
                Messages(9);		
              break;	
       case 3:
              if(Guitars_list)	
                {
                 if((*Count)>2)
                   {
                    printf("Введите номер позиции элемента, который следует удалить (от %d до %d): ", 2, (*Count));
                    temp=enter_num(2, (*Count));
                    Del(&Guitars_list, (temp-1), 2);
                    (*Count)--;
                    Messages(10);									 					
                   }
                 else
                   Messages(13);
                }
              else
                Messages(9);	 	
              break;																							
       case 4:		
              fr(&Guitars_list);
              (*Count)=0;	
              Messages(9);
              break;																															
       default:
               if(Q!=5)
                 Messages(7);
      }
    }
   while(Q!=5);		
   return Guitars_list;
  }	
//*****************************************************************************************
//Функция удаления n-го элемента в списке
void Del(LIST **Guitars_list, int n, int Key) 
  {
   LIST *pBwd = (*Guitars_list), *pFwd = NULL;
   switch(Key)
    {
     case 0:
            *Guitars_list = (*Guitars_list)->next;
            free(pBwd);					
            break;
     case 1:
            pFwd = *Guitars_list; 
            while(pFwd->next) 
             { 
              pBwd = pFwd;
              pFwd = pFwd->next;
             }
            if(!pBwd) 
              {
               free(*Guitars_list);
               *Guitars_list = NULL;
              } 
            else 
              {
               free(pFwd->next);
               pBwd->next = NULL;
              }
            break;				
     case 2:
            for(int i = 1; i < n && (*Guitars_list)->next; i++)
              (*Guitars_list) = (*Guitars_list)->next;
            pBwd = (*Guitars_list);  
            pFwd = pBwd->next;	
            pBwd->next = pFwd->next;
            free(pFwd);
            break;										
    }
  }	
//*****************************************************************************************
//Функция очистки списка                                  
void fr(LIST **Guitars_list)
  {
   LIST *pBwd=NULL;
   if(*Guitars_list)
     {
      while((*Guitars_list)->next) 
       {
        pBwd = (*Guitars_list);
        (*Guitars_list) = (*Guitars_list)->next;
        free(pBwd);
       }
      free(*Guitars_list);
      (*Guitars_list)=NULL;
     }
  } 
//*****************************************************************************************
//Функция подменю сортировки
LIST* sort_menu(LIST* Guitars_list)
  {
   LIST *temp=NULL;	                              
   int Q;
   do
    {
     system("cls");
     puts("Меню сортировки, выберите по какому пункту сделать сортировку");
     puts("1 - Год производства");
     puts("2 - Количество струн");
     puts("3 - Выход в главное меню");
     printf("Введите номер пункта - ");
     scanf("%d", &Q);
     fflush(stdin);
     if(Q!=3)      
       if(Q==1||Q==2) 
         temp=Sort(Guitars_list, Q);
       else
         Messages(7); 
     if(Q!=3)		
       Messages(4);    
    }
   while(Q!=3);
	 
   return temp;
  }
//*****************************************************************************************
//Функция сортировки данных	
LIST* Sort(LIST *Guitars_list, int key) 
  {
   LIST *temp,*sort=NULL,*pFwd,*pBwd;
   while(Guitars_list)
    { 
     temp = Guitars_list; 
     Guitars_list = Guitars_list->next;   
     for(pFwd=sort,pBwd=NULL;  pFwd && (temp->Guitars.Year > pFwd->Guitars.Year && key==1 || temp->Guitars.Strings > pFwd->Guitars.Strings && key==2); pBwd=pFwd,pFwd=pFwd->next);
        if(!pBwd) 
          { 
           temp->next=sort; 
           sort=temp; 
          }
        else 
          { 
           temp->next=pFwd; 
           pBwd->next=temp; 
          }   
    }	 			
   return sort;
  }			
//*****************************************************************************************
//Функция подменю обработки
LIST* processing_menu(LIST *Guitars_list, int *NewCount)
  {
   LIST *New_Guitars_list=NULL;	
   const char* str;
   int Q, temp, tempfirst, templast;
   do
    {
     system("cls");
     puts("Меню поиска, выберите по какому пункту сделать выборку");
     puts("1 - Год производства");
     puts("2 - Количество струн");
     puts("3 - Выход в главное меню");
     printf("Введите номер пункта - ");
     scanf("%d", &Q);
     fflush(stdin);
     switch(Q)
      {
       case 1:
              tempfirst=1899;
              templast=2015;
              str="до какого года производства";	
              break;
       case 2:
              tempfirst=1;
              templast=20;
              str="до какого количества струн";
              break;
       default:
       	       if(Q!=3)
                 Messages(7);
      }
     if(Q==1||Q==2)
       {
        printf("Введите %s выводить результаты (от %d до %d): ", str, tempfirst, templast);
        temp=enter_num(tempfirst, templast);
        *NewCount=0;
        New_Guitars_list=Search(Guitars_list, NewCount, Q, temp);
       }
    }
   while(Q!=3);	
   return New_Guitars_list;
  }
//*****************************************************************************************
//Функция обработки данных	
LIST* Search(LIST *Guitars_list,int *NewCount, int key, int tempint) 
  {
   LIST *search=NULL,*pFwd; 
     while(Guitars_list)
      {
      	if(Guitars_list->Guitars.Year<=tempint && key==1 || Guitars_list->Guitars.Strings<=tempint && key==2)
         {
          pFwd=search;
          search=(LIST*)malloc(sizeof(LIST));
          search->Guitars=Guitars_list->Guitars;
          search->next=pFwd;
          (*NewCount)++;
         }
       Guitars_list=Guitars_list->next;
      }
   return search;
  }	
//*****************************************************************************************
//Функция вывода данных
void Output_list(LIST *Guitars_list)
  {
   system("cls");
   printf("================================================================================");
   printf("%12s  | %18s | %14s | %17s\n", " ", " ", " ", "Дерево:");
   printf("%12s  | %18s | %14s | %s\n", "Название", "Год производства", "Кол-во струн","_________________________");
   printf("%12s  | %18s | %14s | %11s | %6s\n", " ", " ", " ", "Корпус", "Гриф" );
   printf("================================================================================");
   while(Guitars_list)
    {
     printf("%12s  | %18d | %14d | %11s | %6s ",Guitars_list->Guitars.Name, Guitars_list->Guitars.Year,
            Guitars_list->Guitars.Strings, Guitars_list->Guitars.Wood.Deck, Guitars_list->
            Guitars.Wood.Neck);
            printf("\n================================================================================");
     if(Guitars_list->next)
       printf("Для вывода следующего элемента нажмите любую клавишу\r");
     else
        puts("Для завершения просмотра нажмите любую клавишу");
     getch();
     Guitars_list=Guitars_list->next;	
    }
  }
//*****************************************************************************************
//Функция вывода сообщений пользователю
void Messages(int Key)
  {
   system("cls");
   switch(Key)
    {
     case 1:
            puts("Сначала необходимо ввести данные");
            break;
     case 2:
            puts("Вы ввели данные, но не обработали их");
            puts("Вам необходимо выбрать 5 пункт меню для поиска данных");
            break;
     case 3:
            puts("Для добавления последующих элементов, сначала необходимо добавить первый");
            break;
     case 4:
            puts("Сортировка успешно завершена");	
            break;
     case 5:
            puts("Выборка из данных успешно сформирована");
            break;
     case 6:
            puts("Выборка из данных не была сформирована");
            puts("В исходных данных не нашлось таких результатов");
            break;
     case 7:
            puts("Что-то пошло не так, введите пункт меню повторно");
            break;	
     case 8:
            puts("До новых встреч!");
            break;		
     case 9:
            puts("Список пуст");
            break;				
     case 10:	
             puts("Элемент удалён");		
             break;		
     case 11:	
             puts("Элемент успешно добавлен");		
             break;				
     case 13:	
             puts("Для того чтобы удалить элемент по позиции, необходимо наличие как минимум\n2-х элементов");		
             break;																				
    }
   system("pause");
  }
