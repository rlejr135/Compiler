int qq;
int factorial (int n){
    if(n==0){
        return 1;
    } 
    else
        return n*factorial(n-1);
}

int g[10];

int IterativeFibonacci(int num)
{
    int a;
    int b;
    int c;
    int i;
    a=1;
    b=1;
    if(num == 0){
        return 0;
    }
    i=3;
    while(i<=n){
        int c;
        c = a+b;
        a = b;
        b = c;
        i = i+1;
    }
    return b;
}

int main(void){
    int x;
    int y;
    x=input();
    output(factorial(x));
    y=input();
    output (IterativeFibonacci(y));
}
