/**
 * \file listeui.h
 * \brief Stupid wrappers for time measurement.
 * \date 2017
 * \author 
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

#ifndef MOT_H
#define MOT_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define LONG_MOT_MAX 64

typedef struct s_mot {
	char chaine[LONG_MOT_MAX]; // le mot
	unsigned int ident; // l’identifiant associé
} mot;

// Operations
mot *motNouv(char *s, unsigned int id);
void detruireMot(void *m);
void *cloneMot(void *m);
void afficheMot(mot *m);
char *chaineDuMot(mot *m);
unsigned int identDuMot(mot *m);
int compareMot(void *m, void *nom); // compare les chaines 

#endif