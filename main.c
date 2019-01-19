#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"
#include "rsa.h"

//#define __DEBUG__
#define _RSA


int main(int argc, char** argv) {

	BigInt num1;
	BigInt num2;
	BigInt num3;
//	BigInt* ret;

#ifdef _BIGNUM
	char number1[MAX], number2[MAX];
	char number3[MAX];

	scanf("%s",number1);
	scanf("%s", number2);
	scanf("%s", number3);

	strcpy(num1.num,number1);
	num1.sign = '1';
	num1.digit = strlen(num1.num);

	strcpy(num2.num,number2);
	num2.sign = '1';
	num2.digit = strlen(num2.num);
	
	strcpy(num3.num,number3);
	num3.sign = '1';
	num3.digit = strlen(num3.num);

	BigInt result;

	result = exp_mod(num1, num2, num3);
	if(result.sign == '0')
		printf("-%s, %c, %d", result.num,result.sign,result.digit);
	else {
		printf("%s, %c, %d", result.num,result.sign,result.digit);
	}

#endif

//	BigInt midNum,fixNum;
//	BigInt * rst;
//	rst = (BigInt*)malloc(sizeof(BigInt));
//
//	midNum = generatePrime();
//	printf("%s\t%d\n", midNum.num,strlen(midNum.num));
//
//	strcpy(fixNum.num, "2");
//	fixNum.digit = 1;
//	fixNum.sign = '1';
//	printf("%s\t%d\n", fixNum.num,strlen(fixNum.num));
//
//	rst = BigIntAdd(midNum, fixNum);
//	printf("%s\t%d\n", rst->num, rst->digit);

#ifdef _RSA
	char message[MAX], ciphertext[MAX], plaintext[MAX];
	printf("请输入要加密的内容>>>\n");
	scanf("%s", message);
	printf("--------------------------------------------------------------------------------\n");
	publicKey* pub_key;
	privateKey* pri_key;

	pub_key = (publicKey*)malloc(sizeof(publicKey));
	pri_key = (privateKey*)malloc(sizeof(privateKey));

	generate_keys(pub_key, pri_key);
	printf("公钥：\n");
	printf("modules(n):%s\t%c\t%d\n", pub_key->modulus.num, pub_key->modulus.sign, pub_key->modulus.digit);
	printf("public_exp(e):%s\t%c\t%d\n", pub_key->public_exp.num, pub_key->public_exp.sign, pub_key->public_exp.digit);
	printf("私钥：\n");
	printf("modules(n):%s\t%c\t%d\n", pri_key->modulus.num, pri_key->modulus.sign, pri_key->modulus.digit);
	printf("private_exp(d):%s\t%c\t%d\n", pri_key->private_exp.num, pri_key->private_exp.sign, pri_key->private_exp.digit);
	printf("--------------------------------------------------------------------------------\n");
	printf("加密后：\n");
	encrypt(message, ciphertext, pub_key);
	printf("密文：%s\n", ciphertext);
	printf("--------------------------------------------------------------------------------\n");
	printf("解密后：\n");
	decrypt(ciphertext, plaintext, pri_key);
	printf("明文：%s\n", plaintext);
#endif
	return 0;
}
