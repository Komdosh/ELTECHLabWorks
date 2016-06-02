#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<iterator>
#include<time.h>

using namespace std;

class mySet {
public:
	set<int> values;
	vector<set<int>::iterator> pointers;
	char name;

	mySet(char n) :name(n) {}

	void gen(int n, int mod) {
		for (int i = 0; i < n; ++i)
			pointers.push_back(values.insert(rand()%(1+mod)).first);
	}

	void setOut() {
		cout <<"\n"<< name << " = {";
		for (auto it = values.cbegin(); it != values.cend(); ++it)
			cout << (*it) << ' ';
		cout << "\b}"<<endl;
	}

	void seqOut() {
		cout << "\n" << name << " = {";
		for (auto it = pointers.cbegin(); it != pointers.cend(); ++it)
			cout << (*(*it)) << ' ';
		cout << "\b}" << endl;
	}
};

int setAnd(mySet A, mySet B, mySet& C) {
	C.values.clear();
	C.pointers.clear();
	set_intersection<set<int>::const_iterator, set<int>::const_iterator, insert_iterator<set<int>>>
		(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	for (auto it = C.values.cbegin(); it != C.values.cend(); ++it)
		C.pointers.push_back(it);
	return C.pointers.size();
}

int setDif(mySet A, mySet B, mySet& C) {
	C.values.clear();
	C.pointers.clear();
	set_difference<set<int>::const_iterator, set<int>::const_iterator, insert_iterator<set<int>>>
		(A.values.cbegin(), A.values.cend(), B.values.cbegin(), B.values.cend(), inserter(C.values, C.values.begin()));
	for (auto it = C.values.cbegin(); it != C.values.cend(); ++it)
		C.pointers.push_back(it);
	return C.pointers.size();
}

int erase(mySet& A, int p, int q) {
	if (p > q || A.pointers.empty())
		return 0;
	if (q > A.pointers.size())
		q = A.pointers.size();
	mySet T('A');
	int i = 0;
	for (auto it = A.pointers.cbegin(); it != A.pointers.cend(); ++it, ++i)
		if (i < p || i > q)
			T.pointers.push_back(T.values.insert((*(*it))).first);
	swap(A, T);
	return A.pointers.size();
}

int subst(mySet& A, mySet B, int p) {
	mySet T('A');
	int i = 0;
	auto itA = A.pointers.cbegin();
	for (; itA != A.pointers.cend() && i < p; ++itA, ++i)
		T.pointers.push_back(T.values.insert((*(*itA))).first);
	for(auto it = B.pointers.cbegin(); it != B.pointers.cend(); ++it)
		T.pointers.push_back(T.values.insert((*(*it))).first);
	for (; itA != A.pointers.cend(); ++itA)
		T.pointers.push_back(T.values.insert((*(*itA))).first);
	swap(A, T);
	return A.pointers.size();
}

int change(mySet& A, mySet B, int p) {
	if (p >= A.pointers.size()) {
		for (auto it = B.pointers.cbegin(); it != B.pointers.cend(); ++it)
			A.pointers.push_back(A.values.insert((*(*it))).first);
	}
	else {
		auto itA = A.pointers.begin();
		auto itB = B.pointers.cbegin();
		int i = 0;

		while (i < p && itA!= A.pointers.end()) { ++itA; ++i; }

		for (; itA != A.pointers.end() && itB != B.pointers.cend(); ++itA, ++itB)
			*itA = A.values.insert(*(*itB)).first;
		/*for (; itB != B.pointers.end(); ++itB)
			A.pointers.push_back(A.values.insert((*(*itB))).first);*/
	}			
	return A.pointers.size();
}



int main() {
	srand(time(nullptr));
	mySet A('A'), B('B'), C('C');
	
	A.gen(10, 40);
	B.gen(12, 40);
	A.seqOut();
	B.seqOut();
	//setAnd(A, B, C);
	//setDif(A, B, C);
	//C.seqOut();
	//erase(A, 2, 5);
	//subst(A, B, 3);
	//change(A, B, 2);
	//A.seqOut();

	system("pause");
	return 0;
}