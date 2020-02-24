#include <iostream>

template <typename T>
class StackStruct {
public:
	StackStruct();
	~StackStruct();

	/*stack functions*/
	void push(T data);
	T pop();
	T peek();
	int count() { return size; };
	void swap(StackStruct<T> &stack);
	void reverse();

	/*********************definition comparision operators*****************************************************/
	bool operator==(StackStruct<T> &stack)
	{
		int size1 = this->count();
		int size2 = stack.count();
		Stack<T>* actual1;
		Stack<T>* actual2;
		if (size1 != size2)
		{
			return false;
		}
		else
		{
			actual1 = this->head;
			actual2 = stack.head;
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

	friend bool operator!=(StackStruct<T> &stack1, StackStruct<T> &stack2)
	{
		if (!(stack1 == stack2))
		{
			return true;
		}
		return false;
	}

	friend bool operator <(StackStruct<T>& stack1, StackStruct<T> &stack2)
	{
		Stack<T>* actual1;
		Stack<T>* actual2;
		int size1 = stack1.count();
		int size2 = stack2.count();
		int min = 0;
		if (stack1 == &stack2)
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
			actual1 = stack1.head;
			actual2 = stack2.head;
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

	friend bool operator >(StackStruct<T> &stack1, StackStruct<T> &stack2)
	{
		Stack<T>* actual1;
		Stack<T>* actual2;
		int size1 = stack1.count();
		int size2 = stack2.count();
		int min = 0;
		if (stack1 == stack2)
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
			actual1 = stack1.head;
			actual2 = stack2.head;
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

	friend bool operator <=(StackStruct<T> &stack1, StackStruct<T> &stack2)
	{
		if ((stack1 < stack2) || (stack1 == stack2))
		{
			return true;
		}
		return false;
	}

	friend bool operator >=(StackStruct<T> &stack1, StackStruct<T> &stack2)
	{
		if ((stack1 > stack2) || (stack1 == stack2))
		{
			return true;
		}
		return false;
	}
private:

	template<typename>
	class Stack {
	public:
		T data;
		//mem adresses of next and previous element
		Stack* nxtPtr;
		Stack* prevPtr;

		Stack(T data = T(), Stack* nxtPtr = nullptr, Stack* prevPtr = nullptr)
		{
			this->data = data;
			this->nxtPtr = nxtPtr;
			this->prevPtr = prevPtr;
		}
	};
	Stack<T>* head; // here, the head will indicate the end of the stack, so the last to get out
	Stack<T>* tail;
	int size;
};

template <typename T>
StackStruct<T>::StackStruct()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
StackStruct<T>::~StackStruct()
{
}

template <typename T>
void StackStruct<T>::push(T data)
{
	Stack<T>* actual;
	Stack<T>* previous;
	if (this->head == nullptr)
	{
		head = new Stack<T>(data);
		this->tail = this->head;
	}
	else
	{
		actual = this->head;
		while (actual->nxtPtr != nullptr)
		{
			actual = actual->nxtPtr;
		}

		previous = actual; //when adding in a stack, because order is reversed(LIFO), the existing item will always be behind the new item 
		actual->nxtPtr = new Stack<T>(data);
		actual = actual->nxtPtr;
		actual->prevPtr = previous;
		this->tail = actual;
	}
	size++;
}

template<typename T>
T StackStruct<T>::pop()
{
	T tempData;
	Stack<T>* actual = this->tail; // in a stack, the last item is the first to get out
	tempData = actual->data;
	this->tail = actual->prevPtr; // the new tail is the previous item to the actual tail
	if(size != 1 ) tail->nxtPtr = nullptr;
	if (this->tail == nullptr) this->head = nullptr;
	delete actual;
	size--;
	return tempData;
}

template<typename T>
T StackStruct<T>::peek()
{
	if (size != 0)
	{
		Stack<T>* actual = this->tail;
		return actual->data;
	}
	else
	{
		std::cout << "Empty Stack" << std::endl;
		return 0;
	}
}

template<typename T>
void StackStruct<T>::swap(StackStruct<T> &stack)
{
	//here our queues are just commuting their heads adresses, tail adresses and their sizes
	Stack<T>* head;
	Stack<T>* tail;
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

template<typename T>
void StackStruct<T>::reverse()
{
	T* tempArr = new T[size]; //temporary array to save our stack data
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
