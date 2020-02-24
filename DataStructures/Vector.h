#include <iostream>

template<typename T>
class VectorStruct {
public:
	VectorStruct();
	~VectorStruct();

	void push(int index, T data);
	T pop(int index);
	T peek();
	int count() { return size; };
	void swap(VectorStruct<T>& vector, int index1, int index2);
	void reverse();
	T& operator[](const int index); // just to display the value of an item

	/*********************definition comparision operators*****************************************************/
	friend bool operator==(VectorStruct<T>& vector1, VectorStruct<T>& vector2)
	{
		int size1 = vector1.count();
		int size2 = vector2.count();
		if (size1 != size2)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < size1; i++)
			{
				if (vector1[i] != vector2[i])
				{
					return false;
				}
			}
			return true;
		}
	}

	friend bool operator!=(VectorStruct<T>& vector1, VectorStruct<T>& vector2)
	{
		if (!(vector1 == vector2))
		{
			return true;
		}
		return false;
	}

	friend bool operator <(VectorStruct<T>& vector1, VectorStruct<T>& vector2)
	{
		int size1 = vector1.count();
		int size2 = vector2.count();
		int min = 0;

		if (vector1 == vector2)
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
				if (vector1[i] > vector2[i])
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

	friend bool operator >(VectorStruct<T>& vector1, VectorStruct<T>& vector2)
	{
		int size1 = vector1.count();
		int size2 = vector2.count();
		int min = 0;

		if (vector1 == vector2)
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
				if (vector1[i] < vector2[i])
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

	friend bool operator <=(VectorStruct<T>& vector1, VectorStruct<T>& vector2)
	{
		if ((vector1 < vector2) || (vector1 == vector2))
		{
			return true;
		}
		return false;
	}

	friend bool operator >=(VectorStruct<T>& vector1, VectorStruct<T>& vector2)
	{
		if ((vector1 > vector2) || (vector1 == vector2))
		{
			return true;
		}
		return false;
	}

private:

	template<typename>
	class Vector {
	public:
		T data;
		Vector* nxtPtr; //adress of the next to the current item
		Vector* prevPtr; //adress of the previous to the current item

		Vector(T data = T(), Vector* nxtPtr = nullptr, Vector* prevPtr = nullptr)
		{
			this->data = data;
			this->nxtPtr = nxtPtr;
			this->prevPtr = prevPtr;
		}
	};
	Vector<T>* head;
	int size;
};

template <typename T>
VectorStruct<T>::VectorStruct()
{
	size = 0;
	head = nullptr;
}

template<typename T>
VectorStruct<T>::~VectorStruct()
{
}

template <typename T>
void VectorStruct<T>::push(int index, T data)
{
	Vector<T>* next;
	Vector<T>* actual;
	Vector<T>* previous;
	if (index == 0)
	{
		if (head == nullptr)
		{
			head = new Vector<T>(data);
		}
		else //if there is already a head
		{
			actual = this->head;
			previous = new Vector<T>(data); //new head
			actual->prevPtr = previous; //the old head saves address of new head
			next = actual;
			head = previous;
			head->nxtPtr = next; //we restore link between the head(the new one) and the second item(old head)
		}
	}
	else
	{
		actual = this->head;
		if ((index + 1) <= size) //if we are adding between items, we have to check that the index we indicate exists
		{
			int counter = 0;

			while (actual->nxtPtr != nullptr)
			{
				previous = actual; //if we create a new item next to the current item, it will be the previous item of the new one

				actual = actual->nxtPtr;
				counter++;

				if (counter == index)
				{
					next = actual; //the next item to the new item will be the current one
					actual = new Vector<T>(data);
					actual->prevPtr = previous;
					previous->nxtPtr = actual;
					actual->nxtPtr = next;
					break;
				}
			}
		}
		else
		{
			while (actual->nxtPtr != NULL)
			{
				actual = actual->nxtPtr;
			}
			actual->nxtPtr = new Vector<T>(data);
			previous = actual;
			actual = actual->nxtPtr;
			actual->prevPtr = previous;
		}
	}
	size++;
}

template<typename T>
T VectorStruct<T>::pop(int index)
{
	T tempData;
	Vector<T>* next;
	Vector<T>* actual;
	Vector<T>* previous;

	actual = this->head;
	if (index == 0)
	{
		tempData = actual->data;
		if (actual->nxtPtr != nullptr)
		{
			next = actual->nxtPtr;
			next->prevPtr = nullptr;
			this->head = next;
		}
		size--;
		delete actual;
		//return tempData;

	}
	else if ((index + 1) <= size) //we always check if that index exists
	{
		int counter = 0;

		previous = actual; //if we delete the item, next to this one, it will be the previous item of the item next to the one that we delete

		actual = actual->nxtPtr;
		counter++;

		if (counter == index)
		{

			tempData = actual->data; //we save the data that we return before delete
			previous->nxtPtr = actual->nxtPtr; //the next item of the item that is before the one that we delete will be the next to the one that we delete
			next = actual->nxtPtr;
			next->prevPtr = previous; // the previous item of the next item to the one that we delete will be the previous to the one that we delete
			delete actual;
			size--;
			//return tempData;
		}
	}
	else
	{
		std::cout << "Error: there is no item at that index" << std::endl;
	}
	return tempData;
}

template<typename T>
T VectorStruct<T>::peek()
{
	Vector<T>* actual = this->head;
	return actual->data;

}

template<typename T>
T& VectorStruct<T>::operator[](const int index)
{
	int counter = 0;
	Vector<T>* actual = this->head;
	while (actual->nxtPtr != nullptr)
	{
		if (counter == index)
		{
			return actual->data;
		}
		actual = actual->nxtPtr;
		counter++;
	}
}

template<typename T>
void VectorStruct<T>::swap(VectorStruct<T>& vector, int index1, int index2)
{
	T tempdata1 = pop(index1); //we pop and save value of the item at index1
	T tempdata2 = vector.pop(index2); //we pop and save value of the item at index 2
	push(index1, tempdata2); //we push the value of the item that was at index2 at index1
	vector.push(index2, tempdata1); //we push the value of the item that was at index1 at index2
}

template<typename T>
void VectorStruct<T>::reverse()
{
	T tempdata;
	int i = 0;
	int j = size - 1; // index of the last item
	int k = size / 2; // middle item
	while (i != k)
	{
		//begining with by the limits and by incrementing "i" and decrementing "j", we swap items at those indexes
		//continuing while we don't reach the middle of the structure
		tempdata = pop(j);
		push(i, tempdata);
		tempdata = pop(i + 1);
		push(j, tempdata);
		i++;
		j--;
	}
}