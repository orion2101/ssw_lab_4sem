#include <iostream>
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"

int main()
{
	int size = 0;
	
	VectorStruct<int> vector;

	for (int i = 0; i < 10; i++) vector.push(i, i);

	size = vector.count();
	std::cout << size << std::endl;

	for (int i = 0; i < 10; i++) std::cout << vector.pop(0) << " ";

	std::cout << std::endl;

	system("pause");
}