#include "lists.h"

int main()
{
	list<int> liste1;

	liste1.pushSLL(0, 0);
	liste1.pushSLL(1, 0);
	liste1.pushSLL(2, 0);
	liste1.pushSLL(3, 0);
	liste1.pushSLL(4, 0);
	liste1.pushSLL(5, 0);

	list<int> liste2;
	//liste2.pushSLL(1, 0);
	//liste2.pushSLL(2, 0);
	//liste2.pushSLL(3, 0);
	//liste2.pushSLL(4, 0);

	//liste1.merge(liste2);

	liste1.divide(liste1, liste2, 3);

	liste1.view();
	liste2.view();


	//liste.view();
	//cout << liste.countSLL() << endl;

	//liste.popSLL(1);


	//liste.insert(9, 1);
	//liste.view();
	//cout << liste.countSLL() << endl;

	//liste.eraseSLL(1);
	//liste.view();
	//cout << liste.countSLL() << endl;

	//liste.eraseSLL(2);
	//liste.view();
	//cout << liste.countSLL() << endl;

	//cout << liste.beginSLL() << endl;
}