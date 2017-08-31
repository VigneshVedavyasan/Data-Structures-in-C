//#include "CaseDiaryCurrent.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define N 1000000
#define MAX_DIM 3
#define rand1() (rand()/(double)RAND_MAX)
#define rand_pt(v) { v.x[0]=rand1(); v.x[1] = rand1(); v.x[2] = rand1();}

/* This KD tree code is still not fully constructed.
 * A macro for random number generation has been taken and
 * replaced instead of the original data for the time being.
 * Once complete I will take the flat structure data and insert
 * and the code will fully be able to use the KD tree.
 * Till then this file remains isolated.
 * */

struct node
{
	double x[MAX_DIM];
	struct node *lChild;
	struct node *rChild;
};

inline double dist(struct node *a,struct node *b,int dim)
{
	double t,d=0;
	while(dim--)
	{
		t=a->x[dim]-b->x[dim];
		d+=t*t;
	}
	return d;
}

inline void swap(struct node *x,struct node *y)
{
	double tmp[MAX_DIM];
	memcpy(tmp,x->x,sizeof(tmp));
	memcpy(x->x,y->x,sizeof(tmp));
	memcpy(y->x,tmp,sizeof(tmp));
}

struct node *findMedian(struct node *start,struct node *end,int idx)
{
	if(end<=start)
		return NULL;
	if(end==start+1)
		return start;
	struct node *p,*store,*md = start+(end-start)/2;
	double pivot;
	while(1)
	{
		pivot = md->x[idx];
		swap(md,end-1);
		for(store = p = start;p<end;p++)
		{
			if(p->x[idx]<pivot)
			{
				if(p!=store)
					swap(p,store);
				store++;
			}
		}
		swap(store,end-1);
		if(store->x[idx] == md->x[idx])
			return md;
		if(store>md)
			end = store;
		else
			start = store;
	}
}

struct node *makeTree(struct node *t,int len,int i,int dim)
{
	struct node *n;
	if(!len)
		return 0;
	if((n=findMedian(t,t+len,i)))
	{
		i=(i+1)%dim;
		n->lChild = makeTree(t,n-t,i,dim);
		n->rChild = makeTree(n+1,t+len-(n+1),i,dim);
	}
	return n;
}

int visited;

void nearest(struct node *root,struct node *nd,int i,int dim,struct node **best,double *best_dist)
{
	double d,dx,dx2;
	if(!root)
		return;
	d = dist(root,nd,dim);
	dx = root->x[i]-nd->x[i];
	dx2 = dx*dx;
	visited++;
	if(!*best || d<*best_dist)
	{
		*best_dist = d;
		*best = root;
	}
	if(!*best_dist)
		return;
	if(++i>=dim)
		i=0;
	nearest(dx>0?root->lChild:root->rChild,nd,i,dim,best,best_dist);
	if(dx2>=*best_dist)
		return;
	nearest(dx>0?root->rChild:root->lChild,nd,i,dim,best,best_dist);
}

int main()
{
	int i;
	struct node wp[]={{{2,3}},{{5,4}},{{9,6}},{{4,7}},{{8,1}},{{7,2}}};
	struct node testNode = {{9,2}};
	struct node *root,*found,*million;
	double best_dist;

	root = makeTree(wp,sizeof(wp)/sizeof(wp[1]),0,2);

	visited = 0;
	found = 0;
	nearest(root,&testNode,0,2,&found,&best_dist);
	printf("\nSearching for(%g,%g)\nfound (%g,%g) dist %g\nseen %d nodes\n\n",testNode.x[0],testNode.x[1],found->x[0],found->x[1],sqrt(best_dist),visited);
	million = (struct node*)calloc(N,sizeof(struct node));
	srand(time(0));
	for(i=0;i<N;i++)
		rand_pt(million[i]);
	root = makeTree(million,N,0,3);
	rand_pt(testNode);
	visited = 0;
	found = 0;
	nearest(root,&testNode,0,3,&found,&best_dist);
	printf("\nSearching for (%g, %g, %g)\nfound (%g, %g, %g) dist %g\nseen %d nodes\n",testNode.x[0], testNode.x[1],testNode.x[2], found->x[0], found->x[1], found->x[2], sqrt(best_dist),visited);
	int sum = 0, test_runs = 100000;
	for(i=0;i<test_runs;i++)
	{
		found = 0;
		visited = 0;
		rand_pt(testNode);
		nearest(root,&testNode,0,3,&found,&best_dist);
		sum+=visited;
	}
	printf("\n\nVisited %d nodes for %d random findings (%f per lookup)\n",sum,test_runs,sum/(double)test_runs);
	return 0;
}
