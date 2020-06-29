#include "lists.h"

int main()
{
	list<int> liste;

	liste.pushSLL(0, 0);
	liste.pushSLL(1, 0);
	liste.pushSLL(2, 0);
	liste.pushSLL(3, 0);
	liste.pushSLL(4, 0);
	liste.pushSLL(5, 0);

	liste.view();
	cout << liste.countSLL() << endl;

	liste.popSLL(1);


	liste.insert(9, 1);
	liste.view();
	cout << liste.countSLL() << endl;

	liste.eraseSLL(1);
	liste.view();
	cout << liste.countSLL() << endl;

	liste.eraseSLL(2);
	liste.view();
	cout << liste.countSLL() << endl;

	//cout << liste.beginSLL() << endl;
}