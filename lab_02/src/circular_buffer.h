#include <iostream>
using namespace std; 

template<typename T>
class CBuff {
public:
	CBuff();
	~CBuff();

	//������� ������������ ������
	void createCB(unsigned size);
	void pushCB(T data);
	T popCB();
	void moveCB(); //����� ���������
	void insertCB(T data, unsigned where);
	void eraseCB(unsigned index); //��������� �������������� ������ �������� ���� "used" = 1
	void viewCB(); //����� ��������� ������
	CBuff<T>* beginCB();
	CBuff<T>* endCB();
	unsigned countCB(); //������� ������ ������
	int mergeCB(CBuff<T>& buff); //������� ���������� 1 ���� ��������� ������
	int divideCB(CBuff<T>& buff, CBuff<T>& empty_buff, T value); //list1 - ������ ��������� ��� ���������, ������ � ������� ����� ��������� �������� ������ ��� �������� ��������
	//empty_list - ������ ������, � ������� ����� ���������� �������� ������ ��� ��������������

private:
	template<typename T>
	class CB { //������������ ������
	public:
		CB* prevPtr;
		CB* nxtPtr;
		T data;
		int index;
		bool used; //������ �� ������

		CB(T data = T(), CB* prevPtr = nullptr, CB* nxtPtr = nullptr, int index = 0, bool used = 0)
		{
			this->prevPtr = prevPtr;
			this->nxtPtr = nxtPtr;
			this->data = data;
			this->index = index;
			this->used = used;
		}
	};

	CB<T>* start;
	CB<T>* end;
	unsigned size;
};

template<typename T>
CBuff<T>::CBuff()
{
	start = nullptr;
	end = nullptr;
	size = 0;
}

template<typename T>
CBuff<T>::~CBuff()
{
}

template<typename T>
void CBuff<T>::createCB(unsigned size)
{
	this->size = size;
	this->start = new CB<T>();
	CB<T>* actual = this->start;
	actual->index = 0;

	CB<T>* previous = actual;
	for (int i = 0; i < size; i++)
	{
		previous = actual;
		actual->nxtPtr = new CB<T>();
		actual = actual->nxtPtr;
		actual->prevPtr = previous;
		actual->index = ++(previous->index);
	}

	//��������� ���������
	this->end = actual;
	actual->nxtPtr = this->start;
	actual = this->start;
	actual->prevPtr = this->end;
}

template<typename T>
void CBuff<T>::pushCB(T data)
{
	CB<T>* actual = this->end;
	if (actual->used = 0)
	{
		actual->data = data;
		actual->used = 1;
	}
	else
	{
		moveCB();
		actual->data = data;
	}
}

template<typename T>
T CBuff<T>::popCB()
{
	CB<T>* actual = this->start;
	actual->used = 0;
	return actual->data;
}

template<typename T>
void CBuff<T>::moveCB()
{
	CB<T>* actual = this->start;
	CB<T>* nxt = actual->nxtPtr;
	while (actual->nxtPtr != this->end)
	{
		actual->data = nxt->data;
		if (nxt->used == 1)
		{
			actual->used == 1;
		}
		actual = actual->nxtPtr;
		nxt = actual->nxtPtr;
	}
}

template<typename T>
void CBuff<T>::insertCB(T data, unsigned where)
{
	CB<T>* actual = this->start;
	while (actual->index != where)
	{
		actual = actual->nxtPtr;
	}
	actual->data = data;
	if (actual->used == 0)
	{
		actual->used = 1;
	}
}

template<typename T>
void CBuff<T>::eraseCB(unsigned index)
{
	CB<T>* actual = this->start;
	while (actual->index != where)
	{
		actual = actual->nxtPtr;
	}
	
	actual->used = 0;
}

template<typename T>
void CBuff<T>::viewCB()
{
	CB<T>* actual = this->start;
	while (actual->nxtPtr != this->end)
	{
		cout << actual->data << " ";
		actual = actual->nxtPtr;
	}
	cout << actual->data;
	cout << endl;
}

template<typename T>
CBuff<T>* CBuff<T>::beginCB()
{
	return this->start;
}

template<typename T>
CBuff<T>* CBuff<T>::endCB()
{
	return this->end;
}

template<typename T>
unsigned CBuff<T>::countCB()
{
	return this->size;
}

template<typename T>
int CBuff<T>::mergeCB(CBuff<T>& buff)
{
	int used1 = 0;
	int used2 = 0;

	//�������� �� ���������� ������� ����� � ������ ������
	CB<T>* actual = this->start;
	while (actual != this->end)
	{
		if (actual->used == 1)
		{
			used1++;
			actual = actual->nxtPtr;
		}
	}

	actual = buff.start;
	while (actual != buff.end)
	{
		if (actual->used == 1)
		{
			used2++;
			actual = actual->nxtPtr;
		}
	}

	if (used1 + used2 < this->size)
	{
		return 1;
	}

	//���������� ��������� ������� ������ � ������
	actual = buff.start;
	while (actual != buff.end)
	{
		if (actual->used == 1)
		{
			CB<T>* actual_1 = this->start;
			while (actual_1->used != 0)
			{
				actual_1 = actual_1->nxtPtr;
			}
			insertCB(actual->data, actual_1->index);
		}
		actual = actual->nxtPtr;
	}

	//��������������
	actual = this->start;
	T data = T();
	while (actual != this->end)
	{
		T min = actual->data;
		CB<T>* nxt = actual->nxtPtr;
		while (nxt->nxtPtr != this->end)
		{
			if (nxt->data <= min)
			{
				data = nxt->data;
				eraseCB(nxt->index);
				insertCB(nxt->data, actual->index);
			}
			nxt = nxt->nxtPtr;
		}
		actual = actual->nxtPtr;;
	}
}

template<typename T>
int CBuff<T>::divideCB(CBuff<T>& buff, CBuff<T>& empty_buff, T value)
{
	CB<T>* actual = buff.start;
	while (actual != this->end)
	{
		if (actual->data < value)
		{
			empty_buff.pushCB(actual->data);
		}
		actual = actual->nxtPtr;
	}

	actual = buff.start;
	while (actual != this->end)
	{
		if (actual->data < value)
		{
			eraseCB(actual->index);
		}
		actual = actual->nxtPtr;
	}
}
