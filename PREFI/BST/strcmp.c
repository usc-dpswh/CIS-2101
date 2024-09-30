#include <stdio.h>
#include <string.h>

int main(){
	char A[5] = "100";
	char B[5] = "200";
	
	printf("\n100 <  200 = %d", strcmp(A, B) < 0);
	printf("\n100 >  200 = %d", strcmp(A, B) > 0);
	printf("\n100 == B = %d", strcmp(A, B) == 0);
	printf("\n100 != B = %d", strcmp(A, B) != 0);
}
