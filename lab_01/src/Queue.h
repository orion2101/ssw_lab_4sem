#include <iostream>

template <typename T1>
class QueueStruct {
public:
	QueueStruct();
	~QueueStruct();

	void push(T1 data);
	T1 pop();
	T1 peek();
	int count() const { return size; };
	void swap(QueueStruct<T1> &queue);
	void reverse();

	bool operator==(const QueueStruct<T1> &queue)
	{
		int size1 = this->size;
		int size2 = queue.count();

		if (size1 != size2)
		{
			return false;
		}
		else
		{
			Queue* actual1 = this->head;
			Queue* actual2 = queue.head;
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

	bool operator!=(const QueueStruct<T1> &queue2)
	{
		return !(*this == queue2);
	}

	bool operator<(const QueueStruct<T1> &queue2)
	{
		int size1 = this->size;
		int size2 = queue2.count();
		int min = 0;
		if (*this == queue2)
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
			Queue* actual1 = this->head;
			Queue* actual2 = queue2.head;
			for (int i = 0; i < min; i++)
			{
				if (actual1->data > actual2->data)
				{
					return false;
				}
				actual1 = actual1->nxtPtr;
				actual2 = actual2->nxtPtr;
			}
			// if items ot 0 to min of our queue are not bigger that the item we compare it to, 
			//but at the same time the size of that item is bigger that the size of our queue, it implies it is bigger than it
			if (size1 > size2) 
			{
				return false;
			}
			return true;
		}
	}

	bool operator>(const QueueStruct<T1> &queue2)
	{
		int size1 = this->size;
		int size2 = queue2.count();
		int min = 0;
		if (*this == queue2)
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
			Queue* actual1 = this->head;
			Queue* actual2 = queue2.head;
			for (int i = 0; i < min; i++)
			{
				if (actual1->data < actual2->data)
				{
					return false;
				}
				actual1 = actual1->nxtPtr;
				actual2 = actual2->nxtPtr;
			}
			// if value of items ot 0 to min of our queue are not lesser that the values of the item we compare it to, 
			//but at the same time the size of that item is lesser that the size of our queue, it implies it is lesser than it
			if (size1 < size2)
			{
				return false;
			}
			return true;
		}
	}
	
	bool operator <=(const QueueStruct<T1> &queue2)
	{
		if ((*this < queue2) || (*this == queue2))
		{
			return true;
		}
		return false;
	}

	bool operator >=(const QueueStruct<T1> &queue2)
	{
		if ((*this > queue2) || (*this == queue2))
		{
			return true;
		}
		return false;
	}

private:

	class Queue {
	public:
		T1 data;
		Queue* nxtPtr;

		Queue(T1 data = T1(), Queue* nxtPtr = nullptr)
		{
			this->data = data;
			this->nxtPtr = nxtPtr;
		}
	};
	Queue* head;
	int size;
};

template <typename T1>
QueueStruct<T1>::QueueStruct()
{
	size = 0;
	head = nullptr;
}

template<typename T1>
QueueStruct<T1>::~QueueStruct()
{
	Queue* actual = this->head;
	int size = this->size;
	for (int i = 0; i < size; i++)
	{
		pop();
	}
	actual = nullptr;
}

template <typename T1>
void QueueStruct<T1>::push(T1 data)
{
	if (this->head == nullptr)
	{
		this->head = new Queue(data);
	}
	else
	{
		Queue* actual = this->head;
		while (actual->nxtPtr != nullptr) // while we are not at the end of the queue
		{
			actual = actual->nxtPtr;
		}
		actual->nxtPtr = new Queue(data);
	}
	size++;
}

template<typename T1>
T1 QueueStruct<T1>::pop()
{
	if (size != 0)
	{
		T1 tempData;
		Queue* actual = this->head; // In a queue the first item is always the first that gets out
		tempData = actual->data;
		this->head = actual->nxtPtr; // the new head is the last previous item to head
		delete actual;
		size--;
		return tempData;
	}
	else
	{
		std::cout << "Empty Queue" << std::endl;
		return 0;
	}
}

template<typename T1>
T1 QueueStruct<T1>::peek()
{
	if (size != 0)
	{
		Queue* actual = this->head;
		return actual->data;
	}
	else
	{
		std::cout << "Empty Queue" << std::endl;
		return 0;
	}
}

template<typename T1>
void QueueStruct<T1>::swap(QueueStruct<T1> &queue)
{
	//here our queues are just commuting their heads adresses and their sizes
	Queue* head;
	int size;
	head = queue.head;
	size = queue.count();
	queue.head = this->head;
	queue.size = this->size;
	this->head = head;
	this->size = size;
}

template<typename T1>
void QueueStruct<T1>::reverse()
{
	T1* tempArr = new T1[size]; //temporary array to save our queue data
	int j = size;

	for (int i = 0; i < j; i++)
	{
		tempArr[i] = pop();
	}

	for (int i = j - 1; i >= 0; i--) //to reverse, we push the data by begining at the end
	{
		push(tempArr[i]);
	}

	delete[] tempArr;
}
