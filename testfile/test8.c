/* error6
	 		void type of array index */

int a[5];

void func(void){
				;
}
void main(void){
				a[func()] = 1;
}

