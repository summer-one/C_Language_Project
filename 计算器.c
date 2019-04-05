#include <reg51.h>
#include <math.h>
#include <lcd.h>

#define GPIO_KEY P1//薄膜按键所用I/O口，P1^0~P1^7 

unsigned char KeyValue=13;//矩阵键盘按键默认值
unsigned int error=0;//非法运算标志
unsigned int bei=0;//标志变量，若被加（减、乘、除）数未输入，则bei为0
unsigned char x=0;//储存运算符
unsigned int xf=0;//标志变量，若运算符刚被输入，则置为1
unsigned char dan;//储存刚输入的单个数位上的字符型数字
unsigned int y=0;//标志变量，若要输出运算结果则置为1
unsigned char e[9]=" Error!!!";

void LcdDisplay_1(long number);//用于在第一行输出被加减乘除数 
void LcdDisplay_2(long number);//用于在第二行输出结果
void Delay_ms(unsigned int ms);
//void UsartConfiguration();

void main()
{
//	UsartConfiguration();
	LcdInit();			 //初始化LCD1602 
	while(1)
   	{
	    static long key=0,result=0,temp=0,a=0,b=0,c=0,d=0;//设置静态局部变量，可保留上一次运算的值
	    unsigned char i=0;

	    GPIO_KEY=0x0f;
	    if(GPIO_KEY!=0x0f)//读取按键是否按下
		{
			Delay_ms(10);//延时消抖
			if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
			{			
				//测试列
				GPIO_KEY=0X0f;
				switch(GPIO_KEY)
				{
					case(0X07):	KeyValue=0;break;
					case(0X0b):	KeyValue=1;break;
					case(0X0d): KeyValue=2;break;
					case(0X0e):	KeyValue=3;break;
				}
				//测试行
				GPIO_KEY=0Xf0;
				switch(GPIO_KEY)
				{
					case(0X70):	KeyValue=KeyValue+0;break;
					case(0Xb0):	KeyValue=KeyValue+4;break;
					case(0Xd0): KeyValue=KeyValue+8;break;
					case(0Xe0):	KeyValue=KeyValue+12;break;
				}
				while((i<60)&&(GPIO_KEY!=0xf0))	 //松手检测
				{
					Delay_ms(10);
					i++;
				}

				switch (KeyValue)
				{
					//key计算最新键入的值，用temp存放被加（减、乘、除）数，result存放最新键入的值或计算结果
					case  0:dan='1';key=key*10+1;result=key;break;//键入1，dan储存刚输入的单个数位上的数字
		   			case  1:dan='2';key=key*10+2;result=key;break;//键入2
		 			case  2:dan='3';key=key*10+3;result=key;break;//键入3
					case  3:x='+';xf=1;temp=result;key=0;a=1;break;      //选择加法，x储存选择的运算符，选择后xf置为1
					case  4:dan='4';key=key*10+4;result=key;break;//键入4
		 			case  5:dan='5';key=key*10+5;result=key;break;//键入5
					case  6:dan='6';key=key*10+6;result=key;break;//键入6
					case  7:x='-';xf=1;temp=result;key=0;b=1;break; 	 //选择减法，
					case  8:dan='7';key=key*10+7;result=key;break;//键入7
					case  9:dan='8';key=key*10+8;result=key;break;//键入8
					case 10:dan='9';key=key*10+9;result=key;break;//键入9
					case 11:x='*';xf=1;temp=result;key=0;c=1;break; 	 //选择乘法
					case 12:temp=key=result=0;a=b=c=d=0;x=dan=0;xf=y=bei=0;break;//所有清零
					case 13:dan='0';key=key*10+0;result=key;break;//键入0
					case 14:if(a==1) {result=temp+result;a=0;key=0;} 	 //计算运算结果 
							if(b==1) {result=temp-result;b=0;key=0;}
							if(c==1) {result=temp*result;c=0;key=0;}
							if(d==1) 
							{
								if (result==0) 	//若除数为0，运算非法，error置为1
									{error=1;result=0;d=0;key=0;}
								else
									{result=temp/result;d=0;key=0;}				
							}
							y=1;				//将要输出运算结果，则y置为1
							break; 
					case 15:x='/';xf=1;temp=result;key=0;d=1;break;  	 //选择除法
				}

				//LCD显示
		 		if (y==0)//若y为0，则不是输出结果，而是输出等式的左边	
				{
					if (KeyValue==12) LcdWriteCom(0x01);//清零则清屏
					else if(x==0&&bei==0) bei=1,LcdWriteCom(0x01),LcdWriteData(dan);//若x和bei都为0，则当前正开始输入被加（减、乘、除）数，要清屏再输出，同时bei置为1
				 	else if(x==0&&bei==1) LcdWriteData(dan);//若x为0，bei为1，则运算符未选择，即当前仍然在输入被加（减、乘、除）数，继续逐位输出显示
					else if(x!=0&&xf==1) xf=0,bei=0,LcdWriteCom(0x01),LcdDisplay_1(result),LcdWriteData(x);//若x和xf都不为0，则为刚选择运算符，将运算符输出且xf重新置为0，此时被加（减、乘、除）数已输完，bei也要重新置为0
					else if(x!=0&&xf==0) LcdWriteData(dan);//若运算符已选但不是刚选，则当前正输入加（减、乘、除）数，逐位输出显示
				}
				else	 //否则输出结果
				{
					LcdDisplay_2(result);	//输出结果 
					x=0;					//运算符已选，重新置为0
					y=0;					//输出结果后，重新置为0
				}	
			} 
		}
	}
}

