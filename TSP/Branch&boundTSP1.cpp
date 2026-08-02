#include <stdio.h>

typedef struct{
	float do_dai;
	int dau,cuoi,PA;
}canh;

typedef struct{
	int n;
	canh C[100][100];
}DoThi;

canh result[100];

void Read_Data(DoThi *G){
	FILE *f;
	f=fopen("TSP.txt","r");
	if(f==NULL){
		printf("Loi mo file!\n");
		return ;
	}
	fscanf(f,"%d",&G->n);
	
	int i,j;
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++){
			fscanf(f,"%f",&G->C[i][j].do_dai);
			G->C[i][j].dau=i;
			G->C[i][j].cuoi=j;
			G->C[i][j].PA=0;
		}
	fclose(f);
}

void Print_Data(DoThi *G){
	int i,j;
	printf("Ma tran trong so cua do thi G:\n");
	for(i=0;i<G->n;i++){
		for(j=0;j<G->n;j++)
			printf("%c%c = %5.2f ",G->C[i][j].dau+97,G->C[i][j].cuoi+97,G->C[i][j].do_dai);
		printf("\n");
	}
}

void reset(DoThi *G){
	int i,j;
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++)
			G->C[i][j].PA=0;
}

int co_chu_trinh(canh x[], int STT, int d_cuoi){
	int i;
	for(i=0;i<STT;i++)
		if(d_cuoi==x[i].dau)
			return 1;
	return 0;
}

float CanDuoi(DoThi *G, float cost, int so_canh_hien_tai){
	int i,j;
	float min = 3.4028235e+38;
	for(i=0;i<G->n;i++)
		for(j=0;j<G->n;j++)
			if(G->C[i][j].do_dai<min)
				min=G->C[i][j].do_dai;
	return cost + (G->n-so_canh_hien_tai)*min;
}

void CapNhat(DoThi *G,float cost, float *GNNTT, canh x[]){
	x[G->n-1] = G->C[ x[G->n-2].cuoi ][ x[0].dau ];
	cost+= x[G->n-1].do_dai;
	
	int i;
	if(cost<*GNNTT){
		*GNNTT=cost;
		for(i=0;i<G->n;i++)
			result[i] = x[i];
	}
}

void NhanhCan(DoThi *G, int STT, int d_dau, float giaPA, float *GNNTT, canh x[]){
	int d_cuoi;
	for(d_cuoi=0;d_cuoi<G->n;d_cuoi++){
		if(d_cuoi!=d_dau && !G->C[d_dau][d_cuoi].PA && !co_chu_trinh(x, STT, d_cuoi)){
			float cost=giaPA + G->C[d_dau][d_cuoi].do_dai;
			float c_duoi = CanDuoi(G, cost, STT+1);
			
			if(c_duoi<*GNNTT){
				x[STT] = G->C[d_dau][d_cuoi];
				G->C[d_dau][d_cuoi].PA=1;
				G->C[d_cuoi][d_dau].PA=1;
				
				if(STT == G->n-2)
					CapNhat(G,cost,GNNTT,x);
				else
					NhanhCan(G,STT+1,d_cuoi,cost,GNNTT,x);
				G->C[d_dau][d_cuoi].PA=0;
				G->C[d_cuoi][d_dau].PA=0;
			}
		}
	}
}

void InKetQua(canh result[], int n){
	int i;
	float tong=0.0;
	printf("Cac canh phuong an:\n");
	for(i=0;i<n;i++)
		printf("%c%c = %5.2f\n",result[i].dau+97,result[i].cuoi+97,result[i].do_dai);
	
	printf("\nPhuong an la duong da di qua cac dinh:\n");
	for(i=0;i<n;i++){
		printf("%c -> ",result[i].dau+97);
		tong+=result[i].do_dai;
	}
	printf("%c\n",result[0].dau+97);
	
	printf("Tong do dai = %5.2f\n",tong);
}

int main(){
	DoThi G;
	printf("Phuong an TSP dung thuat toan NHANH CAN:\n");
	Read_Data(&G);
	canh x[G.n];
	Print_Data(&G);
	
	
	while(1){
		printf("\n");
		reset(&G);
		float GNNTT = 3.40282e+38;
		char s;
		
		do{
			printf("Chon 1 dinh de bat dau (a...%c): ",G.n-1+97);
			scanf(" %c",&s);
		}while(s < 'a' || s > 'a'+G.n-1);
		
		NhanhCan(&G, 0, s-97, 0, &GNNTT, x);
		InKetQua(result,G.n);
		
		do{
			printf("Tiep tuc (Y/N)?");
			scanf("\n%c",&s);
			if(s == 'n' || s == 'N')
				return 0;
		} while( s != 'y' && s != 'Y');
	}
	
	return 0;
}