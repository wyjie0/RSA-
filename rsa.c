#include "rsa.h"

//#define __DEBUG__
//求最大公约数
BigInt get_gcd(BigInt num1, BigInt num2) {
	BigInt mod, gcd;
	char end = '0';
	if(num1.digit<num2.digit||(num1.digit==num2.digit && (num1.num, num2.num)<0)) {
		BigInt temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
#ifdef __DEBUG__
//	printf("num1:%s\n", num1.num);
//	printf("num2:%s\n", num2.num);
#endif
	mod = BigIntMod(num1, num2);

#ifdef __DEBUG__
//	printf("mod:%s\t%d\n", mod.num, mod.digit);
//	printf("--------%d\n", mod.num[0] == end);
#endif
	if(mod.num[0] == end) {
		printf("%s\n", num2.num);
		return num2;
	} else {
		return get_gcd(num2, mod);
	}
}

//快速幂模算法
BigInt exp_mod(BigInt num1, BigInt num2, BigInt mode) {
	BigInt sum, rst_mod, rst_div, fixNum;

	strcpy(fixNum.num, "2");
	fixNum.digit = 1;
	fixNum.sign = '1';

	strcpy(sum.num, "1");
	sum.digit = 1;
	sum.sign = '1';

	num1 = BigIntMod(num1, mode);

	while(strcmp(num2.num, "0")>0) {
		
		rst_mod = BigIntMod(num2, fixNum);
//		printf("%s\t%d\n", rst_mod.num,rst_mod.num[0] == '1');
		if(rst_mod.num[0] == '1') {
			BigInt rst_mul;
			sum = BigIntMul(sum, num1);
			sum = BigIntMod(sum, mode);
//			printf("-----------num1:%s\n", num1.num);
//			printf("-----------sum:%s\n", sum.num);
		}
		num2 = BigIntDiv(num2, fixNum);
		BigInt midData;
		midData = BigIntMul(num1, num1);
//		printf("midData:%s\n", midData.num);
		num1 = BigIntMod(midData, mode);
//		printf("num1:%s\n", num1.num);
//		printf("num2:%s\n", num2.num);
//		printf("---------\n");
	}

	return sum;
}

//扩展欧几里得算法
BigInt exEuclid(BigInt num1, BigInt num2) {
	BigInt result, zero, one;
	BigInt x1, x2, x3, y1, y2, y3;

	strcpy(zero.num, "0");
	zero.digit = 1;
	zero.sign = '1';
	strcpy(one.num, "1");
	one.digit = 1;
	one.sign = '1';

	x1 = num1, x2 = one, x3 = zero;
	y1 = num2, y2 = zero, y3 = one;

//	printf("X:%s\t%s\t%s\n", x1.num, x2.num, x3.num);
//	printf("Y:%s\t%s\t%s\n", y1.num, y2.num, y3.num);
	while(strcmp(x1.num, one.num) > 0) {
		if(x1.digit<y1.digit || (x1.digit==y1.digit&&strcmp(x1.num, y1.num) < 0)) {
			BigInt times, mid_2, mid_3;
			times = BigIntDiv(y1, x1);
			y1 = BigIntMod(y1, x1);
			mid_2 = BigIntMul(x2, times);
			y2 = BigIntSub(y2, mid_2);
			mid_3 = BigIntMul(x3, times);
			y3 = BigIntSub(y3, mid_3);
//			printf("X:%s\t%s\t%s\n", x1.num, x2.num, x3.num);
//			printf("Y:%s\t%s\t%s\n", y1.num, y2.num, y3.num);
		}
		if(x1.digit>y1.digit || (x1.digit==y1.digit&&strcmp(x1.num, y1.num) > 0)) {
			BigInt times, mid_2, mid_3;
			times = BigIntDiv(x1, y1);
			x1 = BigIntMod(x1, y1);
			mid_2 = BigIntMul(y2, times);
			x2 = BigIntSub(x2, mid_2);
			mid_3 = BigIntMul(y3, times);
			x3 = BigIntSub(x3, mid_3);
//			printf("X:%s\t%s\t%s\n", x1.num, x2.num, x3.num);
//			printf("Y:%s\t%s\t%s\n", y1.num, y2.num, y3.num);
		}
//		printf("X:%s\t%s\t%s\n", x1.num, x2.num, x3.num);
//		printf("Y:%s\t%s\t%s\n", y1.num, y2.num, y3.num);
	}
	if(strcmp(x1.num, zero.num) == 0)
		result = y2;
	if(strcmp(x1.num, one.num) == 0)
		result = x2;

	return result;
}

//判断是否为素数(未实现)
int detect_prime(BigInt oddNum) {
	char data[MAX];
	int length;

	strcpy(data, oddNum.num);//data即为要判断的数
	length = oddNum.digit;

	return 1;
}

//生成随机的素数(只实现了生成随机的奇数)
BigInt generatePrime() {
	BigInt midNum,fixNum;

	//fixNUM为累加数，值保持为2
	strcpy(fixNum.num, "2");
	fixNum.digit = 1;
	fixNum.sign = '1';

	//生成一个随机的奇数

	for(int i = 0; i < PRIME_DIGIT; i++) {
		if(i == 0) {
			int r = rand()%10+1;
			midNum.num[i] = r+'0';
		} else {
			int r = rand()%10;
			midNum.num[i] = r+'0';
		}
	}
	midNum.num[PRIME_DIGIT] = '\0';
	if((midNum.num[PRIME_DIGIT-1]-'0')%2 == 0) {
		midNum.num[PRIME_DIGIT-1] = midNum.num[PRIME_DIGIT-1]+1;
	}
	midNum.digit = strlen(midNum.num);
	midNum.sign = '1';

	//由生成的奇数产生一个素数(先不忙实现素数)
//	while(!detect_prime(midNum)) {
//		BigInt* rst;
//		rst = (BigInt*)malloc(sizeof(BigInt));
//
//		rst = BigIntAdd(midNum, fixNum);
//		strcpy(midNum.num,rst.num);
//		midNum.digit = rst.digit;
//		midNum.sign = rst.sign;
//	}

	return midNum;
}

//密钥生成函数实现
void generate_keys(publicKey* pub_key, privateKey* pri_key) {
	BigInt p,p_1, q,q_1, midNum, e, d;//p，q为选择的素数，midNum为中间值
	BigInt gcd, phi_n;

	BigInt n;
	FILE *fp;
//#ifdef _WRITE
//	if((fp = fopen("primeNum.txt", "w")) == NULL) {
//		printf("文件打开错误！");
//		exit(1);
//	}
//#endif
	p.sign = '1';
	q.sign = '1';

	//此素数由网上素数生成器生成
	char prim_num_p[51] = "27409488245517115276142322168576189279543123341141";
	char prim_num_q[51] = "84277931986502860248650900613893446066184963788813";
	strcpy(p.num, "27409488245517115276142322168576189279543123341141");
	strcpy(q.num, "84277931986502860248650900613893446066184963788813");
	p.digit = strlen(p.num);
	q.digit = strlen(q.num);

	//生成一个随机的素数
//	p = generatePrime();
//	q = generatePrime();


//#ifdef _WRITE
//	fputs(p.num, fp);
//	fputc('\n',fp);
//	fputs(q.num, fp);
////	fclose(fp);
////	printf("%s\t%c\t%d\n", p.num,p.sign,p.digit);
////	printf("%s\t%c\t%d\n", q.num,q.sign,q.digit);
//#endif


	n = BigIntMul(p, q);

	strcpy(pub_key->modulus.num, n.num);
	pub_key->modulus.digit = n.digit;
	pub_key->modulus.sign = n.sign;

	strcpy(pri_key->modulus.num, n.num);
	pri_key->modulus.digit = n.digit;
	pri_key->modulus.sign = n.sign;

	pri_key->prime_p = p;
	pri_key->prime_q = q;


#ifdef __DEBUG__
	printf("pub_key.modulus:%s\n", pub_key->modulus.num);
	printf("pri_key.modulus:%s\n", pri_key->modulus.num);
	printf("pri_key.prime_p:%s\n", pri_key->prime_p.num);
	printf("pri_key.prime_q:%s\n", pri_key->prime_q.num);
#endif

	BigInt fixNum;
	strcpy(fixNum.num, "1");
	fixNum.digit = 1;
	fixNum.sign = '1';

	p_1 = BigIntSub(p, fixNum);
	q_1 = BigIntSub(q, fixNum);
	phi_n = BigIntMul(p_1, q_1);
//#ifdef _WRITE
//	fputc('\n', fp);
//	fputs(phi_n.num, fp);
//#endif
#ifdef __DEBUG__
	printf("p-1:%s\n", p_1.num);
	printf("q-1:%s\n", q_1.num);
	printf("phi_n:%s\t%c\t%d\n", phi_n.num, phi_n.sign, phi_n.digit);
#endif

	strcpy(e.num, "17");
	e.digit = strlen(e.num);
	e.sign = '1';

	strcpy(pub_key->public_exp.num, e.num);
	pub_key->public_exp.digit = e.digit;
	pub_key->public_exp.sign = e.sign;
	pri_key->public_exp = pub_key->public_exp;

#ifdef __DEBUG__
	printf("pub_key.public_exp:%s\t%c\t%d\n", pub_key->public_exp.num, pub_key->public_exp.sign, pub_key->public_exp.digit);
	printf("pri_key.public_exp:%s\t%c\t%d\n", pri_key->public_exp.num, pri_key->public_exp.sign, pri_key->public_exp.digit);
#endif

//	BigInt phi_n_2;
//	BigInt mid;
//
//	strcpy(mid.num, "2");
//	mid.digit = strlen(mid.num);
//	mid.sign = '1';
//	phi_n_2 = BigIntSub(phi_n, mid);

	d = exEuclid(e, phi_n);
	if(d.sign == '0'){
		d = BigIntAdd(phi_n, d);
	}
	pri_key->private_exp = d;
	
#ifdef __DEBUG__
	printf("d:%s\t%d\n", d.num, d.digit);
	BigInt test, test_mul;
	test_mul = BigIntMul(e, d);
	test = BigIntMod(test_mul, phi_n);
	printf("e=%s\nd=%s,%c\ne*d=%s\t%d\n", e.num,d.num ,d.sign,test_mul.num, test_mul.digit);
//#ifdef _WRITE
//	fputc('\n', fp);
//	fputs(test_mul.num, fp);
//	fclose(fp);
//#endif
//	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	printf("test:%s\n", test.num);
#endif
}

//加密函数实现
void encrypt(char* message, char* ciphertext, publicKey *kpub){
	BigInt mesg, cipher;
	
	strcpy(mesg.num, message);
	mesg.digit = strlen(message);
	mesg.sign = '1';
	printf(">>>>>>>>>>>>>>>>>>%s\n", mesg.num);
	printf("n:%s\n", kpub->modulus);
	cipher = exp_mod(mesg, kpub->public_exp, kpub->modulus);
	
	strcpy(ciphertext, cipher.num);
}

//解密函数实现
void decrypt(char* ciphertext ,char* plaintext, privateKey *kpri){
	BigInt cipher, plain;
	
	strcpy(cipher.num, ciphertext);
	cipher.digit = strlen(cipher.num);
	cipher.sign = '1';
	printf(">>>>>>>>>>>>>>%s\n", cipher.num);
	plain = exp_mod(cipher, kpri->private_exp, kpri->modulus);
	strcpy(plaintext, plain.num);
	printf("n:%s\n", kpri->modulus);
	printf(">>>>>>>>>>>>>>%s\n",plaintext);
}
