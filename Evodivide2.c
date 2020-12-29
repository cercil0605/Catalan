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