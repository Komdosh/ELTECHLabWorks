#pragma once
#include <iostream>
#include <string>
#include "screen.h"
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
 return (0 <= a && a < XMAX && 0 <= b && b < YMAX);
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
	for (int y = YMAX-1; 0<=y; --y) {
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
	point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point east() const { return e; }
	point west() const { return w; }
	point neast() const { return e; }
	point seast() const { return e; }
	point nwest() const { return w; }
	point swest() const { return w; }
	void move(int a, int b) { w.x += a; w.y += b;e.x += a; e.y += b; }

	void draw() { 
		put_line(w, e);
	}

	line(point a, point b) :w(a), e(b) {
	}

	line(point a, int l) :w(a), e(point(a.x + l - 1, a.y)) {
	}
};

//Прямоугольник
class rectangle:public rotatble {
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
};

rectangle::rectangle(point a, point b)
{
	if(a.x<=b.x)
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
	point nw(sw.x, ne.y);
	point se(ne.x, sw.y);
	put_line(nw, ne);
	put_line(ne, se);
	put_line(se, sw);
	put_line(sw, nw);
}

//Треугольник
class Triangle:public rotatble, public reflectable {
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
	point neast() const { return point(se.x, n.y);}
	point seast() const { return se; }
	point nwest() const { return point(sw.x, n.y);}
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

	void move(int a, int b){
		sw.x += a;
		sw.y += b;
		se.x += a;
		se.y += b;
		n.x += a;
		n.y += b;
	}

	void draw();
};

Triangle::Triangle(point lft, point rgt, point up)
{
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
	put_line(curBaseOne, curBaseTwo);
	put_line(curBaseOne, curTop);
	put_line(curBaseTwo, curTop);
}

void shape_refresh()//Перерисовка всех фигур
{
	screen_clear();
	for (shape* p = shape::list; p; p = p->next) p->draw();
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
