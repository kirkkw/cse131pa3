int f(int k)
{
	{
		  int k = k + 3; // 2nd k is parameter, initializing nested first k
		  int m = k; // use of new k, which is hiding the parameter
	}
	return 1;
}
