#include<AT89X52.h>
void main()
{
	unsigned int a;
	P0=0;
	while(1)
	{
	for(a=0;a<20000;a++);
	if(P0==0)
	P0=0x80;
	else
	P0=P0>>1;
	}
}	
