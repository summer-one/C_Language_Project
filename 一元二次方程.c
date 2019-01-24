#include <stdio.h>
#include <math.h>
#include<stdlib.h>
int main(void)
{
int a, b, c; //定义一元二次方程的三个数值；
printf("请依次输入一元二次方程的三个参数a b c，中间以空格隔开\n");
scanf("%d %d %d", &a, &b, &c); //依次输入一元二次方程的三个参数
double delta = b*b - 4*a*c; //定义delta的值为b*b - 4*a*c
double x1 = (-b + sqrt(delta))/(2 * a);
double x2 = (-b - sqrt(delta))/(2 * a);
if (delta>0) //delta大于0时，方程有两个解
{
printf("一元二次方程有两个解\n");
printf("一元二次方程的第一个解，x1 = %f\n",x1);
printf("一元二次方程的第二个解，x2 = %f\n",x2);
}
else if (delta ==0) //delta等于0，方程有两个相同的解
{
printf("一元二次方程有两个相同的解\n");
printf("一元二次方程的解为x1 = x2 =%f\n",x1);
}
else //delta小于0时，方程没有解
{
printf("一元二次方程没有解\n");
}
system("pause");
return 0;
}
