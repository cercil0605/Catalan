//oppai is good
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define KETA 1000

typedef struct NUMBER
{
	int n[KETA];//�e���̒l
	int sign;//�����ϐ�
}Number;

int setSign(Number*, int);
int getSign(Number*);
void clearByZero(Number*);
void dispNumber(Number*);
int zeroNumber(Number*);
void dispNumberZeroSuppress(Number*);
int isZero(Number*);
void setRnd(Number*, int);
void copyNumber(Number*, Number*);
void getAbs(Number*, Number*);
int mulBy10(Number*, Number*);
int divBy10(Number*, Number*);
int setInt(Number*, int);
int numComp(Number*, Number*);
int getInt(Number*, int*);
void swap(Number*, Number*);
int sub(Number*, Number*, Number*);
int add(Number*, Number*, Number*);
int increment(Number*, Number*);
int decrement(Number*, Number*);
int multiple(Number*, Number*, Number*);
int divide(Number*, Number*, Number*, Number*);
int power(Number*, Number*, Number*);

int setSign(Number* a, int s)
//���{���ϐ�a�̕�����
//s=1�Ȃ琳�ɁCs=-1�Ȃ畉�ɐݒ肵��0��Ԃ�
//����ȊO�Ȃ�G���[�Ƃ���-1��Ԃ�
{
	if (s == 1)
	{
		a->sign = 1;
		return 0;
	}
	else if (s == -1)
	{
		a->sign = -1;
		return 0;
	}
	else
	{
		return -1;
	}
}

