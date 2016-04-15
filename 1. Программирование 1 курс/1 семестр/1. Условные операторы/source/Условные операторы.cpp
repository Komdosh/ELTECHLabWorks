#include <stdio.h>
#include <locale.h>


int main()
{
	setlocale(LC_ALL, "RUS");
	int  X, Y, R;
	char Q;
	do
	{
		printf("Введите радиус\n");
		do
		{
			scanf("%d", &R);
			if (R <= 0)
				printf("Радиус должен быть положительным! Введите радиус повторно!\n");
		} 
		while (R <= 0);
		do
		{
			printf("Введите координаты точки X и Y через пробел\n");
			scanf("%d%d", &X, &Y);
			if (X*X+Y*Y>R*R)
				printf("Точка не принадлежит данным областям\n");
			else
				if (X * X + Y * Y == R * R)
					printf("Точка лежит на границе\n");
				else
					if ((X == 0) && (Y == 0))
						printf("Точка лежит на начале координат\n");
					else
						if (X * X + Y * Y < R * R)
						{
							if (((X == 0) && (Y > 0)) || ((X > 0) && (Y == 0)))
								printf("Точка лежит на границе\n");
							else
								if (X >= 0)
								{
									if ((Y > 0) && (Y == X) || (Y < 0) && (Y < -X) && (X != 0))
										printf("Точка принадлежит данным областям\n");
									else
										if (Y > -X && Y != X)
											printf("Точка не принадлежит данным областям\n");
											else
												printf("Точка лежит на границе\n");
								}
								else
									if ((Y < -X) && (Y > X) && (Y != 0))
										printf("Точка принадлежит данным областям\n");
									else
										if ((Y < X) || (Y > -X))
											printf("Точка не принадлежит данным областям\n");
										else
											if (((Y == X) || (Y == -X) || (Y == 0)))
												printf("Точка лежит на границе\n");
											else
												printf("Точка не принадлежит данным областям\n");
						}
			printf("Проверить другую точку при заданном радиусе? Для повтора введите 'Y'\n");
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

