//oppai is good
int inverseNumber(Number* a,Number* b){ //逆数をNumber* b に返す この逆数ルーチンは2次収束
	Number eps,x,y,g,pow1,pow2,pow3,tei1,tei2,tei0;
	int i,c1,c0,c2;
	//pow2=N(=log10 a)なので多倍長でのlog関数をつくらなきゃ実装できん

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
	
	setInt(eps,10); //
	setInt(pow1,10); //10^{-N}の10のところ N=log10 a（引数）
	setInt(tei1,0.2); //初期値決める時に必要な0.2
	setInt(tei0,2.0); //2.0


	for(i=0;i<8;i++){ //EPS:10^{-8} 逆数の仕組みが完成したら再起呼び出しするのもあり	
		divBy10(eps,10);
	}
	power(pow1,pow2,pow3); //10^{-N}のところをやっておく

	multiple(tei1,pow3,x); //x=0.2*pow(10.0,-(double)((int)log10(a)))のところ

	while(1){
		y=x;
		
		multiple(y,sub(tei0,multiple(a,y,tei2)),x); //x=y*(2.0-a*y)

		getAbs(x-y,g);

		c1=numComp(g,eps); 

		if(c1==-1){
			break; //g<epsと比較することで十分に正確な値を求め切ったかを確認
		}
		
	}

	if(c2<0){
		setSign(x,-1); //-にセットする
	}



	b=x; //逆数を返すところにx（答え）を入れる

	return 0; //正常終了



}