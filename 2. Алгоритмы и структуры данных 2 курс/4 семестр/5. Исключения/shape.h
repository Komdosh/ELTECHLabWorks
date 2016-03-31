#pragma once
#include <iostream>
#include <string>
#include "screen.h"

using std::cout;
using std::endl;
//Базовый класс фигур
struct shape {
	static shape* list;
	shape* next;
	shape() { next = list; list = this; }
	virtual point north() const = 0;
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual void draw() = 0;
	virtual void move(int, int) = 0;

	class onScrException
	{
		point p;
	public:
		onScrException(point p0) : p(p0) {};
		void showPoint() {
			std::cout << '(' << p.x << ", " << p.y << ')';
		}
	};
	~shape(){
		if (shape::list) {
			shape* temp = shape::list;
			shape* tempOne;
			if (temp == this)
				shape::list = shape::list->next;
			else
				while (temp->next) {
					if (this == temp->next) {
						tempOne = temp;
						temp = temp->next;
						tempOne->next = tempOne->next->next;
					}
					else
						temp = temp->next;
				}
			temp->next = nullptr;
			//if (temp)
			//	delete temp;
		}
	}
private:
	shape(const shape&);
	shape(const shape&&);
};

//--------------------------------------------------------------------
//Работа с экраном

char screen[XMAX][YMAX];

enum color { black = '*', white = ' ' };

void screen_init()
{
	for (int y = 0; y < YMAX; ++y)
		for (int x = 0; x < XMAX; ++x)
			screen[x][y] = white;
}

inline int on_screen(int a, int b) //Попадание на экран
{
	return (0 <= a && a < XMAX && 0 <= b && b < YMAX) ? 1 : throw shape::onScrException(point(a, b));
}

void put_point(int a, int b)
{
	if (on_screen(a, b)) screen[a][b] = black;
}

void put_line(int x0, int y0, int x1, int y1)
{
	/*
	Рисование отрезка прямой (x0, y0) - (x1, y1)
	Уравнение прямой: b(x-x0) + a(y-y0) = 0
	Минимизируется величина abs(eps)
	где eps = 2*(b(x-x0))+a(y-y0)
	*/
	int dx = 1;
	int a = x1 - x0;
	if (a < 0) dx = -1, a = -a;
	int dy = 1;
	int b = y1 - y0;
	if (b < 0) dy = -1, b = -b;
	int two_a = 2 * a;
	int two_b = 2 * b;
	int xcrit = -b + two_a;
	register int eps = 0;

	while (1) {
		put_point(x0, y0);
		if (x0 == x1 && y0 == y1) break;
		if (eps <= xcrit) x0 += dx, eps += two_b;
		if (eps >= a || a < b)y0 += dy, eps -= two_a;
	}
}

void screen_clear() { screen_init(); }

void screen_refresh()
{
	for (int y = YMAX - 1; 0 <= y; --y) {
		for (int x = 0; x < XMAX; ++x)
			std::cout << screen[x][y];
		//std::cout << '\n';
	}
}


shape* shape::list = nullptr; //Иницализация списка фигур

class rotatble : public virtual shape { //Фигуры, пригодные к повороту
public:
	virtual void rotate_left() = 0;
	virtual void rotate_right() = 0;
};

class reflectable : public virtual shape {//Фигуры пригодные к зеркальному отражению
public:
	virtual void flip_horisontally() = 0;
	virtual void flip_vertically() = 0;
};

class line : public shape {
	/*
	Отрезок прямой ["w", "e"]
	north() определяет точку "выше центра отрезка и так далеко на север,
	как самая его северная точка", и т.п.
	*/
	point w, e;
	line(const line&);
	line(const line&&);
public:
	/*Как было
	point north() const { return point((w.x + e.x) / 2, e.y<w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y<w.y ? e.y : w.y); }
	point east() const { return point((w.x + e.x) / 2, e.y<w.y ? e.y : w.y); }
	point west() const { return point((w.x + e.x) / 2, e.y<w.y ? e.y : w.y); }
	point neast() const { return point((w.x + e.x) / 2, e.y<w.y ? e.y : w.y); }
	point seast() const { return point((w.x + e.x) / 2, e.y<w.y ? e.y : w.y); }
	point nwest() const { return point((w.x + e.x) / 2, e.y<w.y ? e.y : w.y); }
	point swest() const { return point((w.x + e.x) / 2, e.y<w.y ? e.y : w.y); }
	*/
	/*Исправление предыдущего кода
	point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point east() const { return point(e.x, (w.y + e.y) / 2); }
	point west() const { return point(w.x, (w.y + e.y) / 2); }
	point neast() const { return point(e.x, e.y < w.y ? w.y : e.y); }
	point seast() const { return point(e.x, e.y < w.y ? e.y : w.y); }
	point nwest() const { return point(w.x, e.y < w.y ? w.y : e.y); }
	point swest() const { return point(w.x, e.y < w.y ? e.y : w.y); }
	*/
	//Более рациональное исправление
	point north() const { return point((w.x + e.x) / 2, (w.y + e.y) / 2); }
	point south() const { return point((w.x + e.x) / 2, (w.y + e.y) / 2); }
	point east() const { return e; }
	point west() const { return w; }
	point neast() const { return e; }
	point seast() const { return e; }
	point nwest() const { return w; }
	point swest() const { return w; }
	void move(int a, int b) { w.x += a; w.y += b;e.x += a; e.y += b; }

