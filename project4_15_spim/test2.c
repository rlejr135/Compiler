void main(void)
{
	int n;
	int a;
	int b;
	int c;

	n = input();

	if(n <= 0)
	{
		output(0);
		return;
	}

	a = 0;
	b = 1;

	while(n)
	{
		b = a + b;
		a = b - a;
		n = n - 1;
	}

	output(a);
}
