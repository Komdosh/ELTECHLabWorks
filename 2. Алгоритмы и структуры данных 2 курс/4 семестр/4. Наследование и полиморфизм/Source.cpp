#include <iostream>
#include "conio.h"
#include "time.h"
#include "shape.h"

using namespace std;

class Face : public rectangle {
	line* l_eye; //����� ����
	line* r_eye; //������ ����
	line* mouth; //���
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
	//������������ �����
	screen_init();
	rotatble* hat = new rectangle(point(0, 0), point(14, 5));
	shape* hatsBottom = new line(point(0, 15), 21);
	shape* face = new Face(point(15, 10), point(27, 18));
	//���������� ������������ �� ��� ������! 
	//����� ����� ���������, ������ ����� ���������, �������
	Triangle* lftHorn = new Triangle(point(30, 10), point(34, 10), point(32, 12)); 
	Triangle* rgtHorn = new Triangle(point(40, 10), point(44, 10), point(42, 12));
	Triangle* lftWh = new Triangle(point(30, 0), point(33, 0), point(32, 2));
	Triangle* rgtWh = new Triangle(point(40, 0), point(43, 0), point(42, 2));
	shape_refresh();
	system("pause");
	//���������� ����� � ��������
	lftWh->rotate_left();
	rgtWh->rotate_right();
	hat->rotate_right();
	shape_refresh();
	system("pause");
	//������������ ���������
	rgtWh->flip_vertically();
	rgtHorn->flip_horisontally();
	shape_refresh();
	system("pause");
	//�������
	rgtWh->flip_vertically();
	rgtHorn->flip_horisontally();
	shape_refresh();
	system("pause");
    //������ �����������
	//�����
	up(hatsBottom, face);
	up(hat, face);
	//����
	lftUp(lftHorn, hatsBottom);
	rgtUp(rgtHorn, hatsBottom);
	//�����������
	lftDwn(lftWh, face);
	rgtDwn(rgtWh, face);
	shape_refresh();
	system("pause");
	//����� ������� ��� ������
	hatsBottom->move(0, 6);
	up(hat, hatsBottom);
	lftUp(lftHorn, face);
	rgtUp(rgtHorn, face);
	shape_refresh();
	system("pause");
	//������� �����
	up(hatsBottom, face);
	up(hat, face);
	lftUp(lftHorn, hatsBottom);
	rgtUp(rgtHorn, hatsBottom);
	shape_refresh();
	system("pause");
	return 0;
}