	void draw() {
		if (w.x < 0 || w.y < 0 || e.x < 0 || e.y < 0 || w.x > XMAX || w.y > YMAX || e.x > XMAX || e.y > YMAX) {
			throw Exception(w, e,
				"в функции-члене draw класса line\nНехватка места на экране");
		}
		put_line(w, e);
	}

	line(point a, point b) :w(a), e(b) {
		if (a.x < 0 || a.y < 0 || b.x < 0 || b.y < 0){
			throw Exception(a, b,
				"в конструкторе line\nНекорректные параметры");
		}
	}

	line(point a, int l) :w(a), e(point(a.x + l - 1, a.y)) {
		if (a.x < 0 || a.y < 0 || a.x + l < 0){
			point b;
			b.x = a.x + l;
			b.y = a.y;
			throw Exception(a, b,
				"в конструкторе line\nНекорректные параметры");
		}
	}
	class Exception
	{
		point a;
		point b;
		std::string w;
	public:
		Exception(point p0, point p1, std::string str) : a(p0), b(p1), w(str) {}
		std::string what() { return w; }

		void showPoints() {
			std::cout << '(' << a.x << ", " << a.y << ") ";
			std::cout << '(' << b.x << ", " << b.y << ") ";
		}
	};
};

//Прямоугольник
class rectangle :public rotatble {
	/*
	nw-----n-----ne
	|             |
	|             |
	w      c      e
	|             |
	|             |
	sw-----s-----se
	*/
	rectangle(const rectangle&);
	rectangle(const rectangle&&);
	point sw, ne;
public:
	point north() const { return point((sw.x + ne.x) / 2, ne.y); }
	point south() const { return point((sw.x + ne.x) / 2, sw.y); }
	point east() const { return point(ne.x, (sw.y + ne.y) / 2); }
	point west() const { return point(sw.x, (sw.y + ne.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return point(ne.x, sw.y); }
	point nwest() const { return point(sw.x, ne.y); }
	point swest() const { return sw; }
	void rotate_right()//Поворот относительно se
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		sw.x = ne.x - h * 2;
		ne.y = sw.y + w / 2;
	}
	void rotate_left() //Поворот относительно sw
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		ne.x = sw.x + h * 2;
		ne.y = sw.y + w / 2;
	}
	void move(int a, int b)
	{
		sw.x += a;
		sw.y += b;
		ne.x += a;
		ne.y += b;
	}
	void draw();
	rectangle(point, point);
	class Exception
	{
		point a;
		point b;
		std::string w;
	public:
		Exception(point p0, point p1, std::string str) : a(p0), b(p1), w(str) {};
		std::string what() { return w; }

		void showPoints() {
			std::cout << '(' << a.x << ", " << a.y << ") ";
			std::cout << '(' << b.x << ", " << b.y << ") ";
		}
	};
};

rectangle::rectangle(point a, point b)
{
	if (a.x < 0 || a.y < 0 || b.x < 0 || b.y < 0)
	{
		throw Exception(a, b,
			"в конструкторе rectangle\nНекорректные параметры");
	}
	if (a.x <= b.x)
		if (a.y <= b.y) {
			sw = a;
			ne = b;
		}
		else {
			sw = point(a.x, b.y);
			ne = point(b.x, a.y);
		}
	else
		if (a.y <= b.y) {
			sw = point(b.x, a.y);
			ne = point(a.x, b.y);
		}
		else {
			sw = b;
			ne = a;
		}
}
void rectangle::draw()
{
	if (sw.x < 0 || sw.y < 0 || ne.x < 0 || ne.y < 0 ||
		sw.x > XMAX || sw.y > YMAX || ne.x > XMAX || ne.y > YMAX) {
		throw Exception(sw, ne,"в функции-члене draw класса rectangle\nНехватка места на экране");
	}
	point nw(sw.x, ne.y);
	point se(ne.x, sw.y);
	put_line(nw, ne);
	put_line(ne, se);
	put_line(se, sw);
	put_line(sw, nw);
}

//Треугольник
class Triangle :public rotatble, public reflectable {
	/*
	nw    top   ne
		  / \
		 /   \
		/     \
	w  /   c   \  e
	  /         \
	 /           \
	sw-----s-----se
	*/
	Triangle(const Triangle&);
	Triangle(const Triangle&&);
	point n, sw, se;
	int pos;
public:
	Triangle(point, point, point);
	point north() const { return n; }
	point south() const { return point((sw.x + se.x) / 2, sw.y); }
	point east() const { return point(se.x, (se.y + n.y) / 2); }
	point west() const { return point(sw.x, (sw.y + n.y) / 2); }
	point neast() const { return point(se.x, n.y); }
	point seast() const { return se; }
	point nwest() const { return point(sw.x, n.y); }
	point swest() const { return sw; }

