#include "mot.h"

mot *motNouv(char *s, unsigned int id)
{
	mot *n=malloc(sizeof(*n));
	strncpy(n->chaine,s,64);	
	n->ident=id;
	return n;
}

void detruireMot(void *m)
{
	if(m!=NULL){
		free(m);
	}
}

void *cloneMot(void *m)
{
	return motNouv(((mot *)(m))->chaine, ((mot *)(m))->ident);
}
void afficheMot(mot *m)
{
	printf("%s ", m->chaine);
	printf("%d\n", m->ident);
}

char *chaineDuMot(mot *m)
{
	return m->chaine;
}

unsigned int identDuMot(mot *m)
{
	return m->ident;
}


int compareMot(void *m, void *nom)
{	
	if(m!=NULL){
		char* s1=chaineDuMot(m);
		return strcmp(s1, nom);
	}
	return 1;
}
