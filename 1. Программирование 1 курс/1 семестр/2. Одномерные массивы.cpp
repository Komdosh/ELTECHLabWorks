#include<stdio.h>
#include<locale.h>

int main()
 {
 	setlocale(LC_ALL, "RUS");
 	const int n=30;
	int mas[n],i, j, size, buffer, f;
	char Q;
	do
	 {
		printf("Введите кол-во элементов массива (целые положительные числа от 1 до %d)\n",n);
		do
		 {
			scanf("%d", &size);
			if (size < 1 || size > n)
				printf("Кол-во элементов, целые положительные числа, от 1 до %d! Введите кол-во повторно!\n",n);
		 } 
 	  while (size < 1||size > n);
		do
		 {
			printf("Введите элементы массива через пробел\n");
			for (i = 0; i < size; scanf("%d", &mas[i]), i++);
			for (f= i = 0; i < size && f==0 ; f=(mas[i]<0)?1:0, i++);
			printf("Контрольный вывод элементов массива\n");
			for (i = 0; i < size; printf("%d ", mas[i]), i++);
			  for (i = 0; i < size; i++)
			  	for (j = i + 1; j < size ; j++)
			  		if (mas[i] < mas[j])
				  		{
 				        buffer = mas[i];
				  		  mas[i] = mas[j];
				  		  mas[j] = buffer;
			  			}			
			printf("\nВывод элементов массива по убыванию\n");
			for (i = 0; i < size; printf("%d ", mas[i]), i++);
			if (f!=0)
			  printf("\nВ массиве присутствует отрицательный элемент");
			else
			  printf("\nВ массиве отсутствует отрицательный элемент");
			printf("\nПовторить ввод чисел в массив при заданном кол-ве(%d)? Для повтора введите 'Y'\n", size);
			fflush(stdin);
			scanf("%c", &Q);
		 } 
		while (Q == 'Y' || Q == 'y');
		printf("Повторить программу заново? Для повтора введите 'Y'\n");
		fflush(stdin);
		scanf("%c", &Q);
   } 
  while (Q == 'Y' || Q == 'y');
	return 0;
 }
