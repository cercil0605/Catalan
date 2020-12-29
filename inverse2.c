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


