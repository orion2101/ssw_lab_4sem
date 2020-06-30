#include <iostream>
using namespace std;

template <typename T>
class list {
public:
	list();
	~list();

	//функции односвязного списка
	void pushSLL(T data, unsigned where);
	void popSLL(unsigned where);
	void insertSLL(T data, unsigned where);
	void eraseSLL(unsigned index);
	void viewSLL(); //вывод элементов списка
	void indexationSLL(); //реорганизация индексов
	list<T>* beginSLL();
	list<T>* endingSLL();
	unsigned countSLL(); //подсчёт размер списка
	void mergeSLL(list<T>& list);
	void divideSLL(list<T>& list1, list<T>& empty_list, T value); //list1 - список элементов для рвзбиения, список в котором будут находится элементы больше чем порогово значения
	//empty_list - пустой список, в котором будут рвсоложены элементы меньше чем порогозначения

	//функции двухсвязного списка
	void pushDLL(T data, unsigned where);
	void popDLL(unsigned where);
	void insertDLL(T data, unsigned where);
	void eraseDLL(unsigned index);
	void viewDLL();
	void indexationDLL();
	list<T>* beginDLL();
	list<T>* endingDLL();
	unsigned countDLL();
	void mergeDLL(list<T>& list);
	void divideDLL(list<T>& list1, list<T>& empty_list, T value);

private:

	template<typename T>
	class DLL { //духсвязанный список
	public:
		DLL* prevPtr;
		DLL* nxtPtr;
		T data;
		int index;

		DLL(T data = T(), DLL* prevPtr = nullptr, DLL* nxtPtr = nullptr, int index = 0)
		{
			this->prevPtr = prevPtr;
			this->nxtPtr = nxtPtr;
			this->data = data;
			this->index = index;
		}
	};
	DLL<T>* startDLL;
	DLL<T>* endDLL;
	unsigned sizeDLL;

	template<typename T>
	class SLL { //односвязанный список
	public:
		SLL* nxtPtr;
		T data;
		int index;

		SLL(T data = T(), SLL* nxtPtr = nullptr, int index = 0)
		{
			this->nxtPtr = nxtPtr;
			this->data = data;
			this->index = index;
		}
	};
	
	SLL<T>* startSLL;
	SLL<T>* endSLL;
	unsigned sizeSLL;
};

template<typename T>
list<T>::list()
{
	sizeSLL = 0;
	startSLL = nullptr;
	endSLL = nullptr;
	sizeDLL = 0;
	startDLL = nullptr;
	endDLL = nullptr;
}

template<typename T>
list<T>::~list()
{
}

template<typename T>
void list<T>::pushSLL(T data, unsigned where)
{
	if (where == 0) //добавление в конец
	{
		if (this->startSLL == nullptr)
		{
			this->startSLL = new SLL<T>(data);
		}
		else
		{
			SLL<T>* actual = this->startSLL;
			while (actual->nxtPtr != nullptr)
			{
				actual = actual->nxtPtr;
			}
			actual->nxtPtr = new SLL<T>(data);
			unsigned prevIndex = actual->index;
			actual = actual->nxtPtr;
			actual->index = ++(prevIndex);
			//indexation();
			this->endSLL = actual;
			
		}
	}
	else if (where == 1) //добавление в начало
	{
		if (sizeSLL < 1)
		{
			cout << "ERROR : Add at least one item at the begining" << endl;
		}
		else 
		{
			SLL<T>* prevStart = this->startSLL;
			SLL<T>* newStart = new SLL<T>(data);
			newStart->nxtPtr = prevStart;
			this->startSLL = newStart;
			indexationSLL();
			
		}
		
	}
	
	sizeSLL++;
}

