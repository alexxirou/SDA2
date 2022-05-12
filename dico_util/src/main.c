
// Le prenom jean n'est pas ajouté dans le main car le fichier originel contient
// en fait deux fois jean: jean (1) et jean (2)


/**
 * \file main.c
 * \brief Main.
 * \date 2017
 * \author SDA2
 * \copyright WTFPLv2
 */

/* Copyright © 2018 JM Dischler
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

#define MAX_STR 512
#define MAX_PRENOM 128
#define NN 5

////////////////////////////////////////////////////////////////////////////////
// Main.
////////////////////////////////////////////////////////////////////////////////

// Ce main teste la table de chaines de caracteres en utilisant un fichier Prenoms.txt
// contenant des prenoms usuels
int main(int argc, char* argv[argc-1])
{
  FILE *fnames;
  
  /* init the table. */
  Dico tnames = newDico();

  // load all surnames
  fnames = fopen("Prenoms.txt", "r");
  if (fnames == NULL) { perror("File Prenoms.txt error"); exit(1); }
  char buffer[MAX_STR];
  char prenom[MAX_PRENOM];
 
  /* Read entire file and add all names to the table. */
  unsigned int counter = 0;
  fgets(buffer, MAX_STR, fnames); // jump over first line in file
  fgets(buffer, MAX_STR, fnames);
  do
  { 
	  int i = 0; 
	  bool ignore = false;
	  // copy caracter by caracter the string
	  while (buffer[i] != '\t') 
	  { 
		  // ignore names that contain special caracters
		  if (buffer[i]<'a' || buffer[i]>'z') ignore = true; 
		  prenom[i] = buffer[i]; 
		  i++; 
	  }
	  prenom[i] = 0;
	  if (!ignore)
	  {
		  if (getIdent(tnames, prenom) == OMEGA)
		  {
			  adj(tnames, prenom, counter+1);
			  printf("%s (%u)\n", prenom, counter);
			  counter++;
		  }
	  }
	  fgets(buffer, MAX_STR, fnames);
  } while (!feof(fnames));
  fclose(fnames);

  printf("Database contains: %u names!\n", counter);

  // Now we can perform some tests on the database
  printf("\n\nTrying to find names:\n");
  char *n[NN] = { "jeane", "pierre", "marcel", "toto", "igor" };
  bool v[NN] = { true,true,true,false,true };
  unsigned int id[NN];
  int i;
  for (i = 0; i < NN; i++)
  {
	  id[i] = getIdent(tnames, n[i]);
	  if (id[i] !=0) printf("%s found, id = %u -> %s\n", n[i], id[i], v[i] ? "correct":"faux");
	  else printf("%s not found -> %s\n", n[i], !v[i] ? "correct" : "faux");
  }
  printf("Name of identifier: %u is %s, should be zygmunt\n", counter, getStr(tnames,counter));
  printf("\ndeleting %s\n", n[0]); supStr(tnames, n[0]); v[0] = false;
  printf("adding %s\n", n[3]); adj(tnames, n[3], counter+1); v[3] = true;
  printf("\n\nNow trying to find the same names again (string identifier should not change!):\n");
  for (i = 0; i < NN; i++)
  {
	  unsigned int idn = getIdent(tnames, n[i]);
	  if (id[i]!=OMEGA && idn!=0 && idn != id[i]) printf("warning %s has new identifier: %u versus %u\n", n[i], idn, id[i]);
	  //else
	  {
		  if (idn != 0) printf("%s found, id = %u -> %s\n", n[i], idn, v[i] ? "correct" : "faux");
		  else printf("%s not found -> %s\n", n[i], !v[i] ? "correct" : "faux");
	  }
  }
  printf("Name of identifier: %u is %s, should be zygmunt\n", counter, getStr(tnames, counter));


  /* Cleanup.
    */
  freeDico(tnames);
  return 0;
}

