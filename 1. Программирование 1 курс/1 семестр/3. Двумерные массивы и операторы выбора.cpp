#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main()
{
  setlocale(LC_ALL, "RUS");
  const int n=30;
  int mas1[n][n],mas2[n][n],i,j,size1,size2,f,Q,check=0,check_2=0,g=0;
  do
   {
     printf("\n");
     puts("Главное меню");
     puts("1 - Ввод матрицы");
     puts("2 - Показать введённую матрицу");
     puts("3 - Обработка исходной матрицы ");
     puts("4 - Показать обработанную матрицу");
     puts("5 - Выход");
     printf("Введите номер пункта - ");
     scanf("%d",&Q);
     printf("\n");
     switch(Q)
       {
         case 1: //Ввод матрицы
                          printf("Введите кол-во строк массива (целые положительные числа от 1 до %d)\n",n);
                     do
                       {
                         scanf("%d", &size1);
                         if (size1 < 1 || size1 > n)
                         printf("Кол-во строк, целые положительные числа, от 1 до %d! Введите кол-во повторно!\n",n);
                            } 
                     while (size1 < 1 || size1 > n);
                          printf("Введите кол-во столбцов массива (целые положительные числа от 1 до %d)\n",n);
                    do
                      {
                         scanf("%d", &size2);
                         if (size2 < 1 || size2 > n)
                         printf("Кол-во столбцов, целые положительные числа, от 1 до %d! Введите кол-во повторно!\n",n);
                       } 
                    while (size2 < 1 || size2 > n);
                    for (i = 0; i < size1; i++)
                      {
                         printf("Введите элементы %d строки массива через пробел\n",i+1);
                         for (j = 0; j < size2;  scanf("%d", &mas1[i][j]), j++);
                       }
                    check=1;
                    break;   
         case 2: //Вывод матрицы
                    if (check==1)
                      { 
                         printf("Контрольный вывод элементов массива\n");
                         for (i = 0; i < size1; printf("\n"), i++)
                            for (j = 0; j < size2; printf("%5d", mas1[i][j]), j++);
                       }
                    else
                       printf("Для начала введите матрицу, выбрав 1 пункт в меню!\n");
                       break;
         case 3: //обработка матрицы 
                     check_2=1;		
                     if (check == 1)
                       for (g=j=0; j < size2; j++)
                        {
                           for (i = 0, f = 1; i < size1-1 && f==1; i++) 
                              f=(mas1[i][j] <= mas1[i+1][j])?1:0;
                           if (f==1)
                             {
                                for (i = 0; i < size1; mas2[i][g]=mas1[i][j], i++);
                                g++;
                             }
                        }
                     if (check != 1)
                       printf("Для начала введите матрицу, выбрав 1 пункт в меню!\n");
                     else
                       if (g!=0)
                          printf("Результат сформирован\n");
                       else
                          printf("Результат не может быть сформирован\n");
                     break;
         case 4: //Вывод обработанной матрицы
                     if (g!=0)
                       {
                         printf("Вывод обработанного массива:\n");
                         for (i = 0; i < size1; printf("\n"), i++)
                           for (j = 0; j < g; printf("%5d", mas2[i][j]), j++);
                       }
                     else
                        if (check != 1)
                          printf("Для начала введите матрицу, выбрав 1 пункт в меню!\n");
                        else
                           if (check_2!=1)
                             printf("Результат не сформирован\n");
                      else			 		                       
                        printf("Результат не может быть сформирован\n");
                     break;
         case 5://выход
                     puts("До новых встреч.");
                     puts("Если возникли вопросы или проблемы обращайтесь на электронную почту: ");
                     puts("komdosh@gelezo2.ru");
                     system("pause");
                     break;
         default:
                     printf("Что-то пошло не так, введите пункт меню повторно\n");
       }
   } 
 while (Q != 5);
 return 0;
}

