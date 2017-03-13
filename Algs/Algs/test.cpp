#include <iostream>

int search(int A[], int size, int key)
{
	int i = 0;
	while(i < size)	
	{
		if (A[i] == key)
			return i;
		i++;
	}
	return -1;
}
 
void test(int A[], int size)
{
	std::cout << ((search(A, size, 1) == 0)    ? "passed" : "failed") << std::endl;
	std::cout << ((search(A, size, 0) == -1)   ? "passed" : "failed") << std::endl;
	std::cout << ((search(A, size, 'd') == -1) ? "passed" : "failed") << std::endl;
	std::cout << ((search(A, size, 2) == 1)    ? "passed" : "failed") << std::endl;
	std::cout << ((search(A, size, 100) == -1) ? "passed" : "failed") << std::endl;
}

int main()
{
	int array[] = { 1, 2, 3, 4, 5 };
	test(array, 5);
	return 0;
}