template<typename T>
void list<T>::popSLL(unsigned where)
{
	if (this->startSLL == nullptr)
	{
		cout << "ERROR : Sorry but current list is empty" << endl;
	}
	else if (where == 0) //выталькивание с начала
	{
		SLL<T>* actual = this->startSLL;
		SLL<T>* newStart = actual->nxtPtr;
		this->startSLL = newStart;
		indexationSLL();
		sizeSLL--;
	}
	else if (where == 1) //выталькивание с конца
	{
		SLL<T>* actual = this->startSLL;
		while (actual->nxtPtr != this->endSLL)
		{
			actual = actual->nxtPtr;
		}
		actual->nxtPtr = nullptr;
		this->endSLL = actual;
		indexationSLL();
		sizeSLL--;
	}
}

template<typename T>
void list<T>::insertSLL(T data, unsigned where)
{
	SLL<T>* actual = this->startSLL;
	while (actual->nxtPtr != nullptr)
	{
		if (where == 0)
		{
			pushSLL(data, 1);
			break;
		}
		else
		{
			SLL<T>* nxtItem = actual->nxtPtr;
			if (where == nxtItem->index)
			{
				actual->nxtPtr = new SLL<T>(data);
				SLL<T>* newItem = actual->nxtPtr;
				newItem->nxtPtr = nxtItem;
				indexationSLL();
				break;
			}
		}
		actual = actual->nxtPtr;
	}
	sizeSLL++;
}

template<typename T>
void list<T>::eraseSLL(unsigned index)
{	
	if (index == 0) //если удалящийся элемент явлается началом списка
	{
		popSLL(0);
	}
	else if (index == (sizeSLL - 1))
	{
		popSLL(1);
	}
	else 
	{
		SLL<T>* actual = this->startSLL;
		SLL<T>* nxtItem = actual->nxtPtr;
		while (actual->nxtPtr != nullptr)
		{
			if (nxtItem->index == index)
			{
				actual->nxtPtr = nxtItem->nxtPtr;
				indexationSLL();
				sizeSLL--;
				break;
			}
			actual = actual->nxtPtr;
			nxtItem = actual->nxtPtr;
		}
	}
}

template<typename T>
void list<T>::viewSLL()
{
	SLL<T>* actual = this->startSLL;
	cout << actual->data << " ";
	while (actual->nxtPtr != nullptr)
	{
		actual = actual->nxtPtr;
		cout << actual->data << " ";
	}
	cout << endl;

	/*actual = this->start;
	cout << actual->index << " ";
	while (actual->nxtPtr != nullptr)
	{
		actual = actual->nxtPtr;
		cout << actual->index << " ";
	}
	cout << endl;*/
}

template<typename T>
void list<T>::indexationSLL()
{
	SLL<T>* actual = this->startSLL;
	actual->index = 0;
	unsigned index = actual->index;
	actual = actual->nxtPtr;
	while (actual->nxtPtr != nullptr)
	{
		actual->index = ++index;
		actual = actual->nxtPtr;
	}
	actual->index = ++index;
}

template<typename T>
list<T>* list<T>::beginSLL()
{
	return this->startSLL;
}

template<typename T>
list<T>* list<T>::endingSLL()
{
	return this->end;
}

template<typename T>
unsigned list<T>::countSLL()
{
	return this->sizeSLL;
}

