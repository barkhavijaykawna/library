/*****************************************************************************
 *  * Copyright (c) barkha kawna bkawana707@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/


/*  this file contain declaration of all fuction and structure that are used in the program */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>
#include <time.h> 
#include <termios.h>
typedef struct date {
	int day;
	int mon;
	int year;
} date;
typedef struct book {
	int id[30];		/* required structures */
	int issue[30];
	char name[30];
	char author[30];
	char publication[30];
	int quantity;
	float price;
	int count;
} book;
typedef struct student {
	int id_no;
	char name[25];
	int year;
	int issuedbookid[2];
	int count;
	date d[2];
} student;
ssize_t my_getpass (char *lineptr, size_t len, FILE *stream);
void issuedbookdata();
void enroll();
void removestudent();
void addbook();
void removebook();
void editbook();
void searchbook();
void issuebook();
void returnbook();
void changepassword();
void admin();
void studentlogin();
int login(void); 
int printmenu();
void lower_string(char *string);
void refreshcnt(int *cntbook, int *cntstud);
