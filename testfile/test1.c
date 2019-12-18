int brr[5];

void copy_arr(int a[], int n){
	int i;

	for(i=0;i<n;i++){
		brr[i] = arr[i];
	}
}

void shakersort(int a[], int n)
{
	int i, p;
	int tmp;
	for(p=1;p<=n/2;p++)
	{
		for(i=p-1;i<n-p;i++)
		{
			if(a[i] > a[i+1])
			{
						tmp = a[i];
						a[i] = a[i+1];
						a[i+1] = tmp;
			}
		}

		for(i=n-p-1;i>=p;i--)
		{
			if(a[i] < a[i-1])
			{
						tmp = a[i];
						a[i] = a[i+1];
						a[i+1] = tmp;
			}
		}
	}

	copy_arr(a, n);
}


void main(void){
	int arr[5] = {10, 20, 50, 40, 30};
	int i;

	shakersort(arr, 5);

	return 0;
}
