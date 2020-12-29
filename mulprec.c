//oppai is good
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define KETA 1000

typedef struct NUMBER
{
	int n[KETA];//各桁の値
	int sign;//符号変数
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
//多倍長変数aの符号を
//s=1なら正に，s=-1なら負に設定して0を返す
//それ以外ならエラーとして-1を返す
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

int getSign(Number* a)//aが0なら1を，負なら-1を返す
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

void clearByZero(Number* a)//多倍長変数の値をゼロクリアし，符号をプラスにセットする
{
	int i;

	for (i = 0; i < KETA; i++)
	{
		a->n[i] = 0;
	}

	setSign(a, 1);
}

void dispNumber(Number* a)//aを表示する
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
//多倍長変数の上位にある0を数える関数
//
//戻り値
//多倍長変数の上位にある0の数
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

void dispNumberZeroSuppress(Number* a) //ゼロサプレス版dispNumber()
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
//aがゼロか判別する
//
//戻り値
//0・・・a==0
//-1・・・a!=0
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

void setRnd(Number* a, int k)//aの下位k桁に乱数値をセットする
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

void copyNumber(Number* a, Number* b)//aをbにコピーする
{
	int i;

	setSign(b,getSign(a));

	for (i = 0; i < KETA; i++) 
	{
		b->n[i] = a->n[i];
	}
}

void getAbs(Number* a, Number* b)//aの絶対値をbに返す
{
	copyNumber(a, b);
	setSign(b,1);
}

int mulBy10(Number* a, Number* b)
//aを10倍してbに返す
//
//戻り値
//0・・・正常終了
//-1・・・オーバーフロー
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

int mul10E(Number* a,int i){  //10^iした値を引数のところにまんま返す
	Number b;

    while(1){
		mulBy10(a,&b);
		copyNumber(&b,a);
		if(i<=1){
			break;
		}
		i--;
	}

	
	return 0;
}


int divBy10(Number* a, Number* b) 
//aを1/10倍してbに返す
//
//戻り値
//aを10で割った余り
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

int div10E(Number* a,int i){
	Number b;
	while(1){

		divBy10(a,&b);
		copyNumber(&b,a);
		if(i<=1){
			break;
		}
		i--;

	}

	
	return 0;
}


int setInt(Number* a, int x)
//多倍長変数aにint型変数xの値を設定する
//
//戻り値
//0・・・正常終了
//-1・・・xの値がaに設定しきれなかった
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
//2つの多倍長変数a,bの大小を比較する
//
//戻り値
//0・・・a==b
//1・・・a>b
//-1・・・a<b
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
//int型変数xに多倍長変数aの値を設定する
//
//戻り値
//0・・・正常終了
//-1・・・aの値がxに設定しきれなかった
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

void swap(Number* a, Number* b)//aとbを交換する
{
	Number c = *a;
	*a = *b;
	*b = c;
}

int add(Number* a, Number* b, Number* c)
//c <- a+b
//
//戻り値
//0・・・正常終了
//-1・・・オーバーフロー
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
//戻り値
//0・・・正常終了
//-1・・・オーバーフロー
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
int dec(Number* a)
//a-1
{
	Number one, b;
	int r;

	setInt(&one, 1);
	r = sub(a, &one, &b);

	if (r == 0)
	{
		copyNumber(&b, a);
	}

	return r;
}

int multiple(Number* a, Number* b, Number* c)
//c <- a*b
//
//戻り値
//0・・・正常終了
//-1・・・オーバーフロー
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
				if (i + j > KETA - 1 && e != 0)/* a->n[] * b->[i] がオーバーフロー*/
				{
					clearByZero(c);
					return -1;
				}

				d.n[i + j] |= e % 10;
				h = (e - e % 10) / 10;
				if (h != 0 && i + j >= KETA - 1)/*最上位の桁まで計算してもなお繰上りがある*/
				{
					clearByZero(c);
					return -1;
				}
			}

			r = add(&tmpC, &d, c);

			if (r == -1)/*加算でオーバーフロー*/
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
//戻り値
//0...正常終了
//-1...割る数が0
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