	void rotate_right()
	{
		pos = (pos + 1) % 4;
	}

	void rotate_left()
	{
		if (pos)
			pos -= 1;
		else
			pos = 3;
	}

	void flip_horisontally() {
		if (pos == 0)
			pos = 2;
		else
			if (pos == 2)
				pos = 0;
	}
	void flip_vertically() {
		if (pos == 1)
			pos = 3;
		else
			if (pos == 3)
				pos = 1;
	}

	void move(int a, int b) {
		sw.x += a;
		sw.y += b;
		se.x += a;
		se.y += b;
		n.x += a;
		n.y += b;
	}

	void draw();
	class Exception
	{
		point a;
		point b;
		point c;
		std::string w;
	public:
		Exception(point p0, point p1, point p2, std::string str) :
			a(p0), b(p1), c(p2), w(str) {};
		std::string what() { return w; }

		void showPoints() {
			std::cout << '(' << a.x << ", " << a.y << ") ";
			std::cout << '(' << b.x << ", " << b.y << ") ";
			std::cout << '(' << c.x << ", " << c.y << ')';
		}

	};
};

Triangle::Triangle(point lft, point rgt, point up)
{
	if (lft.x < 0 || lft.y < 0 || rgt.x < 0 || rgt.y < 0 || up.x < 0
		|| up.y < 0 || up.y < lft.y || up.y < rgt.y) {
		throw Exception(lft, rgt, up,
			"в конструкторе Triangle\nНекорректные параметры");
	}
	sw = lft;
	se = rgt;
	n = up;
	pos = 0;
}

void Triangle::draw()
{
	point curTop, curBaseOne, curBaseTwo; //Текущее положение
	switch (pos) {
	case 0:
		curBaseOne = sw;
		curBaseTwo = se;
		curTop = n;
		break;
	case 1:
		curBaseOne = nwest();
		curBaseTwo = sw;
		curTop = east();
		break;
	case 2:
		curBaseOne = nwest();
		curBaseTwo = neast();
		curTop = south();
		break;
	case 3:
		curBaseOne = neast();
		curBaseTwo = se;
		curTop = west();
		break;
	}
	if (curBaseOne.x < 0 || curBaseOne.y < 0 || curBaseTwo.x < 0 ||
		curBaseTwo.y < 0 || curTop.x < 0 || curTop.y < 0 ||
		curBaseOne.x > XMAX || curBaseOne.y > YMAX || curBaseTwo.x > XMAX
		|| curBaseTwo.y > YMAX || curTop.x > XMAX || curTop.y > YMAX) {
		throw Exception(curBaseOne, curBaseTwo, curTop,
			"в функции-члене draw класса Triangle\nНехватка места для отображения");
	}
	put_line(curBaseOne, curBaseTwo);
	put_line(curBaseOne, curTop);
	put_line(curBaseTwo, curTop);
}

void shape_refresh()//Перерисовка всех фигур
{
	screen_clear();
	for (shape* p = shape::list; p; p = p->next) 
	try { 
		p->draw(); 
	}
	catch (rectangle::Exception& e) {
		cout << "Сработало исключение " << e.what() << "\nЗначения точек:";
		e.showPoints();
		cout << "\nМы не виноваты что экран слишком маленький, этот прямоугольник придётся пропустить" << endl;
	}
	catch (Triangle::Exception& e) {
		cout << "Сработало исключение " << e.what() << "\nЗначения точек:";
		e.showPoints();
		cout << "\nМы не виноваты что экран слишком маленький, этот треугольник придётся пропустить" << endl;
	}
	catch (line::Exception& e) {
		cout << "Сработало исключение " << e.what() << "\nЗначения точек:";
		e.showPoints();
		cout << "\nМы не виноваты что экран слишком маленький, эту линию придётся пропустить" << endl;
	}
	catch (shape::onScrException& e) {
		cout << "Точка "; e.showPoint(); cout << " за пределами экрана";
	}
	screen_refresh();
}

void up(shape* p, const shape* q)//Поместить p над q
{
	point n = q->north();
	point s = p->south();
	p->move(n.x - s.x, n.y - s.y + 1);
}

void lftUp(shape* p, const shape* q)//Поместить p слева над q
{
	p->move(q->nwest().x - p->swest().x, q->nwest().y - p->swest().y + 1);
}

void rgtUp(shape* p, const shape* q)//Поместить p справа над q
{
	p->move(q->neast().x - p->seast().x, q->nwest().y - p->swest().y + 1);
}

void rgtDwn(shape* p, const shape* q)//Поместить p справа под q
{
	p->move(q->east().x - p->west().x, q->swest().y - p->nwest().y);
}

void lftDwn(shape* p, const shape* q)//Поместить p справа под q
{
	p->move(q->west().x - p->east().x, q->swest().y - p->nwest().y);
}