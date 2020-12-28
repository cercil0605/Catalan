Number catalan()
//カタラン定数を定義により求める
//戻り値...カタラン定数
{
	Number value, a, two, loop, tmp, tmp1, tmp2, Keta;
	int i;
	int keta = 10;

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

		printf("b");


		if (numComp(&Keta, &tmp1) == -1)  //たばいちょうで計算できる桁数超えそうになったらおしまい
		{
			break;
		}
		printf("c");


		divide(&Keta, &tmp1, &a, &tmp2);  //a<=Keta/tmp1   ここでketa=8以上になると重くなる

		//dispNumber(&a);
		printf("a\n");

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
