#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>

int Menu();												//Прототип функции меню
int f0(const char*);							//Прототип функции ввода размеров матрицы
int **f1(int, int);								//Прототип функции ввода матрицы mas1
void f2(int, int, int**);					//Прототип функции вывода матрицы
int **f3(int, int, int**, int*);	//Прототип функции формирования матрицы mas2
void fr(int**, int);							//Прототип функции освобождения памяти

int main(void)
	{
		setlocale(LC_ALL, "RUS");
		int **mas1 = NULL, **mas2 = NULL, rows, col, Q, check = 0, check_2 = 0, ncol = 0;
		const char* help_enter="Для начала введите матрицу, выбрав 1 пункт в меню!\n";
		do
			{	
				Q = Menu();													//Меню
				switch (Q)
					{
						case 1:													//Ввод матрицы
										system("cls");
										fr(mas1,rows);						//Освобождение памяти исходной матрицы, если есть
										fr(mas2,rows);						//Освобождение памяти сформированной матрицы, если есть
										rows=f0("строк");					//Ввод кол-ва строк
										col=f0("столбцов");				//Ввод кол-ва столбцов
										mas1=f1(rows, col);				//Ввод матрицы
										check=1;
										ncol=check_2=0;
										break;
						case 2:														//Вывод матрицы
										system("cls");
										if (check)
											{
												printf("Контрольный вывод элементов массива\n");
												f2(rows, col, mas1);		//Вывод исходной матрицы
											}
										else
											printf(help_enter);
										system("pause");
										break;
						case 3:													//Обработка матрицы 
										system("cls");
										check_2 = 1;
										if (check)
										 {
											 mas2 = f3(rows, col, mas1, &ncol);	//Обработка исходной матрицы 
											 if (ncol)
											 		printf("Результат сформирован\n");
											 else
													printf("Результат не может быть сформирован\n");
										 }
										else
											printf(help_enter);

										system("pause");
										break;
						case 4:													//Вывод сформированной матрицы
										system("cls");
										if (check != 1)
											printf(help_enter);
										else
										if (check_2 != 1)
											printf("Результат не сформирован\n");
										else
											if (ncol)
												{
													printf("Вывод сформированной матрицы:\n");
													f2(rows, ncol, mas2);		//Вывод сформированной матрицы
												}
											else
											  printf("Результат не может быть сформирован\n");
										system("pause");
										break;
						case 5:												//Выход
										system("cls");
										puts("До новых встреч.");
										puts("Если возникли вопросы или проблемы обращайтесь, пожалуйста, на электронную почту: ");
										puts("komdosh@gelezo2.ru");
										system("pause");
										break;
						default:
										printf("Что-то пошло не так, введите пункт меню повторно\n");
										system("pause");
					}
			} 
		while (Q != 5);
		fr(mas1,rows);
		fr(mas2,rows);
		return 0;
	}
//*****************************************************************************************
//Функция Меню
int Menu()
	{
		int Q;
		system("cls");
		puts("Главное меню");
		puts("1 - Ввод матрицы");
		puts("2 - Показать введённую матрицу");
		puts("3 - Обработка исходной матрицы ");
		puts("4 - Показать обработанную матрицу");
		puts("5 - Выход");
		printf("Введите номер пункта - ");
		scanf("%d", &Q);
		printf("\n");
		return Q;
	}
//*****************************************************************************************
//Функция ввода размеров матрицы
int f0(const char* str)
	{
		int num;
		printf("Введите кол-во %s массива (целые положительные числа)\n", str);
		do
			{
			scanf("%d", &num);
			if (num<=0)
				printf("Кол-во %s это целые положительные числа, Введите кол-во повторно!\n", str);
			}
		while (num<=0);
		return num;
	}
//*****************************************************************************************
//Функция ввода матрицы mas1
int **f1(int rows, int col)
	{
		int i, j, **mas;
		mas = (int**)malloc(rows*sizeof(int*));
		for (i = 0; i < rows; i++)
			{
				*(mas + i) = (int*)malloc(col*sizeof(int));
				printf("Введите элементы %d строки массива через пробел\n", i + 1);
				for (j = 0; j < col; scanf("%d", &mas[i][j]), j++);
			}
		return mas;
	}
//*****************************************************************************************
//Функция вывода матрицы
void f2(int rows, int col, int** mas)
	{
		for (int i = 0; i<rows; printf("\n"), i++)
		for (int j = 0; j<col; printf("%5d", mas[i][j]), j++);
	}
//*****************************************************************************************
//Функция формирования матрицы mas2
int **f3(int rows, int col, int** mas, int* ncol)
	{
		int i, j, f, g, **mas2 = NULL;
		mas2 = (int**)malloc(rows*sizeof(int*));
		for(i=0;i<rows;i++)
	 		 *(mas2 + i) = NULL;								 
		for (g = j = 0; j < col; j++)
			{
				for (i = 0, f = 1; i < rows - 1 && f == 1; i++)
					f = (mas[i][j] <= mas[i + 1][j]) ? 1 : 0;
				if (f)
					{
						for (i = 0; i < rows; i++)
							{
								if(!*(mas2+i))
									*(mas2 + i) = (int*)realloc(*(mas2 + i), (g+1)*sizeof(int));
								*(*(mas2 + i) + g) = *(*(mas + i) + j);
							}
							g++;
					}
			}
		*ncol = g;
		return mas2;
	}
//*****************************************************************************************
//Функция освобождения памяти
void fr(int** mas, int rows)
{
	if (mas!=NULL)
		{
			for(int i=0; i<rows; i++)
			free(*(mas+i));
			free(mas);
			mas=NULL;
		}
}	
