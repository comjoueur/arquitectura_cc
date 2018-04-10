#include<iostream>
using namespace std;
void binarizar(int a){
	for(int i=31;i>=0;i--){
		cout<<((a>>i)&1);
	}cout<<endl;
}
int multiplicacion_sinsigno(int Q,int M){
    if(!Q || !M)return 0;
    int A=0,cont=0,k=31;
    bool acarreo=0,p,r;
    while(!((Q>>k)&1))k--;
    cont=k+1;
    while(cont>0){
	if(Q&1){
            for(int i=0;i<32;i++){
		    r=(acarreo && !((A>>i)&1))||(!acarreo && ((A>>i)&1));
		    p=(r && !((M>>i)&1))||(!r && ((M>>i)&1));
		    acarreo=((acarreo && ((A>>i)&1))||(acarreo && ((M>>i)&1)))||(((A>>i)&1)&&((M>>i)&1));
		    if(p)A=(A|(1<<i));
		    else A=~((~(A))|(1<<i));
            }
        }
	Q=Q>>1;
	if(A&1)Q=(Q|1<<k);
    	A=A>>1;
    	if(acarreo){
    	    acarreo=0;
    	    A=(A|(1<<k));
   	}
    	cont--;
    }
    A=A<<(k+1);
    for(int i=0;i<32;i++){
    	r=(!((A>>i)&1) && ((Q>>i)&1))||(((A>>i)&1) && !((Q>>i)&1));
	if(r)A=(A|(1<<i));
	else A=~(((~A))|(1<<i));
    }
    return A;
}
int multiplicacion_consigno(int Q,int M,bool g,bool h){
	if(!Q || !M)return 0;
	int A=0;
	bool r,p,q0,q1=0,c1,c2;
	int cant,k=31;
	int n=31;
	while(!((M>>n)&1))n--;
	while(!((Q>>k)&1))k--;
	n++;
	k++;
	if(g)k++;
	if(h)n++;
	k=max(n,k);
	//cout<<k<<endl;
	int cont=k;
	while(cont>0){
		q0=q1;
		q1=Q&1;
		c1=0;
		c2=0;
		if(q1 && !q0){
			for(int i=0;i<k;i++){
				if((M>>i)&1)M=~((~M)|(1<<i));
				else M=M|(1<<i);
			}
			int c=0;
			int i=0;
			while((M>>i)&1 && i<k){
				M=~((~M)|(1<<i));
				i++;
			}
			M=M|(1<<i);
		}
		if(q1 != q0){
			for(int i=0;i<k;i++){
				r=(c2 && !((A>>i)&1))||(!c2 && ((A>>i)&1));
				p=(r && !((M>>i)&1))||(!r && ((M>>i)&1));
				c2=((c2 && ((A>>i)&1))||(c2 && ((M>>i)&1)))||(((A>>i)&1)&&((M>>i)&1));
				if(p)A=(A|(1<<i));
				else A=~((~(A))|(1<<i));
			}
		}
		if(q1 && !q0){
			for(int i=0;i<k;i++){
				if((M>>i)&1)M=~((~M)|(1<<i));
				else M=M|(1<<i);
			}
			int i=0;
			while((M>>i)&1 && i<k){
				M=~((~M)|(1<<i));
				i++;
			}
			M=M|(1<<i);
		}
		Q=Q>>1;
		if(A&1){
			Q=Q|(1<<(k-1));
		}
		A=A>>1;
		if((A>>(k-2))&1){
			A=A|(1<<(k-1));
		}
		cont--;
		//cout<<"cal2"<<endl;
		//cout<<"A: "; binarizar(A);
		//cout<<"Q: "; binarizar(Q);
		//cout<<"M: "; binarizar(M);
	}
	A=A<<(k);
	//binarizar(A);
	//binarizar(Q);
	for(int i=0;i<32;i++){
        	r=(!((A>>i)&1) && ((Q>>i)&1))||(((A>>i)&1) && !((Q>>i)&1));
        	if(r)A=(A|(1<<i));
        	else A=~(((~A))|(1<<i));
    	}
	//binarizar(A);
	return A;
}
int main(){
	for(int i=0;i<1000;i++){
		for(int j=0;j<1000;j++){
			if(i*j!=multiplicacion_sinsigno(i,j) || i*j!=multiplicacion_consigno(i,j,1,1))cout<<"error"<<endl;
		}
	}
	return 0;
}
