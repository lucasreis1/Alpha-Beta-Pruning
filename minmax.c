#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX INT_MAX
#define MIN INT_MIN

typedef struct tree{
	int v;
	struct tree **filhos;
	int numf;
	int depth;
}node;

void add_arvore(node **t);
int minmax(node *t,int alpha,int beta,int max);
int maximo(int a,int b);
int minimo(int a,int b);
void free_tree(node *t);

int main()
{
	node *t,*teste;
	t = NULL;
	add_arvore(&t);
	minmax(t,MIN,MAX,1);
	free_tree(t);
	return 0;
}

void add_arvore(node **t)
{
	if(!(*t))
	{
		(*t) = (node *)malloc(sizeof(node));
		(*t)->numf = 0;
		(*t)->depth = 0;
		(*t)->v = 0;
		(*t)->filhos = NULL;
	}
	int valor;
	scanf("%d",&valor);
	while(valor != 0)
	{
		if(valor < 0)
		{
			(*t)->numf++;
			if(!(*t)->filhos)
			{
				node **filhos;
				filhos = (node **)malloc(sizeof(node));
				(*t)->filhos = filhos;
			}
			else
				(*t)->filhos = (node**)realloc((*t)->filhos,((*t)->numf+1)*sizeof(node));
			node *son;
			son = NULL;
			add_arvore(&son);
			(*t)->filhos[(*t)->numf-1] = son;
			int max,i;
			max = MIN;
			for(i=0;i<(*t)->numf;i++)
				if((*t)->filhos[i]->depth > max)
					max = (*t)->filhos[i]->depth;
			(*t)->depth = max+1;
		}
		else{
			(*t)->v = valor;
			break;
		}
		scanf("%d",&valor);
	}
}

void free_tree(node *t)
{
	if(t->filhos)
	{
		int i;
		for(i=0;i<t->numf;i++)
			free_tree(t->filhos[i]);
		free(t->filhos);
	}
	free(t);
}

int minmax(node *t,int alpha,int beta,int max)
{
	if(!t->depth)
		return t->v;
	int i;
	if(max)
	{
		t->v = MIN;
		for(i=0;i<t->numf;i++)
		{
			t->v = maximo(t->v,minmax(t->filhos[i],alpha,beta,0));
			alpha = maximo(t->v,alpha);
			printf("depth => %d // v value => %d // alpha value => %d // beta value => %d\n",t->depth,t->v,alpha,beta);
			if(alpha >= beta)
				break;
		}
		return t->v;
	}
	else
	{
		t->v = MAX;
		for(i=0;i<t->numf;i++)
		{
			t->v = minimo(t->v,minmax(t->filhos[i],alpha,beta,1));
			beta = minimo(t->v,beta);
			printf("depth => %d // v value => %d // alpha value => %d // beta value => %d\n",t->depth,t->v,alpha,beta);
			if(alpha >= beta)
				break;
		}
		return t->v;
	}
}

int maximo(int a,int b)
{
	return a>=b? a:b;
}

int minimo(int a,int b)
{
	return a<=b? a:b;
}