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
    return a1;  //答えを返すお
}