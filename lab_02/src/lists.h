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
	void viewSLL();
	void indexationSLL();
	list<T>* beginSLL();
	list<T>* endSLL();
	unsigned countSLL();
	void mergeSLL(list<T>& list);
	void divideSLL(list<T>& list1, list<T>& empty_list, T value);

	//функции двухсвязного списка
	void pushDLL(T data, unsigned where);
	void popDLL(unsigned where);
	void insertDLL(T data, unsigned where);
	void eraseDLL(unsigned index);
	void viewDLL();
	void indexationDLL();
	list<T>* beginDLL();
	list<T>* endDLL();
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
	
	SLL<T>* start;
	SLL<T>* end;
	unsigned size;
};

template<typename T>
list<T>::list()
{
	size = 0;
	start = nullptr;
	end = nullptr;

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
		if (this->start == nullptr)
		{
			this->start = new SLL<T>(data);
		}
		else
		{
			SLL<T>* actual = this->start;
			while (actual->nxtPtr != nullptr)
			{
				actual = actual->nxtPtr;
			}
			actual->nxtPtr = new SLL<T>(data);
			unsigned prevIndex = actual->index;
			actual = actual->nxtPtr;
			actual->index = ++(prevIndex);
			//indexation();
			this->end = actual;
			
		}
	}
	else if (where == 1) //добавление в начало
	{
		if (size < 1)
		{
			cout << "ERROR : Add at least one item at the begining" << endl;
		}
		else 
		{
			SLL<T>* prevStart = this->start;
			SLL<T>* newStart = new SLL<T>(data);
			newStart->nxtPtr = prevStart;
			this->start = newStart;
			indexationSLL();
			
		}
		
	}
	
	size++;
}

template<typename T>
void list<T>::popSLL(unsigned where)
{
	if (this->start == nullptr)
	{
		cout << "ERROR : Sorry but current list is empty" << endl;
	}
	else if (where == 0) //выталькивание с начала
	{
		SLL<T>* actual = this->start;
		SLL<T>* newStart = actual->nxtPtr;
		this->start = newStart;
		indexationSLL();
		size--;
	}
	else if (where == 1) //выталькивание с конца
	{
		SLL<T>* actual = this->start;
		while (actual->nxtPtr != this->end)
		{
			actual = actual->nxtPtr;
		}
		actual->nxtPtr = nullptr;
		this->end = actual;
		indexationSLL();
		size--;
	}
}

template<typename T>
void list<T>::insertSLL(T data, unsigned where)
{
	SLL<T>* actual = this->start;
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
	size++;
}

template<typename T>
void list<T>::eraseSLL(unsigned index)
{	
	//SLL<T>* element = actual->nxtPtr;
	if (index == 0) //если удалящийся элемент явлается началом списка
	{
		popSLL(0);
	}
	else if (index == (size - 1))
	{
		popSLL(1);
	}
	else //if (actual->index == index)
	{
		SLL<T>* actual = this->start;
		SLL<T>* nxtItem = actual->nxtPtr;
		while (actual->nxtPtr != nullptr)
		{
			if (nxtItem->index == index)
			{
				actual->nxtPtr = nxtItem->nxtPtr;
				indexationSLL();
				size--;
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
	SLL<T>* actual = this->start;
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
	SLL<T>* actual = this->start;
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
	return this->start;
}

template<typename T>
list<T>* list<T>::endSLL()
{
	return this->end;
}

template<typename T>
unsigned list<T>::countSLL()
{
	return size;
}

template<typename T>
void list<T>::mergeSLL(list<T> &list)
{
	//проверка первого списка на упорядоченность
	SLL<T>* actual = this->start;
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
	actual = list.start;
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
	nxt = list.start;
	while (nxt->nxtPtr != nullptr)
	{
		pushSLL(nxt->data, 0);
		nxt = nxt->nxtPtr;
	}
	pushSLL(nxt->data, 0);

	//упорядочивание
	actual = this->start;
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
	SLL<T>* actual = list1.start;
	while (actual->nxtPtr != nullptr)
	{
		if (actual->data < value)
		{
			empty_list.pushSLL(actual->data, 0);
		}
		actual = actual->nxtPtr;
	}

	actual = list1.start;
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
		if (this->start == nullptr)
		{
			this->start = new DLL<T>(data);
		}
		else
		{
			DLL<T>* actual = this->start;
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
			this->end = actual;
		}
	}
	else if (where == 1) //добавление в начало
	{
		if (size < 1)
		{
			cout << "ERROR : Add at least one item at the begining" << endl;
		}
		else
		{
			DLL<T>* prevStart = this->start;
			DLL<T>* newStart = new DLL<T>(data);
			newStart->nxtPtr = prevStart;
			prevStart->prevPtr = newStart;
			this->start = newStart;
			indexationDLL();

		}
	}
	size++;
}

template<typename T>
inline void list<T>::popDLL(unsigned where)
{
	if (this->start == nullptr)
	{
		cout << "ERROR : Sorry but current list is empty" << endl;
	}
	else if (where == 0) //выталькивание с начала
	{
		DLL<T>* actual = this->start;
		DLL<T>* newStart = actual->nxtPtr;
		newStart->prevPtr = nullptr;
		this->start = newStart;
		indexationDLL();
		size--;
	}
	else if (where == 1) //выталькивание с конца
	{
		DLL<T>* actual = this->start;
		while (actual->nxtPtr != this->end)
		{
			actual = actual->nxtPtr;
		}
		actual->nxtPtr = nullptr;
		this->end = actual;
		indexationDLL();
		size--;
	}
}

template<typename T>
inline void list<T>::insertDLL(T data, unsigned where)
{
}

template<typename T>
inline void list<T>::eraseDLL(unsigned index)
{
}

template<typename T>
inline void list<T>::viewDLL()
{
}

template<typename T>
inline void list<T>::indexationDLL()
{
}

template<typename T>
inline list<T>* list<T>::beginDLL()
{
	return NULL;
}

template<typename T>
inline list<T>* list<T>::endDLL()
{
	return NULL;
}

template<typename T>
inline unsigned list<T>::countDLL()
{
	return 0;
}

template<typename T>
inline void list<T>::mergeDLL(list<T>& list)
{
}

template<typename T>
inline void list<T>::divideDLL(list<T>& list1, list<T>& empty_list, T value)
{
}
