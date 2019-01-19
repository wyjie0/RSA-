//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <typeinfo.h>

#include "bignum.h"

//�ӷ�����ʵ��
BigInt BigIntAdd(BigInt num1, BigInt num2) {
//	printf("������\n");
//	printf("num1:strlen(num1.num)==%d	 num1.num==%s  num1.sign==%c  num1.digit==%d\n",strlen(num1.num),num1.num, num1.sign, num1.digit);
//	printf("num2:%d  %s  %c  %d\n",strlen(num1.num),num2.num, num2.sign, num2.digit);

	BigInt result;
	//������
	if(num1.sign == '0' && num2.sign == '1') {
		num1.sign = '1';
		result = BigIntSub(num2, num1);
		return result;
	}
	//�����Ӹ���
	if(num1.sign == '1' && num2.sign == '0') {
		num2.sign = '1';
		result = BigIntSub(num1, num2);
		return result;
	}

	int i, k, carry;
	carry = 0;		//�����λ
//	printf("result:%d\t%s\t%c\t%d\n",strlen(result.num),result.num, result.sign, result.digit);
//	printf("�任ǰnum1:%s  %c  %d\n",num1.num, num1.sign, num1.digit);
//	printf("�任ǰnum2:%s  %c  %d\n",num2.num, num2.sign, num2.digit);
	if(num2.digit > num1.digit) {
		BigInt temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
//	printf("�任��num1:%s  %c  %d\n",num1.num, num1.sign, num1.digit);
//	printf("�任��num2:%s  %c  %d\n",num2.num, num2.sign, num2.digit);
	result.sign = num1.sign;		//�������
	result.digit = num1.digit;
	result.num[0] = '\0';
	//�����������Ƶ����������
	strcpy(result.num, num1.num);
//	result.num[result.digit] = '\0';
//	printf("result:%d  %s  %c  %d\n",strlen(result.num),result.num, result.sign, result.digit);
//	result.digit = num1.digit;

	//��num2����0λ
	int preDigit = num2.digit;
	for(int j = 0; j < num1.digit - preDigit; j++) {
		for(int i = num2.digit-1; i >=0; i--) {
			num2.num[i + 1] = num2.num[i];
		}
		num2.digit += 1;
		num2.num[0] = '0';
	}
	num2.digit = preDigit;
	num2.num[num1.digit] = '\0';
//	printf("����0��num2:%d  %s  %c  %d\n",strlen(num1.num),num2.num, num2.sign, num2.digit);

	for(i = num1.digit - 1,k = 0; i >= num1.digit-num2.digit; i--,k++) {
		//����Ӧλ�����ͽ�λ�����
		char midData;
		int ret = (num1.num[i]-'0')+ (num2.num[i] - '0') + carry;
		carry = ret / 10;
		midData = (ret%10 + '0');
		result.num[k] = midData;//����洢
//		printf("i==%d   k== %d   %c\n",i, k,result.num[k]);
	}
//	printf("һ�ּӷ�����result:%d  %s  %c  %d\n",strlen(result.num),result.num, result.sign, result.digit);
	while(carry) {
		if(i < 0) {
			result.num[result.digit] = '1';
			result.digit += 1;
			result.num[result.digit] = '\0';
			break;
//			for(int index = num1.digit - 1; index >= 0; index--){
//				result.num[index + 1] = result.num[index];
//			}
//			result.num[0] = (carry+'0');
//			carry = 0;
		} else {
			int ret = (num1.num[i] - '0') + carry;
			carry = ret / 10;
			result . num[k] = (char)(ret%10 + '0');
			i--;
			k++;
		}
	}
	while(i>=0) {
		result.num[k] = num1.num[i];
		k++;
		i--;
	}
	char number1[MAX];
	for(int j = result.digit - 1,k = 0; j >= 0; j--, k++) {
		number1[k] = result.num[j];
	}
	number1[result.digit] = '\0';
	strcpy(result.num,number1);
	return result;
}

//��������ʵ��
BigInt BigIntSub(BigInt num1, BigInt num2) {

	BigInt result;
	//����������
	if(num1.sign == '1' && num2.sign == '0') {
		num2.sign = '1';
		result = BigIntAdd(num1, num2);
		return result;
	}
	//����������
	if(num1.sign == '0' && num2.sign == '1') {
		num1.sign = '1';
		result = BigIntAdd(num1, num2);
		result.sign = '0';
		return result;
	}
	//����������
	if(num1.sign == '0' && num2.sign == '0') {
		num2.sign = '1';
		num1.sign = '1';
		result = BigIntSub(num2, num1);
		return result;
	}

	int i, k, carry;

	int borrow = 0;		//�����λ
	int convert = 0;//�Ƿ񽻻�����

	//��num2����0λ
	if(num2.digit>num1.digit) {

		BigInt temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
		convert = 1;
	}
	int preDigit = num2.digit;
	for(int j = 0; j < num1.digit - preDigit; j++) {
		for(int i = num2.digit-1; i >=0; i--) {
			num2.num[i + 1] = num2.num[i];
		}
		num2.digit += 1;
		num2.num[0] = '0';
	}
	num2.digit = preDigit;
	num2.num[num1.digit] = '\0';
//	printf("num2����0��%s\n", num2.num);
	//ʼ���ø����������С����
	if(strcmp(num1.num,num2.num) < 0) {
		BigInt temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
		convert = 1;
	}
//	printf("������%s\t%s\n", num1.num, num2.num);
	//�����������Ƶ����������
	result.sign = num1.sign;		//�������
	result.digit = num1.digit;
	strcpy(result.num, num1.num);
//	printf("num1��ֵ��result��\n%s\t%c\t%d\n",result.num,result.sign,result.digit);

	for(i = num1.digit - 1,k = 0; i >= 0; i--,k++) {
		//����Ӧλ�����ͽ�λ�����
//		char midData;
		int trans;

		if(borrow) {
			//����н�λ
			trans = (num1.num[i]-'0') - 1;//��λ�����ȼ�1
			if(trans >= (num2.num[i] - '0')) {
				int ret = trans - (num2.num[i] - '0');
				result.num[k] = ret + '0';
				borrow = 0;
			} else {
				int ret = trans - (num2.num[i] - '0') + 10;
				result.num[k] = ret + '0';
				borrow = 1;
			}
		} else {
			//û�н�λ
			if((num1.num[i]-'0') >= (num2.num[i] - '0')) {
				int ret = (num1.num[i]-'0') - (num2.num[i] - '0');
				result.num[k] = ret + '0';
				borrow = 0;
			} else {
				int ret = (num1.num[i]-'0') - (num2.num[i] - '0') + 10;
				result.num[k] = ret + '0';
				borrow = 1;
			}
		}
//		printf("result:%s\n", result.num);
	}
	char number1[MAX];
//	for(int j = result.digit - 1,k = 0; j >= 0; j--, k++) {
//		if(convert){
//			if()
//			number1[k] = result.num[j];
//		}
//
//	}
//	number1[result.digit] = '\0';
	strrev(result.num);
//	printf("�������%s\t%d\n", result.num, result.digit);

	//��������
	int zero_prefix_count = 0;
	for(int i = 0; i < result.digit; i++) {
		if(result.num[i] != '0' || i == result.digit-1) {
			zero_prefix_count = i;
			break;
		}
	}
//	printf("zero_prefix_count=%d\n",zero_prefix_count);
	//��������
	char simple[MAX]= {0};
//	printf("simple:%s\n",simple);
	strncpy(simple, result.num+zero_prefix_count,result.digit-zero_prefix_count);
//	printf("simple:%s\n",simple);
	strcpy(result.num, simple);
	result.digit -= zero_prefix_count;
	if(convert) {
		result.sign = '0';
		return result;
	}
	return result;
}

//�˷�����ʵ��
BigInt BigIntMul(BigInt num1, BigInt num2) {
	BigInt result;//���ֵ
//	char * output;
	int i, j, rstDigit;

	//ʼ��ʹnum1������λ�����
	if(num1.digit < num2.digit) {
		BigInt temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}

	rstDigit = num1.digit + num2.digit;
	result.digit = rstDigit;//��ʼ�����ֵ��λ��

	//��ʼ�����ֵ�ķ���
	if(num1.sign == num2.sign) result.sign = '1';
	else result.sign = '0';

	//�����ֵ��ʼ��Ϊ0
	for(int index = 0; index < rstDigit; index++)
		result.num[index] = '0';
	result.num[rstDigit] = '\0';
//	printf("��ʼ��result��%s\t%c\t%d\n", result.num, result.sign, result.digit);
//	printf("��ʼ��num1��%s\t%c\t%d\n", num1.num,num1.sign, num1.digit);
//	printf("��ʼ��num2��%s\t%c\t%d\n", num2.num,num2.sign, num2.digit);
//	for(int k = 0; k < rstDigit; k++){
//		printf("%d ",result.num[k]);
//	}
//	printf("\n");
//	for(int k = 0; k < num1.digit; k++){
//		printf("%d ",num1.num[k]);
//	}
//	printf("\n");
//	for(int k = 0; k < num2.digit; k++){
//		printf("%d ",num2.num[k]);
//	}
//	printf("\n");

	for(i = num2.digit - 1; i >= 0; i--) {
		//�޽�λ�˷�
		for(j = num1.digit - 1; j >= 0; j--) {
			int midData;
			midData = (result.num[i+j+1]-'0')+(num1.num[j]-'0') * (num2.num[i]-'0');
			result.num[i+j+1]  = midData+'0';
//			if((result.num[i+j+1]-'0') < 0)
//				result.num[i+j+1] = result.num[i+j+1] - '0' + 256;
//			printf("midData:%d\tmidData+'0':%d\tresult:%d\n",midData,midData+'0',result.num[i+j+1]);
		}

		//�����λ
		for (j = num1.digit + i; j > i; j--) {
			int carry,remind,mid;
			int trans;
			if((result.num[j]-'0')<0) {
				carry = (result.num[j]+256-'0')/10;
				remind = (result.num[j]+256-'0') % 10;
				if(result.num[j-1]-'0' < 0){
					mid = (result.num[j-1]+256-'0')+carry;
				}else{
					mid = result.num[j-1]-'0'+carry;
				}
			}else{
				carry = (result.num[j]-'0')/10;
				remind = (result.num[j]-'0') % 10;
				if(result.num[j-1]-'0' < 0){
					mid = (result.num[j-1]+256-'0')+carry;
				}else{
					mid = result.num[j-1]-'0'+carry;
				}
			}
			result.num[j-1] = mid+'0';
			result.num[j] = remind+'0';
//			printf("��λ��%d\n", result.num[j]);
		}
//		for(int k = 0; k < result.digit; k++)
//			printf("%c ",result.num[k]);
//		printf("\n----------\n");
	}



	if(result.num[0] == '0') {
		for(i = 0; i < result.digit; i++) {
			result.num[i] = result.num[i+1];
		}
//		strncpy(result.num, result.num+1, result.digit-1);
		result.digit-=1;
	}
	result.num[result.digit] = '\0';
//	printf("λ����%d\n",strlen(result.num));
	return result;

}

//��������ʵ��
BigInt BigIntDiv(BigInt num1, BigInt num2) {
	BigInt result;

	if(num1.sign == num2.sign) result.sign = '1';
	else result.sign = '0';

	if(num1.digit<num2.digit || (num1.digit==num2.digit && strcmp(num1.num,num2.num)<0)) {
		result.num[0] = '0';
		result.digit = 1;
		result.num[1] = '\0';
		return result;
	} else if(!strcmp(num1.num,num2.num)) {
		result.num[0] = '1';
		result.digit = 1;
		result.num[1] = '\0';
		return result;
	} else {
		char quotient[MAX];
		BigInt mid;
		BigInt dividend, divisor;
		dividend = num1;
		divisor = num2;
		int orig_divisor_digit = divisor.digit;
		int first_set_digit = 1;

		for(int i = 0; i <= dividend.digit-divisor.digit; i++)
			quotient[i] = '0';
		quotient[dividend.digit-orig_divisor_digit+1] = '\0';

//		printf("%s\n",quotient);

		while( strcmp(dividend.num,divisor.num)==0||(dividend.digit > orig_divisor_digit)||(dividend.digit == orig_divisor_digit && strcmp(dividend.num, divisor.num) > 0)) {

			//�����������λ�����ڳ�����λ�����ڳ����������μ���0
			if(dividend.digit > orig_divisor_digit) {
				for(int i = orig_divisor_digit,j = 0; j < dividend.digit-orig_divisor_digit; j++,i++) {
					divisor.num[i] = '0';
				}
				divisor.num[dividend.digit] = '\0';
				divisor.digit = dividend.digit;
			}
//			printf("ǰ��dividend:\t%s\t%c\t%d\t\n", dividend.num, dividend.sign, dividend.digit);
//			printf("ǰ��divisor:\t%s\t%c\t%d\t\n", divisor.num, divisor.sign, divisor.digit);
//			for(int in = 0;in < strlen(quotient); in++)
//				printf("%c ", quotient[in]);
//			printf("\n");
//			if(strcmp(dividend.num, divisor.num) == 0) {
//				quotient[0] = '1';
//				strcpy(result.num, quotient);
//				result.digit = 1;
//
//				return result;
//			} else
			if(strcmp(dividend.num, divisor.num) < 0) {
				divisor.digit--;
				divisor.num[divisor.digit] = '\0';
				if (first_set_digit == 1) {
					quotient[dividend.digit-orig_divisor_digit] = '\0';//ȷ���̵�λ��
					first_set_digit = 0;
				}

			}
			first_set_digit = 0;

			mid = BigIntSub(dividend, divisor);

//			printf("mid:%s\n", mid.num);
			strcpy(dividend.num, mid.num);
			int last_digit = divisor.digit;
			dividend.digit = mid.digit;
			dividend.sign = mid.sign;
			divisor = num2;

			quotient[last_digit-orig_divisor_digit] = quotient[last_digit-orig_divisor_digit]+1;
//			printf("��dividend:\t%s\t%c\t%d\t\n", dividend.num, dividend.sign, dividend.digit);
//			printf("��divisor:\t%s\t%c\t%d\t\n", divisor.num, divisor.sign, divisor.digit);
//			for(int in = 0;in < strlen(quotient); in++)
//				printf("%c ", quotient[in]);
//			printf("\n");
//			printf("------------------------------\n");
		}
//		printf("count:%d\n", count);
		strrev(quotient);
		strcpy(result.num, quotient);
		result.digit = strlen(quotient);
//	printf("dividend:%s\t%c\t%d\t\n", dividend.num, dividend.sign, dividend.digit);
	}
	return result;
}

//ģ�ຯ��ʵ��
BigInt BigIntMod(BigInt num1, BigInt num2) {
	//num1Ϊ��������num2Ϊ����������ֵΪ����
	BigInt result;

	int count = 0;
	int mod = 0;

	if(num1.sign=='1' && num2.sign=='1') result.sign = '1';
	else result.sign = '0';

	if(num1.digit<num2.digit || (num1.digit==num2.digit && strcmp(num1.num,num2.num)<0)) {
		strcpy(result.num, num1.num);
		result.digit = num1.digit;
		result.sign = num1.sign;
		return result;
	} else if(!strcmp(num1.num,num2.num)) {
		result.num[0] = '0';
		result.digit = 1;
		result.num[1] = '\0';
		return result;
	} else {

		BigInt mid;
		BigInt dividend, divisor;
		dividend = num1;
		divisor = num2;

		int orig_divisor_digit = divisor.digit;
		int zero_count = 0;

		while( (dividend.digit > orig_divisor_digit)||(dividend.digit == orig_divisor_digit && strcmp(dividend.num, divisor.num) >= 0)) {

			//�����������λ�����ڳ�����λ�����ڳ����������μ���0
			if(dividend.digit > orig_divisor_digit) {
				for(int i = orig_divisor_digit,j = 0; j < dividend.digit-orig_divisor_digit; j++,i++) {
					divisor.num[i] = '0';
				}
				divisor.num[dividend.digit] = '\0';
				divisor.digit = dividend.digit;
			}
//			printf("ǰ��dividend:\t%s\t%c\t%d\t\n", dividend.num, dividend.sign, dividend.digit);
//			printf("ǰ��divisor:\t%s\t%c\t%d\t\n", divisor.num, divisor.sign, divisor.digit);
			if(strcmp(dividend.num, divisor.num) == 0) {
				result.num[0] = '0';
				result.digit = 1;
				result.num[1] = '\0';

				return result;
			} else if(strcmp(dividend.num, divisor.num) < 0) {
				divisor.digit--;
				divisor.num[divisor.digit] = '\0';
			}

			mid = BigIntSub(dividend, divisor);

			strcpy(dividend.num, mid.num);
			dividend.digit = mid.digit;
			dividend.sign = mid.sign;
			divisor = num2;
//			printf("��dividend:\t%s\t%c\t%d\t\n", dividend.num, dividend.sign, dividend.digit);
//			printf("��divisor:\t%s\t%c\t%d\t\n", divisor.num, divisor.sign, divisor.digit);
//			mid = BigIntSub(dividend, divisor);
//			strcpy(dividend.num, mid.num);
//			dividend.digit = mid.digit;
//			count++;

//			printf("dividend:%s\t%c\t%d\t\n", dividend.num, dividend.sign, dividend.digit);
//			printf("divisor:%s\t%c\t%d\t\n", divisor.num, divisor.sign, divisor.digit);
//			printf("mid:%s\t%c\t%d\t\n", mid.num, mid.sign, mid.digit);
		}
//		printf("count:%d\n", count);
		strcpy(result.num, dividend.num);
		result.digit = dividend.digit;
		result.sign = dividend.sign;

//	printf("dividend:%s\t%c\t%d\t\n", dividend.num, dividend.sign, dividend.digit);
	}
	return result;
}

