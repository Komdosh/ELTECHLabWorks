//�� ������ ����� ���������������� ���������: (C)lgn, 16.05.05;25.02.14

#include <iostream>
#include <locale>
#include <stdio.h>
#include <conio.h>
#include "Classes.h"

using std::cin;
using std::cout;
using std::endl;

//***********************************************************************
//���������� ������� �����
STACK::~STACK()
{
	EL* s;
	while (ptr) {
		s = ptr;
		ptr = ptr->prev;
		delete s;
	}
}
//-----------------------------------------------------------------------
void STACK::push(NODE * pp, int ct) //��������
{
	EL* s = new EL(pp, ct);
	s->prev = ptr;
	ptr = s;
}
//-----------------------------------------------------------------------
int STACK::pop(NODE * & pp, int & ct) //����������
{
	EL* s = ptr;
	pp = ptr->el;
	ct = ptr->ctl;
	ptr = ptr->prev;
	delete s;
	return (ptr != nullptr);
}
//***********************************************************************
void NODE::erase() //�������� ����
{
	if (down) {
		if (next->next) next->next->down->erase();
		next->down->erase();
		down->erase();
	}
	else {
		if (next) {
			if (next->next) delete next->next;
			delete next;
		}
		delete this;
	}
}
//-----------------------------------------------------------------------
TREE23 :: ~TREE23()
{
	if (root) root->erase();
}
//***********************************************************************
//��������� ������ �� �����
const int FIRSTROW = 0, FIRSTCOL = 40,
MAXCOL = 80, OFFSET[] = { 40, 24, 10, 4, 1 },
MAXROW = FIRSTROW + 18,
MAXOUT = FIRSTROW + 14, SHIFT = 2;
char SCREEN[MAXROW * MAXCOL];
int row = 0, col = 0;
//***********************************************************************
//������� ������ � �������
void gotoxy(int c, int r) { row = r, col = c; }
//-----------------------------------------------------------------------
void clrscr()
{
	for (auto &x : SCREEN) x = ' ';
}
//-----------------------------------------------------------------------
void showscr()
{
	for (int i = 0; i<MAXROW; i++)
		for (int j = 0; j < MAXCOL; j++)
			if (SCREEN[i * MAXCOL + j] && SCREEN[i * MAXCOL + j] != '�') 
				cout << SCREEN[i * MAXCOL + j];
			else cout << ' ';
	cout << endl;
}
//***********************************************************************
//����� ���� � ������ screen � ����� (x, y)
void NODE::out(int row, int col)
{
	if ((row > MAXROW) || (col < 1) || (col > MAXCOL)) return;
	gotoxy(col, row);
	if (row > MAXOUT) {
		sprintf_s(SCREEN + row*MAXCOL + col, 4, "..."), col += 3;
		return;
	}
	sprintf_s(SCREEN + row*MAXCOL + col, 4, "%1d ", key);
	if (next) {
		sprintf_s(SCREEN + (row + 1)*MAXCOL + col + 1, 4, "%1d ", next->key);
		if (next->next)
			sprintf_s(SCREEN + (row + 2)*MAXCOL + col + 2, 4, "%1d ", next->next->key);
		//else sprintf_s(SCREEN + (row + 2)*MAXCOL + col + 2, 4, "@  ");
	}
}
//-----------------------------------------------------------------------
//����� ������ �� �����
void TREE23::display()
{
	clrscr();
	gotoxy(FIRSTCOL - OFFSET[0], FIRSTROW);
	col += sprintf_s(SCREEN + row*MAXCOL + col, 11, "������ %c:", name);
	if (root) root->display(0, FIRSTCOL - SHIFT);
	else sprintf_s(SCREEN + row*MAXCOL + col, 9, "<�����!>");
	showscr();
}
//-----------------------------------------------------------------------
//����� ���� �� ����� � �����
void NODE::display(int lvl, int col)
{
	int row = FIRSTROW + lvl * 4;
	this->out(row, col);
	if (down) {
		down->display(lvl + 1, col - (OFFSET[lvl + 1]));
		next->down->display(lvl + 1, col);
		if ((next->next) && (next->next->down))
			next->next->down->display(lvl + 1, col + (OFFSET[lvl + 1]));
	}
}
//***********************************************************************
//������� � 2-3 ������
int TREE23::insert(int k)
{
	NODE *t, *p, *q;
	int a = 1, up = 0;

	//===== ������������� =====
	t = root;
	if (t == nullptr) {	// ������ �����
		root = new NODE(k);
		height = 1;
		return 2;
	}
	else {		//����� �� ������
		STACK * St = new STACK(t, 1);	// �������� � ������������� �����
										//===== ����� ����� ������� =====
		while (a) {
			if ((k == t->key) || //�������� �� ���������� ��������
				(t->next) && (k == t->next->key) ||
				(t->next) && (t->next->next) && (k == t->next->next->key)) { //������� �������
				delete St; 	//����������� �����
				return 1;		//����� "������� �� ������������"
			}
			if (k < t->key) {
				if (t->down) { //��� ���� � �����
					p = t->next->next;
					t = t->down;
					if (p) St->push(t, 4);
					else St->push(t, 2);
				}
				else { //����� ���� ����� (������� ������ � ������� ������)
					p = new NODE(t->key);
					p->next = t->next;
					t->key = k;
					if ((t->next) && (t->next->next)) up = 1; //�������� ��������
					t->next = p;
					a = 0;
				}
			}
			else if (!(t->next)) { //���������� ������� ��������
				p = new NODE(k);
				t->next = p;
				a = 0;
			}
			else if (k < t->next->key) {
				if (t->next->down) {//��� ���� ����������
					p = t->next->next;
					t = t->next->down;
					if (p) St->push(t, 5);
					else St->push(t, 3);
				}
				else { // ����� ���� ����������
					p = new NODE(k);
					p->next = t->next;
					if (t->next->next) up = 1; //�������� ��������
					t->next = p;
					a = 0;
				}
			}
			else if (!t->next->next) { //�������� ���� ���;
				if (t->next->down) {     //��� ���� ����������
					t->next->key = k; 	//������ ����������
					t = t->next->down;
					St->push(t, 3);
				}
				else {                   // ����� ���� ������
					p = new NODE(k);
					t->next->next = p;
					a = 0;
				}
			}
			else {
				if (t->next->next->down) { //��� ���� � ������
					if (k > t->next->next->key)
						t->next->next->key = k; //������ ����������
					t = t->next->next->down;
					St->push(t, 6);
				}
				else {                     //����� ����
					p = new NODE(k);
					a = 0;
					if (t->next->next) {    //������ ��� ����...
						up = 1;
						if (k < t->next->next->key) { // - ������ �� ������
							p->next = t->next->next;
							t->next->next = p;
						}
						else {                  // - ��������
							t->next->next->next = p;
						}
					}
					else { //����� ���� - ������ �� ���
						t->next->next = p;
						//	           St->Top( )->key = k;
					}
				}
			}
		}
		while (up) { //���������� ��������� ���� (���� �� ����)
			St->pop(p, a);	//p-> ���� � �������� ���������
			if (a != 1) t = St->top();	//t-> ����������� ���� ��� "p->"
			q = new NODE(p->next->next->next->key);
			switch (a) {
			case 1:	//�������� ���� ������: root == p == t
				up = 0;
				height++;	//���������� ������ ������
				root = t = new NODE(root->next->key); //�������� �������� ������������ ����
				t->down = p;
				t->next = q;
				break;
			case 2:	//����� ������� ��� ��� ����
				up = 0;
			case 4:     //����� ������� ��� ���
				q->next = t->next; //������� � �������
				t->next = q;
				t->key = p->next->key;	//��������� ���������� ��������
				break;
			case 3:	//����� ������ ��� ��� ����
				up = 0;
			case 5:     //����� ������ ��� ���
				q->next = t->next->next;
				t->next->next = q;		//������������� � �������
				t->next->key = p->next->key;	//��������� ���������� ��������
				break;
			case 6:	//����� �������� ���
				t->next->next->next = q;		//������������� � �������
				t->next->next->key = p->next->key;	//��������� ���������� ��������
				break;
			}
			q->down = p->next->next;
			p->next->next = nullptr; //����������� �������
		}
		delete St; 	//����������� �����
		return 2;
	}
};
//***********************************************************************
//�������� 2-3 ������ �� ������������ ������������������
int TREE23::build(int k)	// ���� ������������ ������������������
{
	NODE *q;				// � �������������� � � 2-3-������
	static NODE *p;
	static int count = 0;

	if (k) { //���������� � �������
		q = new NODE(k);
		if (root == nullptr) { //������ ���������
			root = p = q;
			count = 1;
		}
		else {
			p->next = q;
			p = q;
			count++;
		}
	}
	else if (count) { //���� �������, ������ ������
		int rest = count;
		height = 1;
		while (rest > 3) {
			q = root;
			height++;
			if (rest == 4) { //��� ����������� ����
				root = new NODE(q->next->key);
				p = new NODE(q->next->next->next->key);
				root->next = p;
				root->down = q;
				p->down = q->next->next;
				q->next->next = nullptr;
				rest = 0;
			}
			else { //������� ����������� �����
				int last = rest - 3;
				root = p = new NODE(q->next->next->key);
				p->down = q;
				q = q->next->next->next;
				p->down->next->next->next = nullptr;
				rest = 1;
				while (last) {
					rest++;
					switch (last) {
					case 2:
						p->next = new NODE(q->next->key);
						p->next->down = q;
						last = 0;
						break;
					case 3:
						p->next = new NODE(q->next->next->key);
						p->next->down = q;
						last = 0;
						break;
					case 4:
						p->next = new NODE(q->next->key);
						p->next->down = q;
						p->next->next = new NODE(q->next->next->next->key);
						p->next->next->down = q->next->next;
						q->next->next = nullptr;
						last = 0;
						rest++;
						break;
					default:
						p->next = new NODE(q->next->next->key);
						p->next->down = q;
						q = q->next->next->next;
						p = p->next;
						p->down->next->next->next = nullptr;
						last -= 3;
						break;
					}
				}
			}
		}
	}
	return count;
}
//***********************************************************************
//����� 2-3 ������
STACK globalStack;	//������� ���� ��� ������� step
int TREE23::step(NODE *& p, STACK& stack=globalStack) const
{
	int a;
	if (!p) { //������ ���������
		if (!root) return 0; //������ �����, �����
		p = root;	//����� �������� ������ ��������
		stack.push(p, 1);
		while (p->down) {
			stack.push(p, 2);
			p = p->down;
		}
		return 1;
	}
	else { //������� ��� �����
		if (p->next) { //���� ���� ������, ��� ������
			p = p->next;
			return 1;
		}
		while (true) {	//����� ���������� �����
			stack.pop(p, a);	//��� �����
			switch (a) {
			case 1:
				return 0;	//��������� � �����, �����
			case 2:
				stack.push(p, 3);	//����� �� ������� �����
				p = p->next->down;
				while (p->down) {
					stack.push(p, 2);
					p = p->down;
				}
				return 1;
			case 3:
				if (p->next->next) {
					stack.push(p, 4);	//����� �� ������ (���� ����)
					p = p->next->next->down;
					while (p->down) {
						stack.push(p, 2);
						p = p->down;
					}
					return 1;
				}
			case 4:;	//������ �� ���������, ������
			}
		}
	}
}
//***********************************************************************
//��������� 2-3 ������
void TREE23::genSet()
{
	int power = (rand() % genPower);
	while (power--)
		insert(rand()%genMaxNum +1);
}
//***********************************************************************
//����� �� ����� � 2-3 ������
bool TREE23::find(int num) const
{
	NODE* t=root;
	while (t) {
		if (num == t->getKey())
			return true;
		if (num > t->getKey() && t->next)
			t = t->next;
		else
			t = t->down;
	}
	return false;
}
//***********************************************************************
//���������� ���������� 2-3 ������
const TREE23& TREE23::operator &(const TREE23& rightExp) const
{
	TREE23 *temp = new TREE23;
	STACK stackL, stackR;
	int checkL, checkR;
	bool t = false;
	NODE *curL = nullptr, *curR = nullptr;
	checkR = rightExp.step(curR, stackR);
	checkL = step(curL, stackL);
	while (checkL && checkR) {
		while (curL->getKey() < curR->getKey() && checkL)
			checkL = step(curL, stackL);
		while (curR->getKey() < curL->getKey() && checkR)
			checkR = rightExp.step(curR, stackR);
		if (curR->getKey() == curL->getKey()) {
			temp->build(curR->getKey());
			if (!t) t = true;
			checkL = step(curL, stackL);
			checkR = rightExp.step(curR, stackR);
		}
	}
	if (t)
		temp->build(0);
	return *temp;
}
//----------------------------------------------------------------------
const TREE23& TREE23::operator | (const TREE23 & rightExp) const
{
	TREE23 *temp = new TREE23;
	STACK stackL, stackR;
	int checkL, checkR;
	bool t = false;
	NODE *curL = nullptr, *curR = nullptr;
	checkR = rightExp.step(curR, stackR);
	checkL = step(curL, stackL);
	while (checkL || checkR) {
		if (!t) t = true;
		if(checkL && checkR)
			if (curR->getKey() == curL->getKey()) {
				temp->build(curR->getKey());
				checkL = step(curL, stackL);
				checkR = rightExp.step(curR, stackR);
			}
			else {
				while (curL->getKey() < curR->getKey() && checkL) {
					temp->build(curL->getKey());
					checkL = step(curL, stackL);
				}
				while (curR->getKey() < curL->getKey() && checkR) {
					temp->build(curR->getKey());
					checkR = rightExp.step(curR, stackR);
				}
			}
		else
			if(checkL)
				while (checkL) {
					temp->build(curL->getKey());
					checkL = step(curL, stackL);
				}
			else
				while (checkR) {
					temp->build(curR->getKey());
					checkR = step(curR, stackR);
				}

	}
	if (t)
		temp->build(0);
	return *temp;
}
//----------------------------------------------------------------------
const TREE23& TREE23::operator = (const TREE23& rightExp)
{
	NODE *cur = nullptr;
	if (rightExp.root) {
		while (rightExp.step(cur))
			build(cur->getKey());
		build(0);
	}
	return *this;
}
//***********************************************************************
//������� ����
int menu()
{
	int point;
	do {
		cin.clear();
		cin.sync();
		cout << "�������� ����� ����" << endl;
		cout << "1 - ������������� ������" << endl;
		cout << "0 - �����" << endl;
		cout << ">";
		cin >> point;
		if (cin.fail())
			cout << "���-�� ����� �� ���, �������� ����� ���� ��������" << endl;
	} while (cin.fail());
	return point;
}
//***********************************************************************
//������� �������
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	int pause;
	do
	{
		TREE23 A('A'), B('B'), C('C'), D('D'), E('E');
		switch (pause = menu())
		{
		case 1:
			A.genSet(); B.genSet(); C.genSet(); D.genSet();
			//cout << "��������������� ���������" << endl;
			break;
		case 0:
			cout << "�� ����� ������!" << endl;
			break;
		default:
			cout << "������ ������ �� ����������, ��������� ����!" << endl;
		}
		if (pause==1)
		{
			system("cls");
			A.display();
			B.display();
			C.display();
			D.display();
			cout << "��������� E = A&B|C&D" << endl;
			E = A&B|C&D;
			E.display();
			cout << "��� �������� � ���� ������� ����� �����, ��� ������ 0: ";
			cin >> pause;
		}
	} while (pause);
	return 0;
}
