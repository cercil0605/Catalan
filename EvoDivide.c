int Evodivide(Number* a, Number* b, Number* c, Number* d)
//
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
				return 0;
			}
			else
			{
                copyNumber(b,&f);   //f=b
                setInt(&g,1); //g=1
                while(1){
                    mulBy10(&d,&n);
                    copyNumber(&n,&d);  //d*=10
                    if(numComp(a,&d)==-1){
                        divBy10(&d,&n);
                        copyNumber(&n,&d);  //a>fの最大のf
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
                copyNumber(&n,&a);  //a-f
                add(&c,&g,&n);
                copyNumber(&n,&c);  //c+e
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
