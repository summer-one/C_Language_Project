#include<AT89X52.h>
#define ROTATE_LEFT(x,  n) ((x) << (n)) | ((x) >> ((8*sizeof(x)) - (n)))
void delay(){
	int i,j;
	for(i=0;i<500;i++){
		for(j=0;j<100;j++){}
	}
}
void main(){
	unsigned char   x = 0xAA;
	P0 = 0x00;
	while(1){
		x = ROTATE_LEFT(x,1);
		P0 = x;
		delay();
		/*
		P0 = 0x00;
		P0_0 = 1;
		delay();
		P0_0 = 0;
		P0_1 = 1;
		delay();
		P0_1 = 0;
		*/
		
	}
}
