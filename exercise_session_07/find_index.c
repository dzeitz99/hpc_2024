#include <stdio.h>

int ii(int x, int y){
	return y * 14 + x;
}

int main() {
	int x,y;
	for ( y = 0 ; y < 6 ; ++y){
		for ( x = 0 ; x < 14 ; ++x) {
			printf("(%d , %d) = A[%d]", y, x, ii(x,y));
		}
	}
	return 0;
}
