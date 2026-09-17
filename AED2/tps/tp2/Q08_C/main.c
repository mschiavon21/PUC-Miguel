#include "veiculos_c.h"
static void selection(Veiculo *arr,int n){
    for(int i=0;i<n-1;i++){int m=i;for(int j=i+1;j<n;j++)if(strcmp(arr[j].modelo,arr[m].modelo)<0)m=j;if(m!=i){Veiculo t=arr[i];arr[i]=arr[m];arr[m]=t;}}
}
static int binaria(Veiculo *arr,int n,const char *modelo){int esq=0,dir=n-1;while(esq<=dir){int meio=(esq+dir)/2;int c=strcmp(modelo,arr[meio].modelo);if(c==0)return 1;if(c<0)dir=meio-1;else esq=meio+1;}return 0;}
int main(void){
    int nb=0,n=0;Veiculo*base=lerCsv("/tmp/veiculos.csv",&nb);if(!base)return 1;Veiculo*arr=malloc((size_t)nb*sizeof(Veiculo));
    int id;char linha[512];
    while(scanf("%d",&id)==1&&id!=-1){Veiculo*v=buscar(base,nb,id);if(v)arr[n++]=*v;}
    while(getchar()!='\n'&& !feof(stdin));
    selection(arr,n);
    while(fgets(linha,sizeof(linha),stdin)){trim_newline(linha);if(strcmp(linha,"FIM")==0)break;printf("%s\n",binaria(arr,n,linha)?"SIM":"NAO");}
    free(arr);free(base);return 0;
}
