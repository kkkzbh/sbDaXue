


#include<stdio.h>
#include<stdlib.h>


#define MAXN 1000
#define D 20


void Scanf(int x[MAXN][D],int n,int d) {
	int i,j;
	for(i = 0;i<n; i++) {
		for(j=0;j<d; j++) {
			scanf("%d",&x[i][j]);
		}
	}
}

void Dot(int x[MAXN],int y[MAXN][MAXN],int n,int d) {
	int i,j;
	for(i = 0; i<n; i++) {
		for(j = 0; j<n; j++) {
			y[i][j] *= x[i];
		}
	}
}

void T(int x[MAXN][D],int y[D][MAXN],int n,int d) {
	int i,j;
	for(i = 0; i<n; i++) {
		for(j=0; j<d; j++) {
			y[j][i] = x[i][j];
		}
	}
}

int (*Mul(int x[MAXN][D],int y[D][MAXN],int n,int d))[MAXN][MAXN] {
	int (*p)[MAXN][MAXN] = (int (*)[MAXN][MAXN])malloc(sizeof(int [MAXN][MAXN]));
	int i,j,m;
	for(i = 0; i<n; i++) {
		int sum = 0;
		for(m=0; m<n; m++) {
			sum = 0;
			for(j = 0; j<d; j++) {
				sum += x[i][j] * y[j][m];
			}
			(*p)[i][m] = sum;
		}
		
	}
	return p;
}

int (*MUL(int x[MAXN][MAXN],int y[MAXN][D],int n,int d))[MAXN][D] {
	int (*p)[MAXN][D] = (int (*)[MAXN][D])malloc(sizeof(int [MAXN][D]));
	int i,j,m;
	for(i = 0; i<n; i++) {

		for(m=0; m<d; m++) {
			int sum = 0;
			for(j=0; j<n; j++) {
				sum += x[i][j] * y[j][m];
			}
			(*p)[i][m] = sum;
		}
	}
	return p;
}

int main() {

	int n,d;
	scanf("%d %d",&n,&d);
	int Q[MAXN][D] = {0};
	int K[MAXN][D] = {0};
	int V[MAXN][D] = {0};
	Scanf(Q,n,d);
	Scanf(K,n,d);
	Scanf(V,n,d);
	int W[MAXN] = {0};
	int i = 0;
	int j = 0;
	for(i=0; i<n; i++) {
		scanf("%d",&W[i]);
	}
	int KT[D][MAXN] = {0};
	T(K,KT,n,d);
	int (*p1)[MAXN][MAXN] = Mul(Q,KT,n,d);
	Dot(W,(int (*)[MAXN])p1,n,d);
	int (*p2)[MAXN][D] = MUL((int (*)[MAXN])p1,V,n,d);

	for(j = 0; j<n; j++) {

		for(i=0; i<d; i++) {
			printf("%d",(*p2)[j][i]);
			if(i != d-1) printf(" ");
		}
		printf("\n");
	}

	return 0;
}
