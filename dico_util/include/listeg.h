/**
 * \file listeg.h
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

#ifndef LISTEG_H
#define LISTEG_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef int (*fcomp)(void *x, void *y);
typedef void *(*fclone)(void *x);
typedef void (*fdestroy)(void *x);

typedef struct s_maillong {
	void				*data; // the generic data
	struct s_maillong	*succ; // next link
} *listeg;

// Operations
////////////////////////////////////////////////
// creates a new generic list ex nihil
listeg nouvlg();

// add an element x in front of the list
// x is duplicated in memory using clone function
// x != NULL, clone !=NULL
listeg adjtetelg(listeg l, void *x, fclone clone);

// finds the first element that matches x using the comparison function comp
// x != NULL, comp!=NULLS
// returns the link that contains x
listeg rechlg(listeg l, void *x, fcomp comp);

// finds the index of the first element that matches x using the comparison function comp
// x != NULL, comp!=NULL
// returns -1 if not found
int ranglg(listeg l, void *x, fcomp comp);

// removes the k th link, and frees corresponding object with destr
// k>=0 && k<longueur(l), destr!=NULL
listeg supkiemelg(listeg l, unsigned int k, fdestroy destr);

// gets the k th element of the list
// k>=0 && k<longueur(l)
listeg kiemelg(listeg l, unsigned int k);

//test if list is empty
bool videlg(listeg l);

// list length
unsigned int longueur(listeg l);

// free all list memory, including objects
void destroylg(listeg l, fdestroy destr);

// gets the element of the list head
void *elemlg(listeg l);




#endif
