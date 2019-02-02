#include <AT89X52.h> 
unsigned char TAB[16]=
{                         
    0x01,                
    0x02,                 
    0x04,                 
    0x08,                
    0x10,                
    0x20,                 
    0x40,             
    0x80,                  
    0xC0,                 
    0xE0,                
    0xF0,                
    0xF8,                 
    0xFC,                  
    0xFE,                 
    0xFF,                  
    0x00,                 
};     
unsigned char light_on1(unsigned char m){
	unsigned int a;
	for(a=0;a<20000;a++);
	if(P0==0) m=0x01;
	else m=m<<1;
	return m;
}
unsigned char light_on2(b){
	unsigned int a;
	for(a=0;a<20000;a++);
	return TAB[b];	
}
void main(void){
	unsigned char m = 0;unsigned int k = 0;
	P0=0;
	while(1){
		for(k=0;k<8;k++) {
			m = light_on1(m);
			P0 = m;
		}
		for(k=0;k<16;k++)P0 = light_on2(k);	
	}
}

