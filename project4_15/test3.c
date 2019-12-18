int k[100];

int init(void){
	int q;
	q = input();
	return q;
}


void main(void)
{
	int n;
	int sn;
	int a;
	int i;
	int b;

	n = input();
	sn = n;

	b = 0;
	i = 0;
	while(n)
	{
		a = init();
		k[i] = a * a;
		n = n - 1;
		i = i + 1;
	}

	i = 0;
	while(sn){
		output(k[i]);
		i = i+1;
		sn = sn-1;
	}
}
