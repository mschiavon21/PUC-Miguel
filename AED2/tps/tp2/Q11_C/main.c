#include "veiculos_c.h"
typedef struct Cel{Veiculo v;struct Cel*prox;}Cel;
typedef struct{Cel*primeiro,*ultimo;int n;}Lista;
static void init(Lista*l){l->primeiro=l->ultimo=NULL;l->n=0;}
static void inserirInicio(Lista*l,Veiculo v){Cel*novo=malloc(sizeof(Cel));novo->v=v;novo->prox=l->primeiro;l->primeiro=novo;if(l->n==0)l->ultimo=novo;l->n++;}
static void inserirFim(Lista*l,Veiculo v){Cel*novo=malloc(sizeof(Cel));novo->v=v;novo->prox=NULL;if(l->n==0)l->primeiro=novo;else l->ultimo->prox=novo;l->ultimo=novo;l->n++;}
static void inserir(Lista*l,Veiculo v,int pos){if(pos==0){inserirInicio(l,v);return;}if(pos==l->n){inserirFim(l,v);return;}Cel*ant=l->primeiro;for(int i=1;i<pos;i++)ant=ant->prox;Cel*novo=malloc(sizeof(Cel));novo->v=v;novo->prox=ant->prox;ant->prox=novo;l->n++;}
static Veiculo removerInicio(Lista*l){Cel*x=l->primeiro;Veiculo v=x->v;l->primeiro=x->prox;if(--l->n==0)l->ultimo=NULL;free(x);return v;}
static Veiculo removerFim(Lista*l){if(l->n==1)return removerInicio(l);Cel*ant=l->primeiro;while(ant->prox!=l->ultimo)ant=ant->prox;Veiculo v=l->ultimo->v;free(l->ultimo);l->ultimo=ant;ant->prox=NULL;l->n--;return v;}
static Veiculo remover(Lista*l,int pos){if(pos==0)return removerInicio(l);if(pos==l->n-1)return removerFim(l);Cel*ant=l->primeiro;for(int i=1;i<pos;i++)ant=ant->prox;Cel*x=ant->prox;Veiculo v=x->v;ant->prox=x->prox;free(x);l->n--;return v;}
int main(void){int nb=0;Veiculo*base=lerCsv("/tmp/veiculos.csv",&nb);if(!base)return 1;Lista l;init(&l);int id;char linha[200];
while(scanf("%d",&id)==1&&id!=-1){Veiculo*v=buscar(base,nb,id);if(v)inserirFim(&l,*v);}getchar();int n=0;if(scanf("%d",&n)!=1)n=0;getchar();
for(int i=0;i<n;i++){fgets(linha,sizeof(linha),stdin);trim_newline(linha);char *op=strtok(linha," ");if(strcmp(op,"II")==0){Veiculo*v=buscar(base,nb,atoi(strtok(NULL," ")));if(v)inserirInicio(&l,*v);}else if(strcmp(op,"IF")==0){Veiculo*v=buscar(base,nb,atoi(strtok(NULL," ")));if(v)inserirFim(&l,*v);}else if(strcmp(op,"I*")==0){int pos=atoi(strtok(NULL," "));int vid=atoi(strtok(NULL," "));Veiculo*v=buscar(base,nb,vid);if(v)inserir(&l,*v,pos);}else if(strcmp(op,"RI")==0){Veiculo v=removerInicio(&l);printf("(R) %s %s\n",v.marca,v.modelo);}else if(strcmp(op,"RF")==0){Veiculo v=removerFim(&l);printf("(R) %s %s\n",v.marca,v.modelo);}else if(strcmp(op,"R*")==0){Veiculo v=remover(&l,atoi(strtok(NULL," ")));printf("(R) %s %s\n",v.marca,v.modelo);}}
for(Cel*x=l.primeiro;x;x=x->prox){char b[1200];formatVeiculo(&x->v,b);printf("%s\n",b);}while(l.primeiro)removerInicio(&l);free(base);return 0;}
