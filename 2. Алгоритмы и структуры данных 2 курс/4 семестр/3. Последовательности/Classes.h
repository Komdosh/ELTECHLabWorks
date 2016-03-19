#ifndef CLASSES_H
#define CLASSES_H

class HT
{
	enum { hPower = 8, arrPower = 16 };
	struct LIST {
		int key;
		int pos;
		LIST* next;
		//~LIST() { if (next) delete next; }
	};
	
	char name;
	int power;

	LIST* hashTable[hPower] = { nullptr };

	int hashFunc(int x) const
	{
		int p = 7, q = 3;
		return (p*x + q) % 8;
	}

public:
	
	HT(char iName = 'T') :name(iName), power(0) {}
	HT(const HT&);

	HT& operator | (const HT &) const;
	HT& operator & (const HT &) const;
	HT& operator = (const HT &);

	//геттеры
	void getInf();
	void getInfSeq();
	char getName() { return name; }
	int getPower() { return power; }

	//сеттеры
	void setName(char iName) { name = iName; }

	//функции ввода
	void genSet();
	void inpSet();
	int fileSet();

	//функции работы с последовательностями
	void concat(const HT&);
	void excl(const HT&);
	void erase(int start, int finish);
	//void erase(const HT&, int, int);

	//Работа с хеш-таблицей
	void addHT(int, int);
	LIST* findPos(int) const;
	LIST* findKey(int) const;
};
#endif