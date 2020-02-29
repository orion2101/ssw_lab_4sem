#include <iostream>

template <typename T1>
class VectorStruct {
public:
	VectorStruct();
	~VectorStruct();

	void push(T1 data);
	T1 pop();
	T1 peek();
	int count() const { return size; };
	void swap(VectorStruct<T1> &vector);
	void reverse();
	T1& at(int index) const;
	
	/*********************definition comparision operators*****************************************************/
	bool operator==(const VectorStruct<T1>& vector2)
	{
		int size1 = this->size;
		int size2 = vector2.count();
		if (size1 != size2)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < size1; i++)
			{
				if (this->at(i) != vector2.at(i))
				{
					return false;
				}
			}
			return true;
		}
	}

	bool operator!=(const VectorStruct<T1> &vector2)
	{
		return !(*this == vector2);
	}

	bool operator <(const VectorStruct<T1> &vector2)
	{
		int size1 = this->size;
		int size2 = vector2.count();
		int min = 0;

		if (*this == vector2)
		{
			return false;
		}
		else
		{
			if (size1 < size2)
			{
				min = size1;
			}
			else
			{
				min = size2;
			}

			for (int i = 0; i < min; i++)
			{
				if (this.at(i) > vector2.at(i))
				{
					return false;
				}
			}
			if (size1 > size2)
			{
				return false;
			}
			return true;
		}

	}

	bool operator >(const VectorStruct<T1> &vector2)
	{
		int size1 = this->size;
		int size2 = vector2.count();
		int min = 0;

		if (*this == vector2)
		{
			return false;
		}
		else
		{
			if (size1 < size2)
			{
				min = size1;
			}
			else
			{
				min = size2;
			}

			for (int i = 0; i < min; i++)
			{
				if (this.at(i) < vector2.at(i))
				{
					return false;
				}
			}
			if (size1 < size2)
			{
				return false;
			}
			return true;
		}
	}

	bool operator <=(const VectorStruct<T1> &vector2)
	{
		if ((*this < vector2) || (*this == vector2))
		{
			return true;
		}
		return false;
	}

	bool operator >=(const VectorStruct<T1> &vector2)
	{
		if ((*this > vector2) || (*this == vector2))
		{
			return true;
		}
		return false;
	}

private:

	class Vector {
	public:
		T1 data;
		Vector* nxtPtr; //adress of the next to the current item
		Vector* prevPtr; //adress of the previous to the current item

		Vector(T1 data = T1(), Vector* nxtPtr = nullptr, Vector* prevPtr = nullptr)
		{
			this->data = data;
			this->nxtPtr = nxtPtr;
			this->prevPtr = prevPtr;
		}
	};
	Vector* tail;
	int size;
};

template <typename T1>
VectorStruct<T1>::VectorStruct()
{
	size = 0;
	tail = nullptr;
}

template<typename T1>
VectorStruct<T1>::~VectorStruct()
{
	Vector* actual = this->tail;
	int size = this->size;
	for (int i = 0; i < size; i++)
	{
		pop();
	}
	actual = nullptr;
}

template <typename T1>
void VectorStruct<T1>::push(T1 data)
{
	if (this->tail == nullptr)
	{
		this->tail = new Vector(data);
	}
	else
	{
		Vector* actual = this->tail;
		actual->nxtPtr = new Vector(data);
		actual = actual->nxtPtr;
		actual->prevPtr = this->tail;
		this->tail = actual;
	}
	size++;
}

template<typename T1>
T1 VectorStruct<T1>::pop()
{
	T1 tempData;
	
	if (tail != nullptr)
	{
		Vector* actual = this->tail;
		tempData = actual->data;
		this->tail = actual->prevPtr;
		delete actual;
		actual = nullptr;
	}
	else
	{
		std::cout << "Empty vector" << std::endl;
	}
	size--;
	return tempData;
}

template<typename T1>
T1 VectorStruct<T1>::peek()
{
	Vector* actual = this->tail;
	return actual->data;

}

template<typename T1>
void VectorStruct<T1>::swap(VectorStruct<T1> &vector)
{
	//Commutation of tail pointers and size pointers of objects
	Vector* pointer = this->tail;
	int size = this->size;
	this->tail = vector.tail;
	this->size = vector.size;
	vector.tail = pointer;
	vector.size = size;
	pointer = nullptr;
}

template<typename T1>
void VectorStruct<T1>::reverse()
{
	Vector* actual = this->tail;
	Vector* next;
	Vector* previous;

	while (actual->prevPtr != nullptr)
	{
		previous = actual->prevPtr;
		next = actual->nxtPtr;
		
		actual->prevPtr = next;
		actual->nxtPtr = previous;

		actual = actual->nxtPtr;
	}

	//for the fist item
	if (actual->prevPtr == nullptr)
	{
		previous = actual->prevPtr;
		next = actual->nxtPtr;
		actual->prevPtr = next;
		actual->nxtPtr = previous;
		this->tail = actual;
	}
	actual = nullptr;
	next = nullptr;
	previous = nullptr;
}

template<typename T1>
T1& VectorStruct<T1>::at(int index) const
{
	Vector* actual = this->tail;
	
	//to scan our structure from the begining
	while (actual->prevPtr != nullptr)
	{
		actual = actual->prevPtr;
	}
	
	int counter = 0;
	while (counter != index)
	{
		actual = actual->nxtPtr;
		counter++;
	}

	return actual->data;
}