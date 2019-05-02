int rearray(int a[], int index, int len)
{
    int temp;
    temp=a[index];
    a[index] = a[len-index];
    a[len-index]=temp;
    if(index==len/2)
        return;
    rearray(a,index+1,len);
}

void main(void)
{
    int a[100];
    int b;
    int i;
    i=0;
    while(i<100){
        a[i]=input();
        i=i+1;
    }
    rearray(a,0,99);
    i=0;
    while(i<99){
        output(a[i]);
        i++;
    }
}
