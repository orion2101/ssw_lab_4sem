#include <iostream>

template <typename T>
class QueueStruct {
public:
	QueueStruct();
	~QueueStruct();

	void push(T data);
	T pop();
	T peek();
	int count() { return size; };
	void swap(QueueStruct<T> &queue);
	void reverse();

	bool operator==(QueueStruct<T> &queue)
	{
		int size1 = this->count();
		int size2 = queue.count();
		Queue<T>* actual1;
		Queue<T>* actual2;
		if (size1 != size2)
		{
			return false;
		}
		else
		{
			actual1 = this->head;
			actual2 = queue.head;
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

	friend bool operator!=(QueueStruct<T> &queue1, QueueStruct<T> &queue2)
	{
		if (!( queue1 == queue2))
		{
			return true;
		}
		return false;
	}

	friend bool operator<(QueueStruct<T>& queue1, QueueStruct<T> &queue2)
	{
		Queue<T>* actual1;
		Queue<T>* actual2;
		int size1 = queue1.count();
		int size2 = queue2.count();
		int min = 0;
		if (queue1 == queue2)
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
			actual1 = queue1.head;
			actual2 = queue2.head;
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

	friend bool operator>(QueueStruct<T> &queue1, QueueStruct<T> &queue2)
	{
		Queue<T>* actual1;
		Queue<T>* actual2;
		int size1 = queue1.count();
		int size2 = queue2.count();
		int min = 0;
		if (queue1 == queue2)
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
			actual1 = queue1.head;
			actual2 = queue2.head;
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
	
	friend bool operator <=(QueueStruct<T> &queue1, QueueStruct<T> &queue2)
	{
		if ((queue1 < queue2) || (queue1 == queue2))
		{
			return true;
		}
		return false;
	}

	friend bool operator >=(QueueStruct<T> &queue1, QueueStruct<T> &queue2)
	{
		if ((queue1 > queue2) || (queue1 == queue2))
		{
			return true;
		}
		return false;
	}

private:

	template <typename T>
	class Queue {
	public:
		T data;
		Queue* nxtPtr;

		Queue(T data = T(), Queue* nxtPtr = nullptr)
		{
			this->data = data;
			this->nxtPtr = nxtPtr;
		}
	};
	Queue<T>* head;
	int size;
};

template <typename T>
QueueStruct<T>::QueueStruct()
{
	size = 0;
	head = nullptr;
}

template<typename T>
QueueStruct<T>::~QueueStruct()
{
}

template <typename T>
void QueueStruct<T>::push(T data)
{
	if (head == nullptr)
	{
		head = new Queue<T>(data);
	}
	else
	{
		Queue<T>* actual = this->head;
		while (actual->nxtPtr != nullptr) // while we are not at the end of the queue
		{
			actual = actual->nxtPtr;
		}
		actual->nxtPtr = new Queue<T>(data);
	}
	size++;
}

template<typename T>
T QueueStruct<T>::pop()
{
	if (size != 0)
	{
		T tempData;
		Queue<T>* actual = this->head; // In a queue the first item is always the first that gets out
		tempData = actual->data;
		head = actual->nxtPtr; // the new head is the last previous item to head
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

template<typename T>
T QueueStruct<T>::peek()
{
	if (size != 0)
	{
		Queue<T>* actual = this->head;
		return actual->data;
	}
	else
	{
		std::cout << "Empty Queue" << std::endl;
		return 0;
	}
}

template<typename T>
inline void QueueStruct<T>::swap(QueueStruct<T> &queue)
{
	//here our queues are just commuting their heads adresses and their sizes
	Queue<T>* head;
	int size;
	head = queue.head;
	size = queue.count();
	queue.head = this->head;
	queue.size = this->size;
	this->head = head;
	this->size = size;
}

template<typename T>
inline void QueueStruct<T>::reverse()
{
	T* tempArr = new T[size]; //temporary array to save our queue data
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