int Evodivide(Number* a, Number* b, Number* c, Number* d)
//進化版
//c <- a/b
//d <- a%d
//
//戻り値
//0...正常終了
//-1...割る数が0
{
	Number n, m,f,g,flag;

	clearByZero(c);
	clearByZero(d);
    clearByZero(&flag);


	if (isZero(b) == 0)
	{
		return -1;
	}

	int aSign = getSign(a);
	int bSign = getSign(b);

	if (aSign == 1 && bSign == 1)
	{

		while (1)
		{
			if (numComp(a, b) == -1)  //a<bならおしまい
			{
				copyNumber(a, d);
				break;
			}
			else
			{
                copyNumber(b,&f);   //f=b
                setInt(&g,1); //g=1
                while(1){
                    mulBy10(&f,&n);
                    copyNumber(&n,&f);  //f*=10
                    if(numComp(a,&f)==-1){
                        divBy10(&f,&n);
                        copyNumber(&n,&f);  //a>fの最大のf
                        break;
                    }
                    inc(&flag); //10をかけた回数
                }

                while (1)
                {
                    mulBy10(&g,&n);
                    copyNumber(&n,&g);  //g*=10
                    dec(&flag);
                    if(isZero(&flag)==0){
                        break;  //回数分かけたのでokどすえ
                    }
                }
                sub(a,&f,&n);
                copyNumber(&n,a);  //a-f
                add(c,&g,&n);
                copyNumber(&n,c);  //c+e
			}
		}
	}
	else if (aSign == 1 && bSign == -1)
	{
		Number p;
		getAbs(b, &p);
		Evodivide(a, &p, c, d);
		setSign(c, -1);
	}
	else if (aSign == -1 && bSign == 1)
	{
		Number p;
		getAbs(a, &p);
		Evodivide(&p, b, c, d);
		setSign(c, -1);
		setSign(d, -1);
	}
	else
	{
		Number p, q;
		getAbs(a, &p);
		getAbs(b, &q);
		Evodivide(&p, &q, c, d);
		setSign(d, -1);
	}
	return 0;
}


int power(Number* a, Number* b, Number* c)


//
//c <- a^b
//
//戻り値
//0...正常終了
//-1...オーバーフローまたはアンダーフロー
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

Number logarithm(Number* a){   //自然対数でのlog   常用対数でどうやってやろうかしら....
	//log a    bはそれの計算結果
	Number k,one,two,tmp,tmp1,tmp2,tmp3,tmp4,tmp5,value,Keta,trash;
	int i=0; //フラグ
	int j=0;
	int keta=10;

	clearByZero(&k);  //k=0
	clearByZero(&value); //ゴミ掃除

	setInt(&one,1);
	setInt(&two,2);
	copyNumber(&one,&Keta);  //Keta=one(1)

	for(i=0;i<keta;i++){
		mulBy10(&Keta, &tmp);
		copyNumber(&tmp, &Keta);  //Keta=10^{keta}
	}


	while(1)
	{
		multiple(&k,&two,&tmp);  //tmp=2*k
		inc(&tmp);  //tmp=2*k+1
		decrement(a,&tmp1);  //y-1
		increment(a,&tmp2);  //y+1

		power(&tmp1,&tmp,&tmp3);  //tmp3=(y-1)^{2*k+1}
		multiple(&tmp3,&two,&tmp5);  //tmp5=分子

		power(&tmp2,&tmp,&tmp1);  //tmp1=(y+1)^{2*k+1}
		multiple(&tmp1,&tmp,&tmp4);  //tmp4=分母

		multiple(&Keta,&tmp5,&tmp3);  //tmp3=めっちゃ大きな分子の値

		if(j>5000){
			break;
		}

		divide(&tmp3,&tmp4,&tmp5,&trash);  

		add(&value,&tmp5,&tmp4);
		copyNumber(&tmp4,&value);

		inc(&k);
		j++;
		//printf("f");
	}

	//ここらへんで倍数かけてたばいちょうにどう対応させるかは要検討

	//copyNumber(&c,b); //計算結果代入

	printf("aaaaa");


	return value;  //返り値 こたえ


}

Number logarithm10(Number* a){ //log10 aを求める  
	Number c,log10,ten,ans,trash,a1;

	clearByZero(&c);
	clearByZero(&log10);
	clearByZero(&ans);

	setInt(&ten,10);

	a1=logarithm(a);
	ten=logarithm(&ten);

	divide(&a1,&ten,&ans,&trash);  //log10 y=(ln y/ln 10)

	//copyNumber(&ans,b); //bに答えをコピー！

	return ans; //正常終了  返り値は答え(Number型)
}

