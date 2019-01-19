#ifndef __BIGNUM_H__
#define __BIGNUM_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdint.h>

#define MAX 1024

typedef struct biging
{
	char num[MAX];//ָ���������飨���0�б��������λ�� 
	char sign;//���ţ�1��ʾ������-1��ʾ������ 
	int digit;//���������λ�� 
} BigInt;

//�ӷ����� 
BigInt BigIntAdd(BigInt num1, BigInt num2);

//��������
BigInt BigIntSub(BigInt num1, BigInt num2);

//�˷�����
BigInt BigIntMul(BigInt num1, BigInt num2); 

//�������� 
BigInt BigIntDiv(BigInt num1, BigInt num2);

//ģ������
BigInt BigIntMod(BigInt num1, BigInt num2);  

#endif
