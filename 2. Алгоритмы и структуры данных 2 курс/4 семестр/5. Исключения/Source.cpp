#include <iostream>
#include "conio.h"
#include "time.h"
#include "shape.h"

using namespace std;

class Face : public rectangle {
	line* l_eye; //левый глаз
	line* r_eye; //правый глаз
	line* mouth; //рот
public:
	Face(point, point);
	void draw();
	void move(int, int);
};

Face::Face(point a, point b) : rectangle(a, b)
{
	int ll = neast().x - swest().x + 1;
	int hh = neast().y - swest().y + 1;
	l_eye = new line(point(swest().x + 2, swest().y + hh * 3 / 4), 2);
	r_eye = new line(point(swest().x + ll - 4, swest().y + hh * 3 / 4), 2);
	mouth = new line(point(swest().x + 2, swest().y + hh / 4), ll - 4);
}

void Face::draw()
{
	rectangle::draw();
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;
	put_point(point(a, b));
}

void Face::move(int a, int b)
{
	rectangle::move(a, b);
	l_eye->move(a, b);
	r_eye->move(a, b);
	mouth->move(a, b);
}

int main() {
	setlocale(LC_ALL, "RUS");
	screen_init();
	//Демонстрация исключений
	try {
		//put_point(-12, 3); //onScrException
		//shape* excFace = new Face(point(-15, 10), point(27, 18)); //констр. rect.
		//shape* excRectangle = new rectangle(point(150, 10), point(27, 18)); //draw rect.
		//shape* excLineOne = new line(point(15, 10), point(27, -18)); //констр. line
		//shape* excLineTwo = new line(point(15, 10), point(270, 18)); //draw line 
		//Triangle excTriangleOne(point(30, 0), point(33, 0), point(32, -2)); //констр. Tri.
		//Triangle excTriangleTwo(point(30, 0), point(330, 0), point(32, 2)); //draw Tri.
	}
	catch (rectangle::Exception& e) {
		cout << "Сработало исключение " << e.what() << ", Можно исправить\nЗначения точек:";
		e.showPoints();
		cout << "\nЧтож, не судьба, давайте удалим этот прямоугольник" << endl;
	}
	catch (Triangle::Exception& e) {
		cout << "Сработало исключение " << e.what() << "\nЗначения точек:";
		e.showPoints();
		cout << "\nЧтож, не судьба, давайте удалим этот треугольник" << endl;
	}
	catch (line::Exception& e) {
		cout << "Сработало исключение " << e.what() << "\nЗначения точек:";
		e.showPoints();
		cout << "\nЧтож, не судьба, давайте удалим эту линию" << endl;
	}
	catch (shape::onScrException& e) {
		cout << "Точка "; e.showPoint(); cout << " за пределами экрана";
	}
	//Инициализаия фигур
		rotatble* hat = new rectangle(point(0, 0), point(14, 5));
		shape* hatsBottom = new line(point(0, 15), 21);
		shape* face = new Face(point(15, 10), point(27, 18));
		//Построение треугольника по трём точкам! 
		//Левая точка основания, правая точка основания, вершина
		Triangle* lftHorn = new Triangle(point(30, 10), point(34, 10), point(32, 12));
		Triangle* rgtHorn = new Triangle(point(40, 10), point(44, 10), point(42, 12));
		Triangle* lftWh = new Triangle(point(30, 0), point(33, 0), point(32, 2));
		Triangle* rgtWh = new Triangle(point(40, 0), point(43, 0), point(42, 2));
		shape_refresh();
		system("pause");
		//Подготовка фигур к стыковке
		lftWh->rotate_left();
		rgtWh->rotate_right();
		hat->rotate_right();
		shape_refresh();
		system("pause");
		//Демонстрация отражений
		rgtWh->flip_vertically();
		rgtHorn->flip_horisontally();
		shape_refresh();
		system("pause");
		//Возврат
		rgtWh->flip_vertically();
		rgtHorn->flip_horisontally();
		shape_refresh();
		system("pause");
		//Сборка изображения
		//Шляпа
		up(hatsBottom, face);
		up(hat, face);
		//Рога
		lftUp(lftHorn, hatsBottom);
		rgtUp(rgtHorn, hatsBottom);
		//Баккенбарды
		lftDwn(lftWh, face);
		rgtDwn(rgtWh, face);
		shape_refresh();
		system("pause");
		//Пусть помашет нам шляпой
		hatsBottom->move(0, 6);
		up(hat, hatsBottom);
		lftUp(lftHorn, face);
		rgtUp(rgtHorn, face);
		shape_refresh();
		system("pause");
		//Возврат шляпы
		up(hatsBottom, face);
		up(hat, face);
		lftUp(lftHorn, hatsBottom);
		rgtUp(rgtHorn, hatsBottom);
		shape_refresh();
	system("pause");
	return 0;
}