void LcdDisplay_1(long number)//在第一行输出被加（减、乘、除）数
{
	int i,n[5]={0};			  //不能设成unsigned
	if (number<0)
		LcdWriteData('-');
	number=abs(number);		  //取绝对值
	if (number-10000>=0) i=5; //判断有效位数
	else if (number-1000>=0) i=4;
	else if (number-100>=0) i=3;
	else if (number-10>=0) i=2;
	else i=1;			
	n[4]=number/ 10000;		  //提取各位上的数
	n[3]=number % 10000 / 1000;
	n[2]=number % 1000 / 100;
	n[1]=number % 100 / 10;
	n[0]=number % 10;
	for (i=i-1;i>=0;i--)	  //若设成unsigned,此处形成死循环！！！
	{
		LcdWriteData(n[i]+48);//输出
	}
}

void LcdDisplay_2(long number)//在第二行输出结果
{
	int i,n[5];				//不能设成unsigned
	//判断运算是否合法
	if (error==1)			//若error为1，则运算非法
	{
		error=0;			//error重新置为0
		LcdWriteCom(0x01);  //清屏
		LcdWriteCom(0x80);  //数据指针返回首位
		for (i=0;i<9;i++)	//输出提示
 			LcdWriteData(e[i]);
		Delay_ms(1500);
		LcdWriteCom(0x01);  //再次清屏
	}
	else					//合法则输出结果
	{
		 LcdWriteData('=');	//先在第一行输出'='
		 LcdWriteCom(0xc0);	//数据指针设置在第二行首位
		 if (number<0)		//负数则输出负号
		 	LcdWriteData('-');
		 number=abs(number);
		 if (number-10000>=0) i=5; //判断有效位数
		 else if (number-1000>=0) i=4;
		 else if (number-100>=0) i=3;
		 else if (number-10>=0) i=2;
		 else i=1;			
		 n[4]=number/10000;
		 n[3]=number%10000/1000;
		 n[2]=number%1000/100;
		 n[1]=number%100/10;
		 n[0]=number%10;
		 for (i=i-1;i>=0;i--)	   //若设成unsigned,此处形成死循环！！！
		 {
			LcdWriteData(n[i]+48);
		 }
	}
/*
	SBUF = '0'+m;	//将接收到的数据放入到发送寄存器
	while (!TI);	//等待发送数据完成
	TI = 0;			//发送完成标志位清零
*/
}

void Delay_ms(unsigned int ms)//延时函数，延时1ms
{
	int j;
	for(;ms>0;ms--)
	  for(j=140;j>0;j--);
}

/*	//此函数适合数码管显示时使用
unsigned int num(long num,unsigned int p)//提取各位上的数
{
    unsigned int i,t,n;
    for(t=1,i=0;i<p;i++)
	{
		n=(abs(num)%(10*t))/t;//计算运算结果的每一位并传递给n显示
	  	t=t*10;
	  	if((num<0)&&(n==0)&&(p>1))
	  	{
	   		n=10; //负数则显示负号
	  	}
	}
	return n;
}
*/

/*
void UsartConfiguration()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
//	ES=1;						//打开接收中断
//	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}
*/
