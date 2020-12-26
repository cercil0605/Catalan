Number kensan()
{
	Number value, one, two,four, loop, tmp, tmp1, tmp2,tmp3,Keta,final;
	int i;
	int keta = 3;

	setInt(&two, 2);
	clearByZero(&loop);
	setInt(&Keta,1);
	clearByZero(&value);
    clearByZero(&ans);
    copyNumber(&Keta,&one);
    setInt(&four,4);
    

	for (i = 0; i < keta; i++)  //ここなにしてんだろ入る桁数の拡大かや
	{
		mulBy10(&Keta, &tmp);
		copyNumber(&tmp, &Keta);
	}

    copyNumber(&one,&loop);  // loop=1
	
	while (1)
	{
		multiple(&two, &loop, &tmp);  //tmp=2*n
        pow(&four,&tmp,tmp2);  //4^{2*n}  分母
		inc(&tmp);  //インクリメント  2*n+1
        zeta(&tmp,&tmp1);  //tmp1=ζ(2*n+1)
        multiple(&tmp1,&loop,tmp);  //tmp=分子(tmpもう使わんから書き換えてもっかいつかう)

        if (numComp(&Keta, &value) == -1)  //たばいちょうで計算できる桁数超えそうになったらおしまい
		{
            break;
		}

        divide(&tmp,&tmp2,&tmp1,&trash);  //tmp1=tmp/tmp2

        add(&value,&tmp1,tmp3);  //tmp3=value+tmp1
        copyNumber(&tmp3,&value);  //value+=tmp1

        inc(&loop);  //loop++

		}
        sub(&one,&value,&final);  //1-Σ(....)=final
        return final;   //答えを返す
}