int getSign(Number* a)//a��0�Ȃ�1���C���Ȃ�-1��Ԃ�
{
	if (a->sign == 1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void clearByZero(Number* a)//���{���ϐ��̒l���[���N���A���C�������v���X�ɃZ�b�g����
{
	int i;

	for (i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}

	setSign(a, 1);
}

void dispNumber(Number* a)//a��\������
{
	int i;

	if (getSign(a) == 1) 
	{
		printf("+");
	}
	else 
	{
		printf("-");
	}

	for (i = KETA-1; i >= 0; i--) 
	{
		printf("%2d", a->n[i]);
	}
}

int zeroNumber(Number* a)
//���{���ϐ��̏�ʂɂ���0�𐔂���֐�
//
//�߂�l
//���{���ϐ��̏�ʂɂ���0�̐�
{
	int zeroNumber = 0;
	int i;

	for (i = KETA - 1; i >= 0; i--)
	{
		if (a->n[i] == 0)
		{
			zeroNumber++;
		}
		else
		{
			break;
		}
	}

	return zeroNumber;
}

void dispNumberZeroSuppress(Number* a) //�[���T�v���X��dispNumber()
{
	int i;
	int zero = zeroNumber(a);

	if (zero == KETA)
	{
		zero--;
	}


	if (getSign(a) == 1)
	{
		printf("+");
	}
	else
	{
		printf("-");
	}

	for(i = KETA - 1 - zero; i >= 0; i--) 
	{
		printf("%2d", a->n[i]);
	}
}

int isZero(Number* a)
//a���[�������ʂ���
//
//�߂�l
//0�E�E�Ea==0
//-1�E�E�Ea!=0
{
	int i;

	if (getSign(a) == -1)
	{
		return -1;
	}

	for (i = 0; i < KETA; i++)
	{
		if (a->n[i] != 0) {
			return -1;
		}
	}

	return 0;
}

void setRnd(Number* a, int k)//a�̉���k���ɗ����l���Z�b�g����
{
	int i;

	clearByZero(a);

	for (i = 0; i < k; i++) 
	{
		a->n[i] = rand() % 10;
	}

	if (rand() % 2 == 0 || isZero(a) == 0) 
	{
		setSign(a, 1);
	}
	else
	{
		setSign(a,-1);
	}

}

void copyNumber(Number* a, Number* b)//a��b�ɃR�s�[����
{
	int i;

	setSign(b,getSign(a));

	for (i = 0; i < KETA; i++) 
	{
		b->n[i] = a->n[i];
	}
}

void getAbs(Number* a, Number* b)//a�̐�Βl��b�ɕԂ�
{
	copyNumber(a, b);
	setSign(b,1);
}

int mulBy10(Number* a, Number* b)
//a��10�{����b�ɕԂ�
//
//�߂�l
//0�E�E�E����I��
//-1�E�E�E�I�[�o�[�t���[
{
	int i;

	clearByZero(b);

	if (a->n[KETA - 1] != 0) 
	{
		return -1;
	}

	int zero = zeroNumber(a);

	for (i = 0; i < KETA - zero; i++) 
	{
		b->n[i + 1] = a->n[i];
	}

	b->n[0] = 0;
	setSign(b, getSign(a));

	return 0;
}

int divBy10(Number* a, Number* b) 
//a��1/10�{����b�ɕԂ�
//
//�߂�l
//a��10�Ŋ������]��
{
	int i;
	int zero = zeroNumber(a);

	clearByZero(b);

	for (i = 0; i < KETA-1-zero; i++) 
	{
		b->n[i] = a->n[i + 1];
	}

	b->n[KETA - 1 - zero] = 0;
	setSign(b, getSign(a));

	if (getSign(a) == 1) 
	{
		return a->n[0];
	}
	else 
	{
		return (a->n[0] * (-1));
	}
}

int setInt(Number* a, int x)
//���{���ϐ�a��int�^�ϐ�x�̒l��ݒ肷��
//
//�߂�l
//0�E�E�E����I��
//-1�E�E�Ex�̒l��a�ɐݒ肵����Ȃ�����
{
	int i;
	int aLen = KETA;

	clearByZero(a);

	if (x < 0)
	{
		setSign(a, -1);

		for (i = 0; i < 10; i++)
		{
			if (x == 0)
			{
				return 0;
			}
			else if (aLen == 0)
			{
				clearByZero(a);
				return -1;
			}
			a->n[i] = x % 10 * (-1);
			aLen--;
			x = (x - x % 10) / 10;
		}
	}
	else
	{
		for (i = 0; i < 10; i++)
		{
			if (x == 0)
			{
				return 0;
			}
			else if (aLen == 0)
			{
				clearByZero(a);
				return -1;
			}
			a->n[i] = x % 10;
			aLen--;
			x = (x - x % 10) / 10;
		}
	}

	if (x == 0)
	{
		return 0;
	}
	else
	{
		clearByZero(a);
		return -1;
	}
}

int numComp(Number* a, Number* b)
//2�̑��{���ϐ�a,b�̑召���r����
//
//�߂�l
//0�E�E�Ea==b
//1�E�E�Ea>b
//-1�E�E�Ea<b
{
	if (getSign(a) == 1 && getSign(b) == -1)
	{
		return 1;
	}
	else if (getSign(a) == -1 && getSign(b) == 1)
	{
		return -1;
	}
	else if (getSign(a) == 1 && getSign(b) == 1)
	{
		int aZero = zeroNumber(a);
		int bZero = zeroNumber(b);

		if (aZero > bZero)
		{
			return -1;
		}
		else if (aZero < bZero)
		{
			return 1;
		}
		else
		{
			int i;

			for (i = KETA - 1 - aZero; i >= 0; i--)
			{
				if (a->n[i] > b->n[i])
				{
					return 1;
				}
				else if (a->n[i] < b->n[i])
				{
					return -1;
				}
			}

			return 0;
		}
	}
	else
	{
		int aZero = zeroNumber(a);
		int bZero = zeroNumber(b);

		if (aZero > bZero)
		{
			return 1;
		}
		else if (aZero < bZero)
		{
			return -1;
		}
		else
		{
			int i;

			for (i = KETA - 1 - aZero; i >= 0; i--)
			{
				if (a->n[i] > b->n[i])
				{
					return -1;
				}
				else if (a->n[i] < b->n[i])
				{
					return 1;
				}
			}

			return 0;
		}
	}
}

int getInt(Number* a, int* x)
//int�^�ϐ�x�ɑ��{���ϐ�a�̒l��ݒ肷��
//
//�߂�l
//0�E�E�E����I��
//-1�E�E�Ea�̒l��x�ɐݒ肵����Ȃ�����
{
	int i;
	int zero = zeroNumber(a);
	Number intMax, intMin;

	setInt(&intMax, INT_MAX);
	setInt(&intMin, INT_MIN);
	*x = 0;

	if (KETA - zero > 10)
	{
		return -1;
	}
	
	if (numComp(a, &intMax) <= 0 && numComp(a, &intMin) >= 0)
	{
		for (i = KETA - 1 - zero; i >= 0; i--)
		{
			*x = *x * 10 + a->n[i];
		}
		if (getSign(a) == -1)
		{
			*x *= -1;
		}

		return 0;
	}
	else
	{
		return -1;
	}
}

void swap(Number* a, Number* b)//a��b����������
{
	Number c = *a;
	*a = *b;
	*b = c;
}

int add(Number* a, Number* b, Number* c)
//c <- a+b
//
//�߂�l
//0�E�E�E����I��
//-1�E�E�E�I�[�o�[�t���[
{
	int i, d;
	int e = 0;

	clearByZero(c);

	int aSign = getSign(a);
	int bSign = getSign(b);

	if (aSign == 1 && bSign == 1)
	{
		if (isZero(a) == 0)
		{
			copyNumber(b, c);
			return 0;
		}
		else if (isZero(b) == 0)
		{
			copyNumber(a, c);
			return 0;
		}


		for (i = 0; i < KETA; i++)
		{
			d = a->n[i] + b->n[i] + e;
			c->n[i] = d % 10;
			e = d / 10;
		}

		if (e != 0)
		{
			clearByZero(c);
			return -1;
		}

		return 0;
	}
	else if (aSign == 1 && bSign == -1)
	{
		Number d;
		getAbs(b, &d);
		int r = sub(a, &d, c);
		return r;
	}
	else if (aSign == -1 && bSign == 1)
	{
		Number d;
		getAbs(a, &d);
		int r = sub(b, &d, c);
		return r;
	}
	else
	{
		Number d, e;
		getAbs(a, &d);
		getAbs(b, &e);
		int r = add(&d, &e, c);
		if (r == 0)
		{
			setSign(c, -1);
		}
		return r;
	}
}

int sub(Number* a, Number* b, Number* c)
//c <- a-b
//
//�߂�l
//0�E�E�E����I��
//-1�E�E�E�I�[�o�[�t���[
{
	clearByZero(c);

	int i;
	int h = 0;
	int aSign = getSign(a);
	int bSign = getSign(b);

	if (aSign == 1 && bSign == 1)
	{
		if (isZero(a) == 0)
		{
			copyNumber(b, c);
			setSign(c, -1);
			return 0;
		}
		else if (isZero(b) == 0)
		{
			copyNumber(a, c);
			return 0;
		}


		if (numComp(a, b) == 1)
		{
			for (i = 0; i < KETA; i++)
			{
				if (a->n[i] < b->n[i] + h)
				{
					c->n[i] = 10 + a->n[i] - b->n[i] - h;
					h = 1;
				}
				else
				{
					c->n[i] = a->n[i] - b->n[i] - h;
					h = 0;
				}
			}
		}
		else if (numComp(a, b) == -1)
		{
			Number d;
			sub(b, a, &d);
			copyNumber(&d, c);
			setSign(c, -1);
		}

		return 0;
	}
	else if (aSign == 1 && bSign == -1)
	{
		Number d;
		getAbs(b, &d);
		int r = add(a, &d, c);
		return r;
	}
	else if (aSign == -1 && bSign == 1)
	{
		Number d;
		getAbs(a, &d);
		int r = add(&d, b, c);
		if (r == 0)
		{
			setSign(c, -1);
		}
		return r;
	}
	else
	{
		Number d, e;
		getAbs(a, &d);
		getAbs(b, &e);
		int r = sub(&e, &d, c);
		return r;
	}
}

int increment(Number* a, Number* b)
//b <- a+1
{
	Number one;
	int r;

	setInt(&one, 1);
	r = add(a, &one, b);

	return r;
}

int inc(Number* a)
//a+1
{
	Number one, b;
	int r;

	setInt(&one, 1);
	r = add(a, &one, &b);

	if (r == 0)
	{
		copyNumber(&b, a);
	}

	return r;
}

int decrement(Number* a, Number* b)
//b <- a-1
{
	Number one;
	int r;

	setInt(&one, 1);
	r = sub(a, &one, b);

	return r;
}

int multiple(Number* a, Number* b, Number* c)
//c <- a*b
//
//�߂�l
//0�E�E�E����I��
//-1�E�E�E�I�[�o�[�t���[
{
	int i, j, e, h, r;
	Number d,tmpC;

	int aSign = getSign(a);
	int bSign = getSign(b);
	int aZero = zeroNumber(a);
	int bZero = zeroNumber(b);
	
	clearByZero(c);

	if (isZero(a) == 0 || isZero(b) == 0)
	{
		return 0;
	}
	else if (aSign == 1 && bSign == 1)
	{
		clearByZero(&tmpC);

		for (i = 0; i < KETA - bZero + 1; i++)
		{
			h = 0;
			clearByZero(&d);

			for (j = 0; j < KETA - aZero + 1; j++)
			{
				e = a->n[j] * b->n[i] + h;
				if (i + j > KETA - 1 && e != 0)/* a->n[] * b->[i] ���I�[�o�[�t���[*/
				{
					clearByZero(c);
					return -1;
				}

				d.n[i + j] |= e % 10;
				h = (e - e % 10) / 10;
				if (h != 0 && i + j >= KETA - 1)/*�ŏ�ʂ̌��܂Ōv�Z���Ă��Ȃ��J��肪����*/
				{
					clearByZero(c);
					return -1;
				}
			}

			r = add(&tmpC, &d, c);

			if (r == -1)/*���Z�ŃI�[�o�[�t���[*/
			{
				return r;
			}

			copyNumber(c, &tmpC);
		}

		return 0;
	}
	else if (aSign == 1 && bSign == -1)
	{
		getAbs(b, &d);
		r = multiple(a, &d, c);
		if (r == 0)
		{
			setSign(c, -1);
		}
		return r;
	}
	else if (aSign == -1 && bSign == 1)
	{
		getAbs(a, &d);
		r = multiple(&d, b, c);
		if (r == 0)
		{
			setSign(c, -1);
		}
		return r;
	}
	else
	{
		Number f;
		getAbs(a, &d);
		getAbs(b, &f);
		r = multiple(&d, &f, c);
		return r;
	}
}

int divide(Number* a, Number* b, Number* c, Number* d)
//
//c <- a/b
//d <- a%d
//
//�߂�l
//0...����I��
//-1...���鐔��0
{
	Number n, m;

	clearByZero(c);
	clearByZero(d);

	if (isZero(b) == 0)
	{
		return -1;
	}

	int aSign = getSign(a);
	int bSign = getSign(b);

	if (aSign == 1 && bSign == 1)
	{
		copyNumber(a, &n);

		while (1)
		{
			if (numComp(&n, b) == -1)
			{
				copyNumber(&n, d);
				return 0;
			}
			else
			{
				increment(c, &m);
				copyNumber(&m, c);
				sub(&n, b, &m);
				copyNumber(&m, &n);
			}
		}
	}
	else if (aSign == 1 && bSign == -1)
	{
		Number p;
		getAbs(b, &p);
		divide(a, &p, c, d);
		setSign(c, -1);
	}
	else if (aSign == -1 && bSign == 1)
	{
		Number p;
		getAbs(a, &p);
		divide(&p, b, c, d);
		setSign(c, -1);
		setSign(d, -1);
	}
	else
	{
		Number p, q;
		getAbs(a, &p);
		getAbs(b, &q);
		divide(&p, &q, c, d);
		setSign(d, -1);
	}
}

int power(Number* a, Number* b, Number* c)


//
//c <- a^b
//
//�߂�l
//0...����I��
//-1...�I�[�o�[�t���[�܂��̓A���_�[�t���[
//-1...b < 0
{
	clearByZero(c);
	Number one,two,d,gm,tmp,tmp1;
	int r;

	int aZero = isZero(a);
	int bZero = isZero(b);

	if (numComp(b, c) == -1)
	{
		return -2;
	}

	increment(c, &one);

	if (bZero == 0)
	{
		setInt(c, 1);
		return 0;
	}
	if (aZero == 0)
	{
		clearByZero(c);
		return 0;
	}
	
	if (numComp(a, &one) == 0)
	{
		setInt(c, 1);
		return 0;
	}
	if (numComp(b, &one) == 0)
	{
		copyNumber(a, c);
		return 0;
	}

	increment(&one, &two);

	if(b->n[0] % 2 == 0)
	{
		r = multiple(a, a, &tmp);
		if (r == -1)
		{
			clearByZero(c);
			return -1;
		}

		divide(b, &two, &d, &gm);
		r = power(&tmp, &d, c);
		if (r == -1)
		{
			clearByZero(c);
			return -1;
		}

		return 0;
	}
	else
	{
		decrement(b, &tmp1);
		r = power(a, &tmp1, &tmp);
		if (r == -1)
		{
			clearByZero(c);
			return -1;
		}

		r = multiple(a, &tmp, c);
		if (r == -1)
		{
			clearByZero(c);
			return -1;
		}

		return 0;
	}
}

Number logarithm(Number* a){   //���R�ΐ��ł�log   ��p�ΐ��łǂ�����Ă�낤������....
	//log a    b�͂���̌v�Z����
	Number k,c,one,two,res1,res2,res3,res4,res5,res6,result,result1,trash;
	int i=0; //�t���O

	clearByZero(&k);
	clearByZero(&c); //�S�~�|��

	setInt(&one,1);
	setInt(&two,2);

	while(1){

		multiple(&two,&k,&res1); 

		add(&res1,&one,&res2);  //2k+1=res2

		divide(&two,&res2,&res3,&trash); // 2/(2k+1)=res3

		sub(a,&one,&res4); //y-1

		add(a,&one,&res5);  //y+1

		divide(&res4,&res5,&res6,&trash); //res6=(y-1)/(y+1)

		power(&res6,&res2,&result); //(y-1/y+1)^(2k+1)=result

		multiple(&res3,&result,&result1);  //result1=res3*result

		add(&result1,&c,&c); //c+=result1  �����I�ɂ܂����H�H


		if(i>2000){ //���񂵂���ʂ��邩�͗v����
			break;
		}
        i++;
	}

	//������ւ�Ŕ{�������Ă��΂����傤�ɂǂ��Ή������邩�͗v����

	//copyNumber(&c,b); //�v�Z���ʑ��


	return c;  //�Ԃ�l ������


}

Number logarithm10(Number* a){ //log10 a�����߂�  
	Number c,log10,ten,ans,trash,a1;

	clearByZero(&c);
	clearByZero(&log10);
	clearByZero(&ans);

	setInt(&ten,10);

	a1=logarithm(a);
	ten=logarithm(&ten);

	divide(&a1,&ten,&ans,&trash);  //log10 y=(ln y/ln 10)

	//copyNumber(&ans,b); //b�ɓ������R�s�[�I

	return ans; //����I��  �Ԃ�l�͓���(Number�^)
}

int inverseNumber(Number* a,Number* b){ //�t����Number* b �ɕԂ� ���̋t�����[�`����2������
	Number eps,x,y,g,pow1,pow2,pow3,tei1,tei2,tei0,h,j,a1;
	int i,c1,c0,c2;



	c0=isZero(a); //�ŏ���a�ɂ��Ĕ��肵�Ď��s�ł��邩�m���߂�
	if(c0==0){
		printf("�ُ�I��");
		return -1;
	}
	c0=getSign(a);
	if(c0==-1){
		setSign(a,1); //��������+�ɃZ�b�g����
		c2=-1; //���Ƃ�-�̕��������邽�߂�

	}
	
	setInt(&eps,10); //
	setInt(&pow1,10); //10^{-N}��10�̂Ƃ��� N=log10 a�i�����j
	setInt(&tei1,0.2); //�����l���߂鎞�ɕK�v��0.2    �����Ή����ĂȂ�����ǂ����Ŕ{����������
	setInt(&tei0,2); //2.0


	for(i=0;i<8;i++){ //EPS:10^{-8} �t���̎d�g�݂�����������ċN�Ăяo������̂�����	
		divBy10(&eps,&eps);
	}

	a1=logarithm10(a); //N(pow2)=log10 a

	copyNumber(&a1,&pow2);

	setSign(&pow2,-1);  //-N

	power(&pow1,&pow2,&pow3); //10^{-N}�̂Ƃ��������Ă���  pow3<=pow1^(pow2)

	multiple(&tei1,&pow3,&x); //x=0.2*pow(10.0,-(double)((int)log10(a)))�̂Ƃ���

	while(1){
		copyNumber(&x,&y);

		multiple(a,&y,&tei2);  //te2=a*y

		sub(&tei0,&tei2,&h);  //2.0-a*y=h
		
		multiple(&y,&h,&x); //x=y*(2.0-a*y)

		sub(&x,&y,&j);  //j=x-y

		getAbs(&j,&g);   //����	

		c1=numComp(&g,&eps); 

		if(c1==-1){
			break; //g<eps�Ɣ�r���邱�Ƃŏ\���ɐ��m�Ȓl�����ߐ؂��������m�F
		}
		
	}

	if(c2<0){
		setSign(&x,(int)-1); //-�ɃZ�b�g����
	}



	copyNumber(&x,b); //�t����Ԃ��Ƃ����x�i�����j������

	return 0; //����I��



}

int zeta(Number* a,Number* f){ 

	//�[�[�^�֐����߂��
	//f=��(a)
	Number n,b,c,d,one,trash;
	int i=0;


	clearByZero(&n);
	clearByZero(&b);
	clearByZero(&c);
	clearByZero(&d);
	
	setInt(&n,1);
	setInt(&one,1);

	while(1){

		power(&n,a,&b); //n^a=b;
		divide(&one,&b,&c,&trash); //c=1/n^a
		add(&d,&c,&d);  //d=c+d

		inc(&n); //n++
		i++;

		if(i>=120){   //break����܂ł̉񐔂͗v����
			break;
		}
	}
	copyNumber(&d,&b);  //������b�ɃR�s�y

	return 0;
}

Number kensan()
{
	Number value, one, two,four, loop, tmp, tmp1, tmp2,tmp3,Keta,final,trash;
	int i;
	int keta = 3;

	setInt(&two, 2);
	clearByZero(&loop);
	setInt(&Keta,1);
	clearByZero(&value);
    clearByZero(&tmp1);
	clearByZero(&tmp);
	clearByZero(&tmp2);
	clearByZero(&tmp3);
	clearByZero(&final);
    copyNumber(&Keta,&one);
    setInt(&four,4);
    

	for (i = 0; i < keta; i++)  //�����Ȃɂ��Ă񂾂���錅���̊g�傩��
	{
		mulBy10(&Keta, &tmp);
		copyNumber(&tmp, &Keta);
	}

    copyNumber(&one,&loop);  // loop=1
	
	while (1)
	{
		multiple(&two, &loop, &tmp);  //tmp=2*n
        power(&four,&tmp,&tmp2);  //4^{2*n}  ����
		inc(&tmp);  //�C���N�������g  2*n+1
        zeta(&tmp,&tmp1);  //tmp1=��(2*n+1)
        multiple(&tmp1,&loop,&tmp);  //tmp=���q(tmp�����g��񂩂珑�������Ă�����������)

        if (numComp(&Keta, &value) == -1)  //���΂����傤�Ōv�Z�ł��錅�����������ɂȂ����炨���܂�
		{
            break;
		}

        divide(&tmp,&tmp2,&tmp1,&trash);  //tmp1=tmp/tmp2

        add(&value,&tmp1,&tmp3);  //tmp3=value+tmp1
        copyNumber(&tmp3,&value);  //value+=tmp1

        inc(&loop);  //loop++

		}
        sub(&one,&value,&final);  //1-��(....)=final
        return final;   //������Ԃ�
}

Number catalan()
//�J�^�����萔���`�ɂ�苁�߂�
//�߂�l...�J�^�����萔
{
	Number value, a, two, loop, tmp, tmp1, tmp2, Keta;
	int i;
	int keta = 10;

	setInt(&two, 2);
	clearByZero(&loop);
	setInt(&Keta,1);
	clearByZero(&value);

	for (i = 0; i < keta; i++)  //�����Ȃɂ��Ă񂾂���錅���̊g�傩��
	{
		mulBy10(&Keta, &tmp);
		copyNumber(&tmp, &Keta);
	}
	
	while (1)
	{
		multiple(&two, &loop, &tmp);  //tmp=2*n
		inc(&tmp);  //�C���N�������g  2*n+1
		power(&tmp, &two, &tmp1);  //(2*n+1)^2=tmp1


		if (numComp(&Keta, &tmp1) == -1)  //���΂����傤�Ōv�Z�ł��錅�����������ɂȂ����炨���܂�
		{
			return value;
		}


		divide(&Keta, &tmp1, &a, &tmp2);  //a<=Keta/tmp1

		if (loop.n[0] % 2 == 0)  //������Ōv�Z�p�^�[����ύX
		{
			add(&value, &a, &tmp2);  //tmp2=value+a
			copyNumber(&tmp2, &value);  //value=tmp2  ���Ȃ킿value+=a�Ă���
		}
		else
		{
			sub(&value, &a, &tmp2);  //tmp2=value-a
			copyNumber(&tmp2, &value);  //value-=a
		}
		inc(&loop);  //loop++(n++)
		
	}
}



int main(){
	Number C;
	clearByZero(&C);
	C=kensan();
	dispNumber(&C);
}