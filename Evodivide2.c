int divide(Number* a, Number* b, Number* c, Number* d)
//
//c <- a/b
//d <- a%d
//
//戻り値
//0...正常終了
//-1...割る数が0
{
	Number n, m,d,e;

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
		copyNumber(a, &n);  //n=a

		while (1)
		{
			if (numComp(&n, b) == -1)
			{
				copyNumber(&n, d);
				return 0;
			}
			else
			{
                

	
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
