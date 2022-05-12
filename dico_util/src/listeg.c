#include "listeg.h"
#include "mot.h"

listeg nouvlg() { 
	return NULL; 
	}

listeg adjtetelg(listeg l, void *x, fclone clone)
{	
	listeg new=malloc(sizeof*new);
	new->succ=l;	

	new->data=clone(x);
	return new;
}

listeg rechlg(listeg l, void *x, fcomp comp)
{
	listeg t=l;
	while(t!=NULL){
		if(comp(elemlg(t),x)==0){return t;}
		t=t->succ;
	}
	return NULL;
}

int ranglg(listeg l, void *x, fcomp comp)
{	int i=0;
	listeg t=l;
	while(t!=NULL){
		if(comp(elemlg(t),x)==0){ return i;}
		t=t->succ;
		i++;
	}	
	return -1;
}

listeg supkiemelg(listeg l, unsigned int k, fdestroy destr)
{
	if(longueur(l)>=k){
		listeg t=l;
		destr(kiemelg(t,k));

	}	
	return l;
}


void destroylg(listeg l, fdestroy destr)
{	
	
	while (l != NULL)
	{
		listeg n = l->succ;
		destr(l->data);
		free(l);
		l = n;
	}
}
// selecteurs
listeg kiemelg(listeg l, unsigned int k)
{
	listeg t=l;
	for(unsigned int i = 0; i<k; i++ ){
		if(t->succ!=NULL){
			t=t->succ;
		}

	}
	return t;
}

bool videlg(listeg l) { 
	return l==NULL;
 }

unsigned int longueur(listeg l)
{
	unsigned int k=0;
	listeg t=l;
	while(t->succ!=NULL){
		t=t->succ;
		k++;
	}	
	return k;
}

void *elemlg(listeg l)
{
	return l->data;
}



