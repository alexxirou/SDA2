/**
 * \file dico.c
 * \brief Stupid wrappers for time measurement.
 * \date 2017
 * \author 
 * \copyright WTFPLv2
 */

/* Copyright © 2017 Harenome Razanajato <hrazanajato@unistra.fr>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar.
 *
 * See http://www.wtfpl.net/ or read below for more details.
 */
/* DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */


#include "dico.h"
#include "mot.h"
#include "listeg.h"

Dico newDico(){
	Dico new=malloc(sizeof(struct s_dico));
	for(int i =0; i<N; i++){
		new->mots[i]=NULL;
		new->mots_collid[i]=NULL;
	}
	return new;
}

void freeDico(Dico t)
{
	
	for(int i =0; i<N; i++){
		detruireMot(t->mots[i]);
		destroylg(t->mots_collid[i], &free);
				
	}
	free(t);
}	



// compute hash code
unsigned int hash(char *s)
{
	unsigned int res=0;
	for(unsigned int i=0; i<strlen(s); i++){
		unsigned int interm=(s[i]-96)*(i+1);
		res=res+interm;
		}
	
	return (((22695477 * res + 1)  >> 16) % N);;
}


// returns the pointer to the string that has strid as identifier
char  *getStr(Dico t, unsigned int strid)
{	
	for (int i = 0; i < N; i++)
	{
		if (t->mots[i] != NULL)
		{
			if (identDuMot(t->mots[i]) == strid) return chaineDuMot(t->mots[i]);
			else
			{
				// search in the liste
				listeg n=t->mots_collid[i];
				while(videlg(n==0)){
					mot* t=elemlg(n);
					if(t->ident==strid){return chaineDuMot(t);}
					n=n->succ;

				}
			}
		}
	} 
	return NULL;
}	

// returns the identifier of the string str, or OMEGA if not in database
unsigned int getIdent(Dico t, char *str)
{	unsigned int res=0;
	unsigned int id=hash(str);
	if(compareMot(t->mots[id],str)==0){
		res=t->mots[id]->ident;
		
	}
	else if(rechlg(t->mots_collid[id],str,compareMot)!=NULL){
		mot* y=rechlg(t->mots_collid[id],str,compareMot)->data;
		res=y->ident;
	}
	return res;
	
}

// adds a string str to the database, returns its unique identifier
//the id and the word must be calculated correctly
void adj(Dico t, char *str, unsigned int id)
{
	unsigned int idm=hash(str);
	if(t->mots[idm]==NULL){
		t->mots[idm]=motNouv(str,id);
		
	}
	else{
		
		t->mots_collid[idm]=adjtetelg(t->mots_collid[idm],t->mots[idm], cloneMot);
		detruireMot(t->mots[idm]);
		t->mots[idm]=motNouv(str,id);
		
	}

}

void supStr(Dico t, char *str)
{
	unsigned int id=getIdent(t,str);
	if(t->mots[id]==NULL){return;}
	else if(t->mots_collid[id]!=NULL && t->mots_collid[id]->data!=NULL ){
		t->mots[id]=cloneMot(t->mots_collid[id]->data);
		listeg next=t->mots_collid[id]->succ;
		free(t->mots_collid[id]);
		t->mots_collid[id]=t;
	}
	else {
		detruireMot(t->mots[id]);
	}
}


  