int inverseNumber(Number* a,Number* b,int p){ //aの逆数をNumber* b に返す  pは精度 この逆数ルーチンは2次収束
	Number eps,x,y,g,x1,pow1,pow2,pow3,tei1,tei2,tei0,h,j,a1;
	int i,c1,c0,c2;
	int n = KETA - zeroNumber(a); //n = N+1 =log_10(a) / 9 + 1
     //ずらす分の10^p

	c0=isZero(a); //最初にaについて判定して実行できるか確かめる
	if(c0==0){
		printf("異常終了");
		return -1;
	}
	c0=getSign(a);
	if(c0==-1){
		setSign(a,1); //いったん+にセットする
		c2=-1; //あとで-の符号をつけるために
	}

	//初期値セット
	setInt(&eps,1);
	//mul10E(&eps,9); //機械イプシロンのセット ε=1

	setInt(&tei2,2);
	copyNumber(&tei2,&x);

	c1=p-n-1;  //ずらす

	mul10E(&x,c1);  //x=2.0*10^{p-n-1}
	setInt(&tei0,2);
	mul10E(&tei0,p);  //x=y*(2.0-a*y)の2.0も10^p倍する


	while(1){
		copyNumber(&x,&y);  //１つ前のx

		multiple(a,&y,&tei2);  //te2=a*y

		sub(&tei0,&tei2,&h);  //2.0-a*y=h
		
		multiple(&y,&h,&x); //x=y*(2.0-a*y)

		div10E(&x,p);   //ずれてんのでその分直しやす

		sub(&x,&y,&j);  //j=x-y

		getAbs(&j,&g);   //直す	

		if(numComp(&g,&eps)==-1||numComp(&g,&eps)==0){
			break; //g<epsと比較することで十分に正確な値を求め切ったかを確認
		}
	}

	if(c2<0){
		setSign(&x,(int)-1); //-にセットする
	}

	copyNumber(&x,b); //逆数を返すところにx（答え）を入れる

	return 0; //正常終
}

int SampleOFultimatedivide(Number* a,Number* b){  //  a/bした値をbに返す  +しか対応してないお
	Number d,e,f;
	int n=KETA-zeroNumber(a)+3;  //精度=被除数の桁数+3




	inverseNumber(b,&d,n);  //除数の逆数をとる
	multiple(a,&d,&e);   //Q=NX(被除数×除数の逆数)
	div10E(&e,n);

	copyNumber(&e,b);   //答えをbに返す


}
int ultimatedivide(Number* a, Number* b, Number* c)
//
//c <- a/b
//
//戻り値
//0...正常終了
//-1...割る数が0
{
	Number m,d,e;

	int n=KETA-zeroNumber(a)+3;

	clearByZero(c);
	//clearByZero(d);

	if (isZero(b) == 0)
	{
		return -1;
	}

	int aSign = getSign(a);  //被除数の符号取得
	int bSign = getSign(b);  //除数の符号取得

	if (aSign == 1 && bSign == 1) //+の時
	{
		inverseNumber(b,&d,n);  //除数の逆数をとる
		multiple(a,&d,&e);   //Q=NX(被除数×除数の逆数)
		div10E(&e,n);  //ずらす
		copyNumber(&e,c);   //答えをcに返す

			
		}
	else if (aSign == 1 && bSign == -1)  //被除数(+) 除数(-)
	{
		Number p;
		getAbs(b, &p);
		ultimatedivide(a, &p, c);
		setSign(c, -1);
	}
	else if (aSign == -1 && bSign == 1)  //被除数(-) 除数(+)
	{
		Number p;
		getAbs(a, &p);
		ultimatedivide(&p, b, c);
		setSign(c, -1);
	}
	else  //両方とも(-)
	{
		Number p, q;
		getAbs(a, &p);
		getAbs(b, &q);
		ultimatedivide(&p, &q, c);
	}
}

int zeta(Number* a,Number* f){ 

	//ゼータ関数求めるよ
	//f=ζ(a)
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

		if(i>=120){   //breakするまでの回数は要検討
			break;
		}
	}
	copyNumber(&d,&b);  //答えをbにコピペ

	return 0;
}

Number kaijo(Number* a){

    Number a1,b,one,i;

    setInt(&a1,1);
    setInt(&i,1);

    while(1){
        multiple(&a1,&i,&b);  //b=a*i
        copyNumber(&b,&a1);   //a==b    a*=i
        inc(&i);
        if(numComp(&i,a)==1){  //i>aなのでやめようね
            break;
        }
    }
	copyNumber(&a1,a);  //引数のやつにも答えを入れる
    return a1;  //答えを返すお
}

