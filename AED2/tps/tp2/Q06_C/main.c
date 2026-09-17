#include "veiculos_c.h"
static void radixPass(Veiculo *arr, Veiculo *out, int n, int exp){
    int count[10]={0};
    for(int i=0;i<n;i++) count[(arr[i].ano/exp)%10]++;
    for(int i=1;i<10;i++) count[i]+=count[i-1];
    for(int i=n-1;i>=0;i--){int k=(arr[i].ano/exp)%10;out[--count[k]]=arr[i];}
    for(int i=0;i<n;i++)arr[i]=out[i];
}
int main(void){
    int nb=0,n=0;Veiculo*base=lerCsv("/tmp/veiculos.csv",&nb);if(!base)return 1;
    Veiculo*arr=malloc((size_t)nb*sizeof(Veiculo)),*out=malloc((size_t)nb*sizeof(Veiculo));int id,max=0;
    while(scanf("%d",&id)==1&&id!=-1){Veiculo*v=buscar(base,nb,id);if(v){arr[n++]=*v;if(v->ano>max)max=v->ano;}}
    for(int exp=1;max/exp>0;exp*=10)radixPass(arr,out,n,exp);
    char buffer[1200];for(int i=0;i<n;i++){formatVeiculo(&arr[i],buffer);printf("%s\n",buffer);}
    free(arr);free(out);free(base);return 0;
}
