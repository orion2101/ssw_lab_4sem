#include <iostream>

template <typename T1>
class StackStruct {
public:
	StackStruct();
	~StackStruct();

	/*stack functions*/
	void push(T1 data);
	T1 pop();
	T1 peek();
	int count() const { return size; };
	void swap(StackStruct<T1> &stack);
	void reverse();

	/*********************definition comparision operators*****************************************************/
	bool operator==(const StackStruct<T1> &stack)
	{
		int size1 = this->size;
		int size2 = stack.count();
	
		if (size1 != size2)
		{
			return false;
		}
		else
		{
			Stack* actual1 = this->head;
			Stack* actual2 = stack.head;
			for (int i = 0; i < size1; i++)
			{
				if (actual1->data != actual2->data)
				{
					return false;
				}
				actual1 = actual1->nxtPtr;
				actual2 = actual2->nxtPtr;
			}
			return true;
		}
	}

	bool operator!=(const StackStruct<T1> &stack2)
	{
		return !(*this == stack2);
	}

	bool operator <(const StackStruct<T1> &stack2)
	{
		int size1 = this->size;
		int size2 = stack2.count();
		int min = 0;
		if (*this == stack2)
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
			Stack* actual1 = this->head;
			Stack* actual2 = stack2.head;
			for (int i = 0; i < min; i++)
			{
				if (actual1->data > actual2->data)
				{
					return false;
				}
				actual1 = actual1->nxtPtr;
				actual2 = actual2->nxtPtr;
			}
			if (size1 > size2)
			{
				return false;
			}
			return true;
		}
	}

	bool operator >(const StackStruct<T1> &stack2)
	{
		int size1 = this->size;
		int size2 = stack2.count();
		int min = 0;
		if (*this == stack2)
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
			Stack* actual1 = this->head;
			Stack* actual2 = stack2.head;
			for (int i = 0; i < min; i++)
			{
				if (actual1->data < actual2->data)
				{
					return false;
				}
				actual1 = actual1->nxtPtr;
				actual2 = actual2->nxtPtr;
			}
			if (size1 < size2)
			{
				return false;
			}
			return true;
		}
	}

	bool operator <=(const StackStruct<T1> &stack2)
	{
		if ((*this < stack2) || (*this == stack2))
		{
			return true;
		}
		return false;
	}

	bool operator >=(const StackStruct<T1> &stack2)
	{
		if ((*this > stack2) || (*this == stack2))
		{
			return true;
		}
		return false;
	}
private:

	class Stack {
	public:
		T1 data;
		//mem adresses of next and previous element
		Stack* nxtPtr;
		Stack* prevPtr;

		Stack(T1 data = T1(), Stack* nxtPtr = nullptr, Stack* prevPtr = nullptr)
		{
			this->data = data;
			this->nxtPtr = nxtPtr;
			this->prevPtr = prevPtr;
		}
	};
	Stack* head; // here, the head will indicate the end of the stack, so the last to get out
	Stack* tail;
	int size;
};

template <typename T1>
StackStruct<T1>::StackStruct()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T1>
StackStruct<T1>::~StackStruct()
{
	Stack* actual = this->tail;
	int size = this->size;
	for (int i = 0; i < size; i++)
	{
		pop();
	}
	actual = nullptr;
}

template <typename T1>
void StackStruct<T1>::push(T1 data)
{
	if (this->head == nullptr)
	{
		head = new Stack(data);
	}
	else
	{
		Stack* actual = this->head;
		while (actual->nxtPtr != nullptr)
		{
			actual = actual->nxtPtr;
		}

		Stack* previous = actual; //when adding in a stack, because order is reversed(LIFO), the existing item will always be behind the new item 
		actual->nxtPtr = new Stack(data);
		actual = actual->nxtPtr;
		actual->prevPtr = previous;
		this->tail = actual;
	}
	size++;
}

template<typename T1>
T1 StackStruct<T1>::pop()
{
	T1 tempData;
	Stack* actual = this->tail; // in a stack, the last item is the first to get out
	tempData = actual->data;
	this->tail = actual->prevPtr; // the new tail is the previous item to the actual tail
	if(size != 1 ) tail->nxtPtr = nullptr;
	if (this->tail == nullptr) this->head = nullptr;
	delete actual;
	size--;
	return tempData;
}

template<typename T1>
T1 StackStruct<T1>::peek()
{
	if (size != 0)
	{
		Stack* actual = this->tail;
		return actual->data;
	}
	else
	{
		std::cout << "Empty Stack" << std::endl;
		return 0;
	}
}

template<typename T1>
void StackStruct<T1>::swap(StackStruct<T1> &stack)
{
	//here our queues are just commuting their heads adresses, tail adresses and their sizes
	Stack* head;
	Stack* tail;
	int size;
	head = stack.head;
	tail = stack.tail;
	size = stack.count();
	stack.head = this->head;
	stack.tail = this->tail;
	stack.size = this->size;
	this->head = head;
	this->tail = tail;
	this->size = size;
}

template<typename T1>
void StackStruct<T1>::reverse()
{
	T1* tempArr = new T1[size]; //temporary array to save our stack data
	int j = size;

	for (int i = 0; i < j; i++)
	{
		tempArr[i] = pop();
	}

	//because we popped last to first, so that is the actual order of in our tempoprary array and to reverse, we push in that order
	for (int i = 0; i < j; i++) 
	{
		push(tempArr[i]);
	}

	delete[] tempArr;
}
