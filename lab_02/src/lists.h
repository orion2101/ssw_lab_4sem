#include <iostream>
using namespace std;

template <typename T>
class list {
public:
	list();
	~list();
	void pushSLL(T data, unsigned where);
	void popSLL(unsigned where);
	void insert(T data, unsigned where);
	void eraseSLL(unsigned index);
	void view();
	void indexation();
	list<T>* beginSLL();
	list<T>* endSLL();
	unsigned countSLL();
	void merge(list<T>& list);
private:

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
			indexation();
			
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
	else if (where == 1) //выталькивание с начала
	{
		SLL<T>* actual = this->start;
		SLL<T>* newStart = actual->nxtPtr;
		this->start = newStart;
		indexation();
		size--;
	}
	else if (where == 0) //выталькивание с конца
	{
		SLL<T>* actual = this->start;
		while (actual->nxtPtr != this->end)
		{
			actual = actual->nxtPtr;
		}
		actual->nxtPtr = nullptr;
		this->end = actual;
		indexation();
		size--;
	}
}

template<typename T>
void list<T>::insert(T data, unsigned where)
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
				indexation();
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
				indexation();
				size--;
				break;
			}
			actual = actual->nxtPtr;
			nxtItem = actual->nxtPtr;
		}
	}
}

template<typename T>
void list<T>::view()
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
void list<T>::indexation()
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
void list<T>::merge(list<T> &list)
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
				insert(nxt->data, actual->index);
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}
}
