int f(int n){
	
	if (n>1) return n*f(n-1);
	else return 1;

	return 1;
}
void main(void){
	output(f(input()));

}
