Number kensan(){    //計算の形はできたけど何倍か掛けて、たばいちょうに表示するとこができない
    Number Keta,bunbo,bunshi,one,two,forty,twe4,three,four,eight,six4,n,n8,c1,c2,c3,c0,c4,c5,h,h1,value,twon,tmp;
	int keta=100;

    clearByZero(&bunbo);  
	clearByZero(&bunshi);
	setInt(&one,1);
	setInt(&Keta,1);
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
		
		kaijo(&n8);
		power(&n8,&three,&c3);  //c3=((2*n!))^3

	    copyNumber(&n,&c4);  //c4=n  階乗関数利用のためにコピー
		kaijo(&c4);  //n!
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
		if (numComp(&Keta, &h) == -1)  //たばいちょうで計算できる桁数超えそうになったらおしまい
		{
			break;
		}
		//printf("a\n");



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

	return h;
}