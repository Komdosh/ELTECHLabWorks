#ifndef CLASSES_H
#define CLASSES_H
enum genSettings { genPower = 30, genMaxNum = 99 };
class NODE {	//Узел дерева
private:
	void display(int, int);
	void out(int, int);
	int key;		    //Ключ
	NODE *next, *down;
	void erase();
	friend class TREE23;
public:
	NODE() : down(nullptr), next(nullptr) {}
	NODE(int k) : key(k), down(nullptr), next(nullptr) {}
	int getKey() { return key; }
	//	~Node( ) { if(down) delete down; 
	//			if(next) delete next; };
};

class EL {	//Элементы стека
	NODE* el;
	int ctl;
	EL* prev;
	friend class STACK;
public:
	EL(NODE *e, int c) : el(e), ctl(c), prev(nullptr) {}
};

class STACK { //Класс "стек"
	EL * ptr; 
public:
	STACK() : ptr(nullptr) {}
	STACK(NODE * pp, int ct) { ptr = new EL(pp, ct); };
	~STACK();
	NODE* top() { return ptr->el; }
	void push(NODE *, int);
	int pop(NODE *&, int &);
};

class TREE23 {	//Класс 2-3-дерева
	NODE* root;
	int height;
	char name;
public:
	const TREE23& operator | (const TREE23 &) const;
	const TREE23& operator & (const TREE23 &) const;
	const TREE23& operator = (const TREE23 &);

	bool find(int num) const;
	int insert(int);   //Вставка элемента
	void display();    //Вывод на экран
	int build(int);    //Построение дерева
	int step(NODE *&, STACK&) const; //Шаг обхода
	void genSet();     //Генерация данных
	TREE23(char n = 'T') : root(nullptr), height(0), name(n) {}
	~TREE23();
};
#endif