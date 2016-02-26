#ifndef CLASSES_H
#define CLASSES_H
#include <string>



class HT
{
	enum { hPower = 8, arrPower = 16 };
	struct LIST {
		int num;
		LIST* next;
		~LIST() { if (next) delete next; }
	};
	LIST* hashTable[hPower] = { nullptr };
	char name;
	int power;

	int hashFunc(int x)
	{
		int p = 7, q = 3;
		return (p*x + q) % 8;
	}

	public:
		
		HT(char iName = 'T'):name(iName), power(0) {}

		HT& operator | (const HT &) const;
		HT& operator & (const HT &) const;
		HT& operator = (const HT &);

		//геттеры
		void getInf();
		char getName() { return name; }
		int getPower() { return power; }

		//сеттеры
		void setName(char iName) { name = iName; }

		//функции ввода
		void genSet();
		void inpSet();
		int fileSet();

		//Работа с хеш-таблицей
		void addHT(int);
};
#endif