template<typename T>
void list<T>::mergeSLL(list<T> &list)
{
	//проверка первого списка на упорядоченность
	SLL<T>* actual = this->startSLL;
	SLL<T>* nxt = actual->nxtPtr;
	T min = actual->data;
	while (actual->nxtPtr != nullptr)
	{
		min = actual->data;
		while (nxt->nxtPtr != nullptr)
		{
			if (nxt->data < min)
			{
				cout << "list1 is not ranged" << endl;
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}

	//проверка второго списка на упорядоченность
	actual = list.startSLL;
	nxt = actual->nxtPtr;
	min = actual->data;
	while (actual->nxtPtr != nullptr)
	{
		min = actual->data;
		while (nxt->nxtPtr != nullptr)
		{
			if (nxt->data < min)
			{
				cout << "list2 is not ranged" << endl;
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}

	//добавление элементов первого списка во второй
	nxt = list.startSLL;
	while (nxt->nxtPtr != nullptr)
	{
		pushSLL(nxt->data, 0);
		nxt = nxt->nxtPtr;
	}
	pushSLL(nxt->data, 0);

	//упорядочивание
	actual = this->startSLL;
	nxt = actual->nxtPtr;
	T data = T();
	while (actual->nxtPtr != nullptr)
	{
		min = actual->data;
		nxt = actual->nxtPtr;
		while (nxt->nxtPtr != nullptr)
		{
			if (nxt->data <= min)
			{
				data = nxt->data;
				eraseSLL(nxt->index);
				insertSLL(nxt->data, actual->index);
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}
}

template<typename T>
void list<T>::divideSLL(list<T> &list1, list<T> &empty_list, T value)
{
	SLL<T>* actual = list1.startSLL;
	while (actual->nxtPtr != nullptr)
	{
		if (actual->data < value)
		{
			empty_list.pushSLL(actual->data, 0);
		}
		actual = actual->nxtPtr;
	}

	actual = list1.startSLL;
	int index = -1;
	while (actual->nxtPtr != nullptr)
	{
		if (actual->data < value)
		{
			index = actual->index;
		}
		if (index != -1)
		{
			list1.eraseSLL(index);
		}
		actual = actual->nxtPtr;
		index = -1;
	}
}

template<typename T>
void list<T>::pushDLL(T data, unsigned where)
{
	if (where == 0) //добавление в конец
	{
		if (this->startDLL == nullptr)
		{
			this->startDLL = new DLL<T>(data);
		}
		else
		{
			DLL<T>* actual = this->startDLL;
			while (actual->nxtPtr != nullptr)
			{
				actual = actual->nxtPtr;
			}
			actual->nxtPtr = new DLL<T>(data);
			unsigned prevIndex = actual->index;
			DLL<T>* previous = actual;
			actual = actual->nxtPtr;
			actual->prevPtr = previous;
			actual->index = ++(prevIndex);
			this->endDLL = actual;
		}
	}
	else if (where == 1) //добавление в начало
	{
		if (sizeSLL < 1)
		{
			cout << "ERROR : Add at least one item at the begining" << endl;
		}
		else
		{
			DLL<T>* prevStart = this->startDLL;
			DLL<T>* newStart = new DLL<T>(data);
			newStart->nxtPtr = prevStart;
			prevStart->prevPtr = newStart;
			this->startDLL = newStart;
			indexationDLL();

		}
	}
	sizeDLL++;
}

template<typename T>
void list<T>::popDLL(unsigned where)
{
	if (this->startDLL == nullptr)
	{
		cout << "ERROR : Sorry but current list is empty" << endl;
	}
	else if (where == 0) //выталькивание с начала
	{
		DLL<T>* actual = this->startDLL;
		DLL<T>* newStart = actual->nxtPtr;
		newStart->prevPtr = nullptr;
		this->startDLL = newStart;
		indexationDLL();
		sizeDLL--;
	}
	else if (where == 1) //выталькивание с конца
	{
		DLL<T>* actual = this->startDLL;
		while (actual->nxtPtr != this->endDLL)
		{
			actual = actual->nxtPtr;
		}
		actual->nxtPtr = nullptr;
		this->endDLL = actual;
		indexationDLL();
		sizeDLL--;
	}
}

template<typename T>
void list<T>::insertDLL(T data, unsigned where)
{
	DLL<T>* actual = this->startDLL;
	while (actual->nxtPtr != nullptr)
	{
		if (where == 0)
		{
			pushDLL(data, 1);
			break;
		}
		else
		{
			DLL<T>* nxtItem = actual->nxtPtr;
			if (where == nxtItem->index)
			{
				actual->nxtPtr = new DLL<T>(data);
				DLL<T>* newItem = actual->nxtPtr;
				newItem->nxtPtr = nxtItem;
				newItem->prevPtr = actual;
				nxtItem->prevPtr = newItem;
				indexationDLL();
				break;
			}
		}
		actual = actual->nxtPtr;
	}
	sizeDLL++;
}

template<typename T>
void list<T>::eraseDLL(unsigned index)
{
	if (index == 0) //если удалящийся элемент явлается началом списка
	{
		popDLL(0);
	}
	else if (index == (sizeDLL - 1))
	{
		popDLL(1);
	}
	else
	{
		DLL<T>* actual = this->startDLL;
		DLL<T>* nxtItem = actual->nxtPtr;
		while (actual->nxtPtr != nullptr)
		{
			if (nxtItem->index == index)
			{
				nxtItem = nxtItem->nxtPtr;
				actual->nxtPtr = nxtItem;
				nxtItem->prevPtr = actual;
				indexationDLL();
				sizeDLL--;
				break;
			}
			actual = actual->nxtPtr;
			nxtItem = actual->nxtPtr;
		}
	}
}

template<typename T>
void list<T>::viewDLL()
{
	DLL<T>* actual = this->startDLL;
	cout << actual->data << " ";
	while (actual->nxtPtr != nullptr)
	{
		actual = actual->nxtPtr;
		cout << actual->data << " ";
	}
	cout << endl;
}

template<typename T>
void list<T>::indexationDLL()
{
	DLL<T>* actual = this->startDLL;
	actual->index = 0;
	unsigned index = actual->index;
	actual = actual->nxtPtr;
	while (actual->nxtPtr != nullptr)
	{
		actual->index = ++index;
		actual = actual->nxtPtr;
	}
	actual->index = ++index;
}

template<typename T>
list<T>* list<T>::beginDLL()
{
	return this->startDLL;
}

template<typename T>
list<T>* list<T>::endingDLL()
{
	return this->end;
}

template<typename T>
unsigned list<T>::countDLL()
{
	return this->sizeDLL;
}

template<typename T>
void list<T>::mergeDLL(list<T>& list)
{
	//проверка первого списка на упорядоченность
	DLL<T>* actual = this->startDLL;
	DLL<T>* nxt = actual->nxtPtr;
	T min = actual->data;
	while (actual->nxtPtr != nullptr)
	{
		min = actual->data;
		while (nxt->nxtPtr != nullptr)
		{
			if (nxt->data < min)
			{
				cout << "list1 is not ranged" << endl;
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}

	//проверка второго списка на упорядоченность
	actual = list.startDLL;
	nxt = actual->nxtPtr;
	min = actual->data;
	while (actual->nxtPtr != nullptr)
	{
		min = actual->data;
		while (nxt->nxtPtr != nullptr)
		{
			if (nxt->data < min)
			{
				cout << "list2 is not ranged" << endl;
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}

	//добавление элементов первого списка во второй
	nxt = list.startDLL;
	while (nxt->nxtPtr != nullptr)
	{
		pushDLL(nxt->data, 0);
		nxt = nxt->nxtPtr;
	}
	pushDLL(nxt->data, 0);

	//упорядочивание
	actual = this->startDLL;
	nxt = actual->nxtPtr;
	T data = T();
	while (actual->nxtPtr != nullptr)
	{
		min = actual->data;
		nxt = actual->nxtPtr;
		while (nxt->nxtPtr != nullptr)
		{
			if (nxt->data <= min)
			{
				data = nxt->data;
				eraseDLL(nxt->index);
				insertDLL(nxt->data, actual->index);
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}
}

template<typename T>
void list<T>::divideDLL(list<T>& list1, list<T>& empty_list, T value)
{
	DLL<T>* actual = list1.startDLL;
	while (actual->nxtPtr != nullptr)
	{
		if (actual->data < value)
		{
			empty_list.pushDLL(actual->data, 0);
		}
		actual = actual->nxtPtr;
	}

	actual = list1.startDLL;
	int index = -1;
	while (actual->nxtPtr != nullptr)
	{
		if (actual->data < value)
		{
			index = actual->index;
		}
		if (index != -1)
		{
			list1.eraseDLL(index);
		}
		actual = actual->nxtPtr;
		index = -1;
	}
}
