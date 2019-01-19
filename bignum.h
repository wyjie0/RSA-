#ifndef __BIGNUM_H__
#define __BIGNUM_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>

#define MAX 1024

typedef struct biging
{
	char num[MAX];//指向长整数数组（序号0中保存着最高位） 
	char sign;//符号（1表示正数，-1表示负数） 
	int digit;//保存该数的位数 
} BigInt;

//加法运算 
BigInt BigIntAdd(BigInt num1, BigInt num2);

//减法运算
BigInt BigIntSub(BigInt num1, BigInt num2);

//乘法运算
BigInt BigIntMul(BigInt num1, BigInt num2); 

//除法运算 
BigInt BigIntDiv(BigInt num1, BigInt num2);

//模余运算
BigInt BigIntMod(BigInt num1, BigInt num2);  

#endif
