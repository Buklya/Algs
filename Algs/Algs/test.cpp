int search(int A[], int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (A[i] == key)
			return i;
	}
	return -1;
}