Number kensan(){    //計算の形はできたけど何倍か掛けて、たばいちょうに表示するとこができない
    Number Keta,bunbo,bunshi,one,eps,two,forty,twe4,three,four,eight,six4,n,n8,c1,c2,c3,c0,c4,c5,h,h1,value,twon,tmp;
	int keta=100;

    clearByZero(&bunbo);  
	clearByZero(&bunshi);
	setInt(&one,1);
	setInt(&Keta,1);
	setInt(&eps,1);
	setInt(&two,2);
	setInt(&forty,40);
	setInt(&twe4,24);
	setInt(&three,3);
	setInt(&four,4);
	setInt(&eight,8);
	setInt(&six4,64);
	copyNumber(&one,&n);    //n=1


	mul10E(&Keta,keta);  //Keta=10^{keta}

	while(1){

		multiple(&eight,&n,&n8);  //n8=8*n

		power(&two,&n8,&c1); //c1=2^(8*n)  c1後で使う

		power(&n,&two,&n8); //n8=n^2

	    multiple(&forty,&n8,&c0);   //c0=40*n^2
		multiple(&twe4,&n,&c2);  //c2=24*n
		sub(&c0,&c2,&c3);  //c0-c2=c3
		add(&c3,&three,&c2);  //c2=c3+3   →40*n^2-24*n+3 =c2

		multiple(&two,&n,&n8);  //n8=2*n
		copyNumber(&n8,&twon);  //twon=2*n
		
		kaijo(&n8);  //n8=(2*n)!
		power(&n8,&three,&c3);  //c3=((2*n!))^3

	    copyNumber(&n,&c4);  //c4=n  階乗関数利用のためにコピー
		kaijo(&c4);  //c4=n!
		power(&c4,&two,&c0);  //c0=(n!)^2


		multiple(&c1,&c2,&c4);  //c4=c1*c2
		multiple(&c3,&c0,&c5);  //c5=c0*c3

		//c4*c5=分子


		multiple(&c4,&c5,&bunshi);

		multiple(&bunshi,&Keta,&c4);  //めっちゃ倍数掛ける（正確に計算）
		copyNumber(&c4,&bunshi);
		//ここまでで分子求めた

		power(&n,&three,&c0);  //c0=n^3
		sub(&twon,&one,&c1);  //c1=2*n-1
		multiple(&two,&twon,&c3);   //c3=(2*n)*2=4*n
		kaijo(&c3); //(4*n)!
        power(&c3,&two,&c4);   //c4=(4*n!)^2

		multiple(&c0,&c1,&c5);   //c5=c0*c1=(n^3)*(2*n-1)
		multiple(&c5,&c4,&bunbo);   //bunbo=c5*c4=c5*((4*n!)^2)
		multiple(&six4,&bunbo,&c5);
		copyNumber(&c5,&bunbo);  

		//ここまでで分母求めた  64*n^3*(2*n-1)*[(4*n)!]^2

		ultimatedivide(&bunshi,&bunbo,&h);  //h=Σのところ

		if (numComp(&h, &eps) == -1)  //たばいちょうで計算できる桁数超えそうになったらおしまい
		{
			break;
		}
		//printf("a");



		if(n.n[0]%2==0){  //+もしくは-かをつける

			sub(&value, &h, &h1);  //h1=value-h
			copyNumber(&h1, &value);  //value-=h

		}
		else{
			add(&value, &h, &h1);  //h1=value+h
			copyNumber(&h1, &value);  //value+=h
		}
		//dispNumber(&value);
		//printf("\n");

		inc(&n);


	}

	return value;
}
Number catalan()
//カタラン定数を定義により求める
//戻り値...カタラン定数
{
	Number value, a, two, loop, tmp, tmp1, tmp2, Keta;
	int i;
	int keta = 8;

	setInt(&two, 2);
	clearByZero(&loop);
	setInt(&Keta,1);
	clearByZero(&value);

	for (i = 0; i < keta; i++)  //ここなにしてんだろ入る桁数の拡大かや
	{
		mulBy10(&Keta, &tmp);
		copyNumber(&tmp, &Keta);  //Keta=10^{keta}
	}
	printf("i\n");
	
	while (1)
	{
		multiple(&two, &loop, &tmp);  //tmp=2*n
		inc(&tmp);  //インクリメント  2*n+1
		power(&tmp, &two, &tmp1);  //(2*n+1)^2=tmp1

		//printf("b");


		if (numComp(&Keta, &tmp1) == -1)  //たばいちょうで計算できる桁数超えそうになったらおしまい
		{
			break;
		}
		//printf("c");


		ultimatedivide(&Keta, &tmp1, &a);  //a<=Keta/tmp1   ここでketa=8以上になると重くなる

		//dispNumber(&a);
		//printf("a\n");

		if (loop.n[0] % 2 == 0)  //奇数偶数で計算パターンを変更
		{
			add(&value, &a, &tmp2);  //tmp2=value+a
			copyNumber(&tmp2, &value);  //value=tmp2  すなわちvalue+=aてこと
		}
		else
		{
			sub(&value, &a, &tmp2);  //tmp2=value-a
			copyNumber(&tmp2, &value);  //value-=a
		}
		inc(&loop);  //loop++(n++)
		
	}
	return value;
}


int main(){
	Number C,B,D;
	
	clearByZero(&C);
	C=kensan();
	dispNumber(&C);

	
}