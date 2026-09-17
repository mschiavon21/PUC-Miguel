#include "veiculos_c.h"
int main(void) {
    int nb=0,n=0; Veiculo *base=lerCsv("/tmp/veiculos.csv",&nb); if(!base)return 1;
    Veiculo *arr=malloc((size_t)nb*sizeof(Veiculo)), *out=malloc((size_t)nb*sizeof(Veiculo));
    int id,min=2147483647,max=-2147483647;
    while(scanf("%d",&id)==1&&id!=-1){Veiculo*v=buscar(base,nb,id);if(v){arr[n++]=*v;if(v->cilindros<min)min=v->cilindros;if(v->cilindros>max)max=v->cilindros;}}
    if(n>0){
        int range=max-min+1; int *count=calloc((size_t)range,sizeof(int));
        for(int i=0;i<n;i++)count[arr[i].cilindros-min]++;
        for(int i=1;i<range;i++)count[i]+=count[i-1];
        for(int i=n-1;i>=0;i--){int k=arr[i].cilindros-min;out[--count[k]]=arr[i];}
        char buffer[1200];for(int i=0;i<n;i++){formatVeiculo(&out[i],buffer);printf("%s\n",buffer);}free(count);
    }
    free(arr);free(out);free(base);return 0;
}
