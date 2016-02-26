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

	//�������
	void getInf();
	void getInfSeq();
	char getName() { return name; }
	int getPower() { return power; }

	//�������
	void setName(char iName) { name = iName; }

	//������� �����
	void genSet();
	void inpSet();
	int fileSet();

	//������� ������ � ��������������������
	void concat(const HT&);
	void excl(const HT&);
	void erase(int start, int finish);
	//void erase(const HT&, int, int);

	//������ � ���-��������
	void addHT(int, int);
	LIST* findPos(int) const;
	LIST* findKey(int) const;
};
#endif