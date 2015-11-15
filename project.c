
/*****************************************************************************
 * Copyright (c) Barkha kawana bkawana707@gmail.com
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

/* this file contain code for all the function which are used in program like for enrolling and removing student ,
		Adding , removing , searching , removing , issuing , retuning books And chainging password, login etc..  */

#include"project.h"
#include<time.h>
#include <termios.h>
#define BACKSPACE 127

 /*  Enroll function takes data  about student ( from ADMIN ) to be enrolled to the library and enrolls if the student is not enrolled 
		previously with the same name or same id    */
void enroll() {			
	system("clear");
	student s, a;			/* enrolls student */
	int tmp = 0;
	FILE *fp;
	fp = fopen("student.txt", "a+");
	printf("\n\n\t *********** enter data of student ***************\n");
	printf("\t____________________________________________________\n\n");
	printf("\tenter id number of student(integer only and max. 9 digit) :-  ");
	scanf("%d", &s.id_no);
	printf("\tenter name of student(max. 25 characters) :- ");	
	getchar();
	scanf("%[^\n]", s.name);
	printf("\tenter year of student (integer ):- ");
	scanf("%d", &s.year);
	s.count = 0;
	rewind(fp);
	while(fread(&a, sizeof(s), 1, fp) == 1) 
	{			
		if(a.id_no == s.id_no) 			/* check for repetation of name or id of student */
		{
			printf("\t*** input error ** :- id number already exists can't enroll\n");
			tmp = 1;
			break;
		}
		if(!strcmp(s.name, a.name)) 
		{
			printf("\t*** input error ** :- name of student already exists can't enroll\n");
			tmp = 1;
			break;
		}			
	}	
	fseek(fp, 0, 2);

	if(tmp != 1)					/* enroll if previously not enrolled  */
	{
		printf("\t*****student enrolled sucessfully*******\n");
		fwrite(&s, sizeof(student), 1, fp);
	}

	fclose(fp);
	printf("\n\twant to enroll another student :(yes - 1 or no - 2)  :-  ");
	scanf("%d", &tmp);

	if(tmp == 1)
		enroll();
	else {	
		system("clear");
		printf("\n");
	}	
}
 /*   first give choice to ADMIN for finding student ,
	Then takes proper input from ADMIN .
	 	If found asks for removing and removes student after conformation from ADMIN  */		
void removestudent()
{				/* remove students */
	system("clear");
	student a;
	int d, choice, tmp = 0, ch;
	char str[25];
	printf("\n\n\t************ Find student by :-- \n\n");
	printf("\t1. Name \n");
	printf("\t2. id number\n");				/* choices */
	printf("\t3. Back to menu\n");
	printf("\n\tenter your choice :--  ");	
	scanf("%d", &choice);
	if((choice >= 4) || (choice <= 0))
	{
		printf("\n\n***** error in choice **** wrong choice\n\tre-enter the choice :-- ");
		scanf("%d", &choice);	
	}
	else if(choice == 3)
	{
		return ;
	}
	else if(choice == 1)
	{
		printf("\n\tenter name to be removed( max. 25 characters) :--  ");
		getchar();
		scanf("%[^\n]", str);
		FILE *fp, *ft;
		fp = fopen("student.txt", "a+");
		ft = fopen("temp.txt", "a+");
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(strcmp(a.name, str))
			{
				fseek(ft, 0, 2);
				fwrite(&a, sizeof(a), 1, ft); 	/*  write all in tempory file except that  */
			}                           		/*  we want to delete  */
			else {
				tmp = 1;
				if(a.count != 0)
				{
					tmp = 2;			
					printf("\t***Some books are issued to the student :-- can't remove student****\n");
					break;
				}
			}
		}
		fclose(ft);
		fclose(fp);
		if(tmp == 1)
		{
			printf("\n\t\t***student found***\n\tDo you really want to remove the student(yes - 1 or No -2) :-- ");		
			scanf("%d", &d);
			if(d == 1)
			{			
				remove("student.txt");
				rename("temp.txt","student.txt"); /*copy all item from temporary file to fp except that */
				printf("\n\t\t ***student removed successfully ***\n\n");
			}
			else {
				remove("temp.txt");
				printf("\t\t##### student not removed ####\n\n");
			}	
		
		}
		else if(tmp != 2) {
			remove("temp.txt");
			printf("\n\t******* invalid name :- no student enrolled with this name  ******\n\n");
		}
		if(tmp == 2) {
			remove("temp.txt");
		}	
	}
	else if(choice == 2) 
	{
		printf("\n\tenter id number of student to be removed(integer only max. 9 digit) :--  ");
		scanf("%d", &d);
		FILE *fp, *ft;
		fp = fopen("student.txt", "a+");
		ft = fopen("temp.txt", "a+");
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(a.id_no != d)
			{
				fseek(ft, 0, 2);
				fwrite(&a, sizeof(a), 1, ft); 	/*  write all in tempory file except that  */
			}                           		/*  we want to delete  */
			else {
				tmp = 1;
				if(a.count != 0)
				{
					tmp = 2;			
					printf("\t***Some books are issued to the student :-- can't remove student****\n");
					break;
				}
			}
		}
		fclose(ft);
		fclose(fp);
		if(tmp == 1)
		{
			printf("\n\t\t***student found***\n\tDo you really want to remove the student(yes - 1 or No -2) :-- ");		
			scanf("%d", &ch);
			if(ch == 1)
			{			
				remove("student.txt");
				rename("temp.txt","student.txt"); 		/*  copy all item from temporary file to fp except that 
											which we want to remove  */
				printf("\n\t ***student removed successfully ***\n");
			}
			else {
				remove("temp.txt");
				printf("\t##### student not removed ####\n");
			}	
		
		}
		else if(tmp != 2) {
			remove("temp.txt");
			printf("\n\t******* invalid id number :- no student enrolled with this id ******\n\n");
		}
		if(tmp == 2) {
			remove("temp.txt");
		}	
	}
	printf("\n\twant to remove another student :(yes -  1 or no -  any number)  :-  ");	
	scanf("%d", &ch);
	if(ch == 1)
		removestudent();
	else {
		system("clear");
		printf("\n");
	}	
	
}	

	/*  this function takes information of book to be added to the library ,	
		checks for previous availability of book with same name, author and publication , Then
		1. If not found , it simply takes id's for all copies of book and check for previous availability of id , 	
				if found  the  ask for another id
		2. If found asks for adding new copies of same book check for id's as mentioned earliar		*/
void addbook()			
{
	system("clear");
	book b, a, c;
	int tmp = 0, i, j, p = 0, tmp2 = 0, x, d[30], tp = 0;
	FILE *fp, *ft;
	printf("\n\n\t ****** enter data for book*****\n");
	add :
	fp = fopen("book.txt", "a+");
	getchar();
	printf("\n\t #########  all data will be saved in small case letters  #######\n\n");
	printf("\n\tenter the name of book(max. 30 characters) :- ");	
	scanf("%[^\n]", b.name);
	lower_string(b.name);
	if(strlen(b.name) > 30) {
		printf("\n\t\t !!! limit of name exceeded !!!\n\n");
		printf("\t           !!!! data not saved !!!!\n\n");
		return;
	}
	printf("\tenter the name of author(max. 30 characters) :- ");		/* take input from user */
	getchar();	
	scanf("%[^\n]", b.author);
	lower_string(b.author);	
	if(strlen(b.author) > 30) {
		printf("\n\t\t !!! limit of characters  exceeded !!!\n\n");
		printf("\t\t!!!! data not saved !!!!\n\n");
		return;
	}
	printf("\t enter the publication of book(max. 30 characters) :- ");
	getchar();
	scanf("%[^\n]", b.publication);
	lower_string(b.publication);
	if(strlen(b.publication) > 30) {
		printf("\n\t\t !!! limit of characters exceeded !!!\n\n");
		printf("\t\t!!!! data not saved !!!!\n\n");
		return;
	}
	stage1 :
	printf("\thow many book do you want to add(integer only and max. 9 digit) :- ");     /* specifing limit for copies of one book */
	scanf("%d", &b.quantity);
	if(b.quantity > 30) {
		printf("\t\t******** sorry *********\n\n\t ***** you can't add more than 30 books at a time *****\n\n");
		goto stage1;
	}		
	b.count = 0;
	tmp = 0;
	rewind(fp);
	while(fread(&c,sizeof(c),1,fp)==1)
	{
		if(!strcmp(c.name, b.name)) {
			if(!strcmp(c.author, b.author)) {
				if(!strcmp(c.publication, b.publication)) 
				{						/* search in file */	
					tmp = 1;					
					break;
				}
			}
		}
	}
	if(tmp != 1) {
		printf("\t****** book not present previously *****\n\n");
		printf("\tenter price of book(float) :- ");
		scanf("%f", &b.price);
		printf("\tenter the id number of %d books to be added(integers only) :- \n", b.quantity);
		for(i = 0; i < b.quantity; i++) {
			level4 :
			scanf("%d", &b.id[i]);
				for(j = 0; j < i; j++) {
					if(b.id[i] == b.id[j]) {
							printf("\n\t\t *** error id no already exists ***\n\n");
							printf("\tDo you want to re-enter id no. (1 for yes) :- ");
							scanf("%d", &p);
	/* confirm that id of book */			if(p == 1)
								goto level4;
	/* should not repeat */				else 
							{
								printf("\n\n\t *** data not saved *** \n\t #######################\n\n");
								goto endfunc;
								
							}	
						}  
				}
				rewind(fp);
				while(fread(&a,sizeof(a),1,fp)==1) {
					for(j = 0; j < a.quantity - a.count; j++) {
						if(b.id[i] == a.id[j]) {
							printf("\n\t\t *** error id no already exists ***\n\n");
							printf("\tDo you want to re-enter id no. (1 for yes) :- ");
							scanf("%d", &p);
							if(p == 1)
								goto level4;
							else 
							{
								printf("\n\n \t *** data not saved *** \n\t ######################\n\n");
								goto endfunc;
								
							}	
						}  
					}
					for(j = 0; j < a.count; j++) {
						if(b.id[i] == a.issue[j]) {
							printf("\n\t\t *** error id no already exists ***\n\n");
							printf("\tDo you want to re-enter id no. (1 for yes) :- ");
							scanf("%d", &p);
							if(p == 1)
								goto level4;
							else 
							{
								printf("\n\n \t *** data not saved *** \n\t #######################\n\n");
								goto endfunc;
								
							}	
						}  
					}		
				}
			
		}
		if (tp != 1) {
			fseek(fp, 0, 2);
			fwrite(&b, sizeof(book), 1, fp);
			printf("\t***** data entered succesfully *****\n\n");
			fclose(fp);
		}
	}
			/*  if book found */
	if(tmp == 1) {
		printf("\n\t *** book with same author and name already present ***\n\n");
		if((c.quantity + b.quantity) > 30) {
			printf("\t%d books already present, so u can't add %d more copies of same book here\n",a.quantity, b.quantity);
			printf(" \t !!!!  try using another name !!!!\n\n");
			goto endfunc;
			
		}
	
		printf("\tDo you want to add extra copies of book(1 for yes ) :-- ");
		scanf("%d", &tmp2);
		if(tmp2 == 1) {
			printf("\t******** enter id numbers of books to be added( %d ) :-- \n", b.quantity);
			for(i = 0; i < b.quantity; i++) {
				level3 :
				scanf("%d", &d[i]);	
				for(j = 0; j < i; j++) {
					if(d[i] == d[j]) {
							printf("\n\t\t *** error id no already exists ***\n\n");
							printf("\tDo you want to re-enter id no. (1 for yes) :- ");
							scanf("%d", &p);
							if(p == 1)
	/* confirm that id of book */			goto level3;
							else {
	/* should not repeat */					
							       printf("\n\n\t *** data not saved *** \n\t #########################\n\n");
								goto endfunc;
							}	
						}  
				}
				rewind(fp);
				while(fread(&a,sizeof(a),1,fp)==1) {
					for(j = 0; j < a.quantity - a.count; j++) {
						if(d[i] == a.id[j]) {
							printf("\n\t\t *** error id no already exists ***\n\n");
							printf("\tDo you want to re-enter id no. (1 for yes) :- ");
							scanf("%d", &p);
							if(p == 1)
								goto level3;
							else {
								printf("\n\n\t *** data not saved *** \n\t ######################\n\n");
								
								goto endfunc;
							}	
						} 
					}
					for(j = 0; j < a.count; j++) {
						if(d[i] == a.issue[j]) {
							printf("\n\t\t *** error id no already exists ***\n\n");
							printf("\tDo you want to re-enter id no. (1 for yes) :- ");
							scanf("%d", &p);
							if(p == 1)
								goto level4;
							else {
							       printf("\n\n \t *** data not saved *** \n\t ########################\n\n");
								goto endfunc;
								tp = 1;
							}	
						}  
					}		
				}					
			}
		}	
		
		x = c.quantity - c.count;	
		for(i = 0; i < b.quantity; i++) {
			c.id[x + i] = d[i];			/* add new id no. to old book */
		}
		c.quantity += b.quantity;
		rewind(fp);
		ft = fopen("tmp.txt", "a+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(!strcmp(a.name, b.name)) {
				if(!strcmp(a.author, b.author)) {
					if(!strcmp(a.publication, b.publication)) {
						tp = 1;
					}
				}					/* write all data in temprary file except the book whose */
			}							/* data is to be changed */
			if(tp != 1) {
					fwrite(&a, sizeof(a), 1, ft);					
			}
			else {
				tp = 0;
			}
		}
		fclose(ft);
		fclose(fp);
		remove("book.txt");
		rename("tmp.txt", "book.txt");			/* rename temprary file and remove original file */
		fp = fopen("book.txt", "a+");
		fseek(fp, 0, 2);
		fwrite(&c, sizeof(c), 1, fp);	
		printf("\t***** data entered succesfully *****\n\n");		
		fclose(fp);	
	}
	endfunc :
	
	printf("\t do you want to add more book (1 for yes) :- ");
	scanf("%d", &tmp);
	if(tmp == 1)
		goto add;
	else
		printf("\n\n");
}	

/*  this function takes input about book and search for it,
	if no copies of book is issued , then removes the book from library 	*/
void removebook() {				
	int ch, tmp = 0, tmp1 = 0;
	book a;
	FILE *fp, *ft;
	fp = fopen("book.txt", "a+");
	char bname[30], author[30], publication[30];
	system("clear");
	printf("\n\n\t\t ######## Remove Book #########");
	remove :
	printf("\n\n\t Do you want to search book first(1 for yes or any number for no) :- ");
	scanf("%d",&ch);
	if(ch == 1) {
		searchbook();								/* call search function */
	}
	printf("\t #########   enter all data in small case letters  #######\n");
	printf("\n\tenter the name of book (max 30 character) :- ");			
	getchar();
	scanf("%[^\n]", bname);	
	printf("\tenter the name of author(max. 30 characters) :- ");			/* take input data for editing */
	getchar();	
	scanf("%[^\n]", author);	
	printf("\t enter the publication of book(max. 30 characters) :- ");
	getchar();
	scanf("%[^\n]", publication);
	ft = fopen("temp0.txt", "a+");
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		if(!strcmp(a.name, bname)) {
			if(!strcmp(a.author, author)) {
				if(!strcmp(a.publication, publication)) {	/* search book for given input */
					tmp1 = 1;
					tmp = 1;
				}
			}
		}
		if(tmp == 1) {
			if(a.count != 0) {
				printf("\n\t !!!!!! some copies of book are issued, can't remove the book !!!!!!!\n\n");
				tmp = 2;
				break;
			}
			
		}
		if(tmp != 1) {
			fseek(ft, 0, 2);				/* copy all data in a temprary file for editing */
			fwrite(&a, sizeof(a), 1, ft);
			
		}
		if(tmp == 1)
			tmp = 0;
	}	
	fclose(ft);
	fclose(fp);
	if(tmp1 != 1) {
		printf("\n\t *******  book not found  *******\n\n");		/* return if book not found */	
		remove("temp0.txt");
		return;
	}
	if(tmp == 2) {
		remove("temp0.txt");
		return;
	}
	remove("book.txt");						/* rename temprary file and remove original file */
	rename("temp0.txt", "book.txt");
	printf("\n\t **** book removed succesfully **** \n\n");
	printf("\t do you want to remove another book (1 for yes) :- ");
	scanf("%d", &tmp);
	if(tmp == 1)
		goto remove;
	else
		printf("\n\n");
}
/*  this function edits book's data which present in library	*/	
void editbook() {
	system("clear");
	printf("\n\n\t\t ****** edit book's data ******\n\n");	
	int ch, tmp = 0, tmp1 = 0;
	book a;
	FILE *fp, *ft;
	fp = fopen("book.txt", "a+");
	char bname[30], author[30], publication[30];
	printf("\n\n\tDo you want to search book first(1 for yes or any number for no) :- ");	/* call search function */
	scanf("%d",&ch);
	if(ch == 1) {
		searchbook();
	}
	printf("\n\t #########   enter all data in small case letters  #######\n\n");	/* take input data for searching */
	printf("\n\tenter the name of book (max 30 character) :- ");
	getchar();
	scanf("%[^\n]", bname);	
	lower_string(bname);
	printf("\tenter the name of author(max. 30 characters) :- ");
	getchar();	
	scanf("%[^\n]", author);
	lower_string(author);	
	printf("\tenter the publication of book(max. 30 characters) :- ");
	getchar();
	scanf("%[^\n]", publication);
	lower_string(publication);
	ft = fopen("temp0.txt", "a+");
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		if(!strcmp(a.name, bname)) {
			if(!strcmp(a.author, author)) {				/* search book for given input */
				if(!strcmp(a.publication, publication)) 	
				{	
					tmp = 1;
				}	
			}
		}
		
		if(tmp != 1) {
			fseek(ft, 0, 2);			/* copy all data in a temprary file for editing */ 
			fwrite(&a, sizeof(a), 1, ft);
			tmp = 0;
		}
	}
	rewind(fp);	
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		if(!strcmp(a.name, bname)) {
			if(!strcmp(a.author, author)) {				/* search book for given input */
				if(!strcmp(a.publication, publication)) {	
					tmp1 = 1;
					break;
				}	
			}
		}
	}
	fclose(ft);
	fclose(fp);
	if(tmp1 != 1) {								/* return if book not found */			
		printf("\n\t *******  book not found  *******\n\n");
		remove("temp0.txt");
		return;
	}
	label2 :
	printf("\n\t what do you want to edit :- \n");
	printf("\t1. Name of book\n");
	printf("\t2. Name of author\n");
	printf("\t3. name of publication\n");
	printf("\t4. Back to menu\n");
	printf("\n\tenter your choice :- ");
	scanf("%d", &ch);
	printf("\n\t #########   enter all data in small case letters  #######\n");	/* take input data for editing */
	if(ch == 1) {
		printf("\n\tenter the name of book (max 30 character) :- ");
		getchar();
		scanf("%[^\n]", bname);	
		lower_string(bname);
		strcpy(a.name, bname);
	}		
	else if(ch == 2) {
		printf("\n\tenter the name of author (max 30 character) :- ");
		getchar();
		scanf("%[^\n]", bname);	
		lower_string(bname);
		strcpy(a.author, bname);
	}
	else if(ch == 3) {
		printf("\n\tenter the name of publication (max 30 character) :- ");
		getchar();
		scanf("%[^\n]", bname);	
		lower_string(bname);
		strcpy(a.publication, bname);
	}
	else {
		remove("temp0.txt");
		printf("\n\t  !!!!  changes not saved !!!! \n\n");
	}
	printf("\n\twant to change another data (1 for yes) :- ");
	scanf("%d", &ch);
	if(ch == 1)
		goto label2;
	remove("book.txt");
	rename("temp0.txt", "book.txt");
	fp = fopen("book.txt", "a+");
	fseek(fp, 0, 2);
	fwrite(&a, sizeof(a), 1, fp);
	printf("\n\t **** book edited successfully **** \n\n");
	fclose(fp);
}
	
/*   	this function first give choice for searching, 
	     it also give results for substrings  found in name of book or author	*/
void searchbook() {				
	system("clear");
	FILE *fp;
	char name[30];
	book a;
	int ch, i, cnt, j, k;
	label1 :
	j = 1, k = 0, cnt = 0;
	fp = fopen("book.txt", "a+");
	printf("\n\n\n\t#### search book by :-\n\n");
	printf("\t1. Name of book\n");				/* menu of function */
	printf("\t2. Name of author\n");
	printf("\t3. id number\n");
	printf("\t4. Back to menu\n");
	printf("\n\tenter your choice :- ");
	scanf("%d", &ch);
	switch(ch) {
		case 1: 		/* search by name */
			printf("\n\tenter the name of book(30 character max.) :- ");
			getchar(); 
			scanf("%[^\n]", name);
			lower_string(name);
			printf("\n\t\t######  Related search :-\n\n");
			rewind(fp);
			printf("\t________________________________________________________________________________________________________________________________\n");
			printf("\t|No.|\tTitle Of book\t\t    | \tName Of Author\t\t     |\tPublication Of Book\t\t| Total copies of book  |\n");
			printf("\t|___|_______________________________|________________________________|__________________________________|_______________________|");				
			while(fread(&a,sizeof(a),1,fp)==1) { 			/*search in file */				
				
				if(strstr(a.name, name) != NULL) {
					printf("\n\t| %d.| %-30s| %-30s | %-30s   |     %d\t\t\t|\n", j++, a.name, a.author, a.publication, a.quantity);
					if(a.quantity - a.count) {
						printf("\t|   id numbers of %d available books are :-  ", a.quantity - a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t\t|\n",a.id[0]);
					}
					for(i = 1; i < a.quantity - a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t\t|\n",a.id[i]);
					if(a.count) {
						printf("\t|   id numbers of %d issued books  are :-    ", a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t\t|\n", a.issue[0]);
					}
					for(i = 1; i < a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t\t|\n",a.issue[i]);
					cnt = 1;
                                        printf("\t|___________________________________|________________________________|__________________________________|_______________________|");
				}
				if(cnt == 1) {
					cnt = 0;
					continue;
				}
				if(strstr(name, a.name) != NULL) {
					printf("\n\t| %d.| %-30s| %-30s | %-30s   |     %d\t\t|\n", j++, a.name, a.author, a.publication, a.quantity);
					if(a.quantity - a.count) {
						printf("\t|   id numbers of %d available books are :-  ", a.quantity - a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t\t|\n",a.id[0]);
					}
					for(i = 1; i < a.quantity - a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t\t\t|\n",a.id[i]);
					if(a.count) {
						printf("\t|   id numbers of %d issued books  are :-    ", a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t\t|\n", a.issue[0]);
					}
					for(i = 1; i < a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t\t|\n",a.issue[i]);
                                        printf("\t|___________________________________|________________________________|__________________________________|_______________________|");
				}	
				
			}
			if(j == 1) 
				printf("\n\t\t#### sorry no book found for your search ###\n\n");
			printf("\n");	
			break;

		case 2:				/* search by author */
			printf("\n\tenter the name of author(in small case letter) :- ");
			getchar(); 
			scanf("%[^\n]", name);
			lower_string(name);
			printf("\n\t\t######  Related search :-\n\n");
			rewind(fp);	
                      	printf("\t_________________________________________________________________________________________________________________________________\n");
			printf("\t|No.|  \tTitle Of book\t\t     | \tName Of Author\t\t      |\tPublication Of Book\t\t |Total copies of book   |\n");
			printf("\t|___|________________________________|________________________________|__________________________________|_______________________|");	
			while(fread(&a,sizeof(a),1,fp)==1) { 
				
				if(strstr(a.author, name) != NULL) {
					printf("\n\t| %d.| %-30s | %-30s | %-30s   |     %d \t\t |\n", j++, a.name, a.author, a.publication, a.quantity);
					if(a.quantity - a.count) {
						printf("\t|   id numbers of %d available books are :-  ", a.quantity - a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t\t |\n",a.id[0]);
					}
					for(i = 1; i < a.quantity - a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t\t |\n",a.id[i]);
					if(a.count) {
						printf("\t|   id numbers of %d issued books  are :-    ", a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t\t |\n", a.issue[0]);
					}
					for(i = 1; i < a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t\t |\n",a.issue[i]);
					cnt = 1;
                                        printf("\t|___|________________________________|________________________________|__________________________________|_______________________|");	
				}
				if(cnt == 1) {
					cnt = 0;
					continue;
				}
				if(strstr(name, a.author) != NULL) {
					if(strstr(a.author, name) != NULL) {
					printf("\n\t| %d.| %-30s | %-30s | %-30s   |     %d\t\t |\n", j++, a.name, a.author, a.publication, a.quantity);
					if(a.quantity - a.count) {
						printf("\t|   id numbers of %d available books are :-  ", a.quantity - a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t |\n",a.id[0]);
					}
					for(i = 1; i < a.quantity - a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t |\n",a.id[i]);
					if(a.count) {
						printf("\t|   id numbers of %d issued books  are :-    ", a.count);
						printf("%-8d\t\t\t\t\t\t\t\t\t\t |\n", a.issue[0]);
					}
					for(i = 1; i < a.count; i++)
						printf("\t|\t\t\t\t\t    %-8d\t\t\t\t\t\t\t\t\t |\n",a.issue[i]);
                                        printf("\t|___|_______________________________|________________________________|__________________________________|_______________________|");	
                                        }
				}	
			}
			if(j == 1) 
				printf("\n\t\t #### sorry no book found for your search ###\n\n");
			printf("\n");
			break;	

		case 3: 			/* search by id no. */
			printf("\n\t enter id number of book :- ");
			scanf("%d", &cnt);
			printf("\n\t\t######  Related search :-\n\n");
			rewind(fp);	
			while(fread(&a,sizeof(a),1,fp)==1) { 				/*search in file */ 
				for(i = 0; i < a.quantity - a.count; i++) {
					if(cnt == a.id[i]) {
						printf("\tinformation of book : %s | %s | %s \n\n",a.name, a.author, a.publication);
						k = 1;
						break;
					}
				}
				for(i = 0; i < a.count; i++) {
					if(cnt == a.issue[i]) {
						printf("\t\t ***** book with this id is issued ***** \n");
						printf("\tinformation of book : %s  |  %s  |   %s \n\n",a.name, a.author, a.publication);
						k = 1;
						break;
					}
				}
				if(k == 1)
					break;
			}
			if(k != 1)
				printf("\t\a *** no book found with this id ***\n\n");
			break;

		case 4: 		/* return to menu */
			return;
		default :
			printf("\n\t !!!!!wrong choice !!!!!!\n\n");
			break;	
	}
	printf("\n\n\tdo you want to search another book(1 for yes) :-");
	scanf("%d", &ch);
	if(ch == 1)
		goto label1;
	else
		printf("\n\n");
}
	
/*   input :- id of student, id of book
	it check for availability of student and book , no. of book issued to student , previously issued book to student
	it takes current date automatically for issuing book and store it 	*/
void issuebook() { 
	system("clear");				/* function for issuing books */
	int sid, bid, tmp = 0, i = 0,j = 0, bid1, tmp1, k = 0, l = 0; 
	char p[30], q[5], r[6];
	student a, c;
	book b, d;
	FILE *fs, *fb, *ft;
	issue :
	tmp1 = 0, tmp = 0, bid1 = 0;
	printf("\n\t\t    ######### Issue Book #########\n");
	printf("\n\n\tenter id no. of student(integer only):- ");
	scanf("%d", &sid);
	printf("\n\tenter id no. of book(integer only) :- ");
	scanf("%d", &bid);	
	fs = fopen("student.txt", "a+");
	fb = fopen("book.txt", "a+");
	rewind(fs);
	while(fread(&a,sizeof(a),1,fs)==1)				/* search for student of given id */
	{		                        	
		if(a.id_no == sid) {
			tmp = 1;
			if(a.count >= 2)
			{			
				printf("\n\t*** 2 books are already issued to the student :-- can't issue more books****\n\n");
				fclose(fs);
				fclose(fb);
				return;
			}
			if(a.count) {
				bid1 = a.issuedbookid[0];
				tmp1 = 1;
			}
			break;
		}
	}
	if(tmp != 1) {
		printf("\n\t***** no student with this id exist *****\n\n");	/* return if student not found */
		return ;
	}
	tmp = 0;
	
	rewind(fb);	
	while(fread(&b,sizeof(b),1,fb)==1) { 
		for(i = 0; i < b.quantity - b.count; i++) {
			if(bid == b.id[i]) {
				tmp = 1;				/* search for book with given id */
				break;
			}
		}
		for(i = 0; i < b.count; i++) {
			if(bid == b.issue[i]) {
				printf("\n\t ***** book is already issued *****\n\n");	/* search for book with given id */
				fclose(fs);
				fclose(fb);
				return;
			}
			if((bid1 == b.issue[i]) && (tmp1 == 1)) {
				printf("\n\n\t\t !!!!!! same book already issued to the student !!!!!!\n\n");
				fclose(fs);
				fclose(fb);
				return;
			}
		}
		if(tmp == 1)
			break;
	}
	if(tmp != 1) {
		printf("\n\t\a *** no book found with this id ***\n\n");	/* return if book not found */
		fclose(fs);
		fclose(fb);
		return;
	}
	l = 0, j = 0;
	if(a.count == 1)
		l = 1;
	system("date > date");
	ft = fopen("date", "r");
	fread(p, 29, 1, ft);
	for(i = 0; i < strlen(p); i++) {
		if(p[i] == ' ') {
			j++;
			if(k == 1)
				k = -1;
			else
				k = 0;
			continue;			/* finding today's date */
		}		
		if(j == 3) {
			a.d[l].day = atoi(q);
			if(a.d[l].day > 0)
				break;
		}
		if((j == 4) && (k == -1)) {
			a.d[l].day = atoi(q);
			k = 0;
			break;
		}
		q[k] = p[i];
		k++;		
	}
	
	j = 0;
	for(i = strlen(p) - 6; i < strlen(p) - 1; i++) {
		r[j] = p[i];
		j++;
	}
	a.d[l].year = atoi(r);
	if(strstr(p, "Jan"))
		a.d[l].mon = 1;
	if(strstr(p, "Feb"))
		a.d[l].mon = 2;
	if(strstr(p, "Mar"))			/* finding current month */
		a.d[l].mon = 4;
	if(strstr(p, "Apr"))
		a.d[l].mon = 5;
	if(strstr(p, "May"))
		a.d[l].mon = 5;
	if(strstr(p, "Jun"))
		a.d[l].mon = 6;
	if(strstr(p, "Jul"))
		a.d[l].mon = 7;
	if(strstr(p, "Aug"))
		a.d[l].mon = 8;
	if(strstr(p, "Sep"))
		a.d[l].mon = 9;
	if(strstr(p, "Oct"))
		a.d[l].mon = 10;
	if(strstr(p, "Nov"))
		a.d[l].mon = 11;
	if(strstr(p, "Dec"))
		a.d[l].mon = 12;
	fclose(ft);
	a.issuedbookid[a.count] = bid;
	a.count++;
	strcpy(d.name, b.name);	
	strcpy(d.author, b.author);
	strcpy(d.publication, b.publication);
	d.quantity = b.quantity;
	d.price = b.price;
	d.issue[0] = bid;
	for(i = 0; i < b.count; i++) {
		d.issue[i + 1] = b.issue[i];
	}
	d.count = b.count + 1;
	for(i = 0,j = 0; i < b.quantity - b.count;) {
		if(b.id[i] == bid) {
			i++;
		}
		else {
			d.id[j] = b.id[i];
			i++, j++;
		}
	}
	ft = fopen("temp3.txt", "a+");
	rewind(fs);
	while(fread(&c,sizeof(c),1,fs)==1)
	{
		if(c.id_no != sid)
		{	
			fseek(ft, 0, 2);
			fwrite(&c, sizeof(c), 1, ft); 	/*  write all in tempory file except that  */
		}                           		/*  we want to delete  */
		else {
			
		}
	}
	fclose(fs);
	fclose(ft);
	remove("student.txt");
	rename("temp3.txt","student.txt"); 	/*  copy all item from temporary file to fp except that which we want to change  */
	fs = fopen("student.txt", "a+");	/* rename temprary file and remove original file */
	fseek(fs, 0, 2);
	fwrite(&a, sizeof(a), 1, fs);									
	fclose(fs);
	ft = fopen("temp3.txt", "a+");
	tmp = 0;
	rewind(fb);	
	while(fread(&b,sizeof(b),1,fb)==1) { 
		for(i = 0; i < b.quantity - b.count; i++) {
			if(bid == b.id[i]) {
				tmp = 1;
			}
		}
		if(tmp != 1) { 
			fseek(ft, 0, 2);
			fwrite(&b, sizeof(b), 1, ft); 		/*  write all in tempory file except that  */
								/*  we want to delete  */
		}
		else {
			tmp = 0;
		}
	}	
	fclose(ft);
	fclose(fb);	
	remove("book.txt");
	rename("temp3.txt", "book.txt");		/* rename temprary file and remove original file */
	fb = fopen("book.txt", "a+");
	fseek(fb, 0, 2);
	fwrite(&d, sizeof(d), 1, fb);
	fclose(fb);
	printf("\n\n\t ######## book issued successfully ########\n\n");
	printf("\t do you want to issue another book (1 for yes) :- ");
	scanf("%d", &tmp);
	if(tmp == 1)
		goto issue;
	else{
	}
}
/*    input :- student id, book id
	  it check for correctness of input
	  it takes current date automatically for checking about delay in returning book and fines 1 RS per day after deadline	*/ 	
void returnbook() {
	system("clear");			/* function for returning books */
	int sid, bid, tmp = 0, tmp1 = 0,i = 0, j = 0, k = 0, delay; 
	student a, c;
	book b, d;
	char p[30], q[5], r[6];
	date cur;
	FILE *fs, *fb, *ft;
	struct tm start_date;
  	struct tm end_date;
  	time_t start_time, end_time;
  	double seconds;
	printf("\n\t\t   #########  Return Book  #########\n");
	return1 :
	tmp = 0;
	printf("\n\n\tenter id no. of student(integer only and max. 9 digit ):- ");
	scanf("%d", &sid);
	printf("\n\tenter id no. of book (integer only and max. 9 digit) :- ");
	scanf("%d", &bid);
	fs = fopen("student.txt", "a+");
	fb = fopen("book.txt", "a+");
	while(fread(&a,sizeof(a),1,fs)==1)				/* search for student of given id */
	{		                        	
		if(a.id_no == sid) {
			tmp = 1;
			if(a.count == 0)
			{			
				printf("\n\t **** no book issued to given student id ****\n\n");
				return;
			}
			for(i = 0; i < a.count; i++) {
				if(a.issuedbookid[i] == bid) {
					tmp1 = 1;
				}
			}
			if(tmp1 != 1) {
				printf("\n\t **** given book id is not issued to given student id ****\n\n");
				fclose(fs);
				fclose(fb);
				return;
			}	
			break;
		}
	}
	if(tmp != 1) {
		printf("\n\t***** no student with this id exist *****\n\n");	/* return if student not found */
		fclose(fs);
		fclose(fb);
		return ;
	}
	rewind(fb);	
	tmp = 0;
	while(fread(&b,sizeof(b),1,fb)==1) { 
		for(i = 0; i < b.count; i++) {
			if(bid == b.issue[i]) {
				tmp = 1;				/* search for book with given id */
				break;
			}
		}
		if(tmp == 1) {
			break;
		}
	}
	j = 0;
	system("date > date");
	ft = fopen("date", "r");
	fread(p, 29, 1, ft);
	for(i = 0; i < strlen(p); i++) {
		if(p[i] == ' ') {
			j++;
			if(k == 1)
				k = -1;
			else
				k = 0;
			continue;			/* finding today's date */
		}		
		if(j == 3) {
			cur.day = atoi(q);
			if(cur.day > 0)
				break;
			
		}
		if((j == 4) && (k == -1)) {
			cur.day = atoi(q);
			k = 0;
			break;
		}
		q[k] = p[i];
		k++;		
	}
	j = 0;
	for(i = strlen(p) - 6; i < strlen(p) - 1; i++) {
		r[j] = p[i];
		j++;
	}

	cur.year = atoi(r);

	if(strstr(p, "Jan"))
		cur.mon = 1;
	if(strstr(p, "Feb"))
		cur.mon = 2;
	if(strstr(p, "Mar"))			/* finding current month */
		cur.mon = 3;
	if(strstr(p, "Apr"))
		cur.mon = 4;
	if(strstr(p, "May"))
		cur.mon = 5;
	if(strstr(p, "Jun"))
		cur.mon = 6;
	if(strstr(p, "Jul"))
		cur.mon = 7;
	if(strstr(p, "Aug"))
		cur.mon = 8;
	if(strstr(p, "Sep"))
		cur.mon = 9;
	if(strstr(p, "Oct"))
		cur.mon = 10;
	if(strstr(p, "Nov"))
		cur.mon = 11;
	if(strstr(p, "Dec"))
		cur.mon = 12;

	fclose(ft);
	j = 0;
	if(a.count == 2)
		j = 1;

	 start_date.tm_hour = 0;  start_date.tm_min = 0;  start_date.tm_sec = 0;
	 start_date.tm_mon = a.d[j].mon;		 start_date.tm_mday = a.d[j].day;
	 start_date.tm_year = a.d[j].year;

	 end_date.tm_hour = 0;  end_date.tm_min = 4;  end_date.tm_sec = 0;
	 end_date.tm_mon = cur.mon;			 end_date.tm_mday = cur.day;
	 end_date.tm_year = cur.year;

	start_time = mktime(&start_date);
	end_time = mktime(&end_date);

	seconds = end_time - start_time;

	delay = (int)seconds/86400;
	
	if(delay <= 7) {
		printf("\n\n\t\t *** Book returned %d days before deadline\n\n", 7 - delay);
	}
	else {
		printf("\n\n\t\t !!!!!! Ooops : deadline was %d days before !!!!!!!", delay -7);
		printf("\n\t\t             ***** fine for book = %d Rs\n\n", delay - 7);
		printf("\t fine collected (1 for yes or any integer for NO) :-");
		scanf("%d", &k);
		if(k != 1) {
			printf("\n\t\t!!!!!  book not returned !!!!!\n\n");
			fclose(fs);
			fclose(fb);
			return;
		}
	}	
			
	c.id_no = sid;
	strcpy(c.name, a.name);				/* copy one structure to another */
	c.year = a.year;
	c.count = a.count - 1;
	i = 0;
	if(a.issuedbookid[0] == bid)
		i = 1;
	if(c.count)
		c.issuedbookid[0] = a.issuedbookid[i];
	if(c.count) {
		c.d[0].day = a.d[1].day;
		c.d[0].mon = a.d[1].mon;
		c.d[0].year = a.d[1].year;
	}
	ft = fopen("temp3.txt", "a+");
	rewind(fs);
	while(fread(&a,sizeof(a),1,fs)==1)
	{
		if(a.id_no != sid)
		{	
			fseek(ft, 0, 2);
			fwrite(&a, sizeof(a), 1, ft); 	/*  write all in tempory file except that  */
		}                           		/*  we want to delete  */
		else {
			
		}
	}
	fseek(ft, 0, 2);
	fwrite(&c, sizeof(c), 1, ft);
	fclose(ft);
	fclose(fs);
	remove("student.txt");
	rename("temp3.txt", "student.txt"); 			/* rename temprary file and remove original file */
	ft = fopen("temp3.txt", "a+");
	strcpy(d.name, b.name);	
	strcpy(d.author, b.author);
	strcpy(d.publication, b.publication);
	d.quantity = b.quantity;
	d.price = b.price;
	d.id[0] = bid;
	for(i = 0; i < b.quantity - b.count; i++) {
		d.id[i + 1] = b.id[i];
	}
	b.count--;
	d.count = b.count;
	for(i = 0, j = 0; i < b.count + 1; ) {
		if(b.issue[i] == bid) {				/* copy one structure to another */
			i++;
		}
		else {
			d.issue[j] = b.issue[i];
			i++, j++;
		}
	}
	tmp = 0;
	rewind(fb);	
	while(fread(&b, sizeof(b), 1, fb)==1) { 
		for(i = 0; i < b.count; i++) {
			if(bid == b.issue[i]) {
				tmp = 1;
			}
		}
		if(tmp != 1) { 
			fseek(ft, 0, 2);
			fwrite(&b, sizeof(b), 1, ft); 		/*  write all in tempory file except that  */
								/*  we want to delete  */
		}
		else {
			tmp = 0;
		}
	}
	fclose(fb);
	fclose(ft);
	remove("book.txt");
	rename("temp3.txt", "book.txt");		/* rename temprary file and remove original file */
	fb = fopen("book.txt", "a+");
	fseek(fb, 0, 2);
	fwrite(&d, sizeof(d), 1, fb);
	fclose(fb);
	printf("\n\t ***** book returned succesfully *****\n\n");
	printf("\t do you want to return another book (1 for yes or any integer for NO) :- ");	
	scanf("%d", &tmp);
	if(tmp == 1)
		goto return1;
	else
		printf("\n\n");
}

/*	 just shows issued books with student information */
void issuedbookdata() {
	system("clear");
	student a;
	int j = 1;
	FILE *fp;
	fp = fopen("student.txt", "r");
	if(fp == NULL) {
		printf("\n\n\t\t !!!! no data present !!!!!\n\n");
		return;
	}
        printf("\t ________________________________________________________________________\n");
	printf("\t|No.|  Name of student\t       |  student id |  book id    | issue date |\n");
        printf("\t|___|__________________________|_____________|_____________|____________|\n");
	while(fread(&a, sizeof(a), 1, fp)==1) { 
		
		if(a.count) {
			printf("\t|%02d.|%-25s | %-10d  | %-10d  | %02d-%d-%d |\n", j, a.name, a.id_no, a.issuedbookid[0], a.d[0].day, a.d[0].mon, a.d[0].year);
			j++;
		
		        if(a.count == 2) {
			        printf("\t|   |\t\t\t\t\t     | %-10d  | %02d-%d-%d |\n", a.issuedbookid[1], a.d[1].day, a.d[1].mon, a.d[1].year);
		        }
                 printf("\t|___|__________________________|_____________|_____________|____________|\n");
                }
	}
         printf("\n\n");
	if(j == 1)
		printf("\t\t !!!! no book issued !!!!\n\n");
	printf("\n\t press ENTER to continue");
	getchar();
	printf("\n\n");
}

/*  this function takes current password , and then new password 
	it hide input character by character */	
void changepassword() {					
	system("clear");
	FILE *fp, *ft;
	fp = fopen("tmp1.txt", "a+");
	char str[15], *a, b[15], password[20], c;
	int i = 0;
	ssize_t n;
	a = malloc(15);
	printf("\n\n\n\t*************** change password *****************\n\n");
	ft = fopen("pass.txt", "r");
	
	if(ft != NULL) {
		 while ((c = fgetc(ft)) != EOF)
    		{
        		a[i++] = (char) c;
    		}				/* take current password */
		
		//strcpy(password, a);
		fclose(ft);
	}
	else  {
		
		strcpy(a, "1234");
	}
	
	level1 :
	getchar();
	printf("\n\t****enter current password :--  ");
	n = my_getpass(password, 20, stdin);		/* hide character by character */
	
	if(strcmp(password, a)) 
	{
		printf("\n\t##### error:: wrong password \n \t\t");
		printf("do you want to try again (1 for yes or any integer for NO) :-  ");
		scanf("%d", &i);
		if(i == 1)	
			goto level1;
		else {
			remove("tmp1.txt");
			printf("\n");
			return;
		}
	}
	
	else  
	{
		level2 :
	
		printf("\n\n\t\a\aenter new password(max 15 character) :--  ");
		n = my_getpass(str, 20, stdin);					/* take new password */
		i = strlen(str);
		if(i > 15) {
			printf("\n\t   !!!!! limit of character exceeded !!!!!\n\n");
			printf("\t\t do you want to try again (1 for yes or any integer for NO):- ");
			scanf("%d", &i);
			if(i == 1) {
				getchar();
				goto level2;
			}
			else {
				remove("tmp1.txt");
				return;
			}
		}	
	
		printf("\n\n\tre-enter new password :--  ");
		n = my_getpass(b, 20, stdin);
		
		if(strcmp(str, b)) {
			printf("\n\t******password not matched ************");		/* confirm new password */
			printf("\n\t   do you want try again (1 for yes or any integer for NO) :- ");
			scanf("%d",&i);
			if(i == 1) {
				getchar();
				goto level2;
			}
			else {
				remove("tmp1.txt");
				printf("\n");
				return;
			}
		}
		else  {
			strcpy(password, b);
			printf("\n\t####### password changed successfully #######\n\n");
			fwrite(password, 1, strlen(password) , fp);
			fclose(fp);
			remove("pass.txt");
			rename("tmp1.txt", "pass.txt");
		}			
	}
	free(a);
}

/*	this function takes string input by hiding each character by *  		*/
ssize_t my_getpass (char *lineptr, size_t len, FILE *stream) 
{
struct termios old, new;
int nread = 0;
char c;

/* Turn echoing off and fail if we can't. */
if (tcgetattr (fileno (stream), &old) != 0)			/* function for reading password character by character */
return -1;
new = old;
new.c_lflag &= ~ECHO || ECHOCTL;
if (tcsetattr (fileno (stream), TCSAFLUSH, &new) != 0)
return -1;
/* Read the password. */
while ((c = getchar()) != '\n' && nread + 1 < len) {
if (c == BACKSPACE) {
if (nread > 0) {
nread--;
printf("\b \b");
}
} else {
lineptr[nread++] = c;
printf("*");
}
}
printf("\n");
lineptr[nread] = '\0';

/* Restore terminal. */
(void) tcsetattr (fileno (stream), TCSAFLUSH, &old);
return nread;
}
/* this function handles admin's powers */
void admin() { 
	int i = 0;
	char password[15], a[15], c, *d;
	FILE *fp;
	ssize_t n;
	d = malloc(15);
	fp = fopen("pass.txt", "r");
	
	if(fp != NULL) {
		 while ((c = fgetc(fp)) != EOF)
    		{
        		d[i++] = (char) c;
    		}
		
		strcpy(password, d);
		fclose(fp);
	}
	else  {
		strcpy(password, "1234");
		
	}
					/* check for password */
	
	level :
	getchar();
	printf("\n\n\tEnter password :-  ");
	n = my_getpass(a, 20, stdin);
	
	if(strcmp(password, a)) {
		printf("\n\t##### error in loging you in :: wrong password \n \t\t  ****** try again *****");
		printf("\n\t Do you want to try again (1 for YES or any integer for NO ) :- ");
		scanf("%d", &i);
		if(i == 1)
			goto level;
		else
			return;
	}
	else {
	printf("\n\n\t\t ******  LOADING  ****** \n");
	sleep(1.0);	
	
		system("clear");
		printf("\n\n\n\t-------------------------------------------------------------------------------------------------\n");
		printf("\t*******************************  ADMINISTRTOR ******************************************************\n");
		printf("\t___________________________________________________________________________________________________\n\n\n");
		printf("\tGive your choice \n\n");
		while(1) {
			i = printmenu();
			switch(i) {
			case 1: /* Enroll new student	*/
				enroll();
				break;
			case 2: /* remove student */
				removestudent();
				break;
			case 3: /* Add book to library */
				addbook();
				break;
			case 4: /* remove book */
				removebook();
				break;
			case 5: /* Edit book's data */
				editbook();
				break;
			case 6: /* search book  */
				searchbook();
				break;
			case 7: /* Issue books */
				issuebook();
				break;
			case 8: /* return book */
				returnbook();
				break;
			case 9: /* Logout and Go to login page */
				return;
				break;
			case 0: /* Change password */
				changepassword();
				break;	
			case 11: /* data of issued book with student */
				issuedbookdata();
				break;
			default : /* wrong choice */
				printf("\t\t!!!!!!!!! wrong choice !!!!!!!!\n\n");	
				break;	
			}
		}
	}
}

/* this function handles student */
void studentlogin() {
	int ch;
	system("clear");
	printf("\n\n\n\t------------------------------------------------------------------------------------------------\n");
	printf("\t*******************************  STUDENT  ******************************************************\n");
	printf("\t_________________________________________________________________________________________________\n\n");
	levela :
	printf("\n\n\tGive your choice \n\n");
	printf( "	1. search book \n"\
	        "	2. return to login page \n");
	printf("\n\t your choice is :- ");
	scanf("%d", &ch);	
	if(ch == 1) {
		searchbook();
		goto levela;
	}	
}
/* this function plays important in changing power from student to admin and vie-versa */
int login(void){
	int ch;
	level0 :
	system("clear");
	printf("\n\n\n\t-------------------------------------------------------------------------------------------------\n");
	printf("\t*******************************  LOGIN PAGE ******************************************************\n");
	printf("\t___________________________________________________________________________________________________\n\n\n");
	printf("\t\twant to login as :--\n\n");
	printf("\t1. Administrator (require password)\n"\
		"\t2. Student (no password)\n"\
		"\t3. Exit \n");
	printf("\n\tEnter your choice :- ");
	scanf("%d", &ch);
	if(ch == 1) {
		admin();
		goto level0;
	}
	else if(ch == 2) {
		studentlogin();
		goto level0;
	}
	else {
		return 0;
	}
}

int printmenu() {
	int choice;
	printf( "	1. Enroll student to library \n"\
	        "	2. Remove student from library \n"\
		"	3. Add book to library \n"\
		"	4. Remove book from library \n"\
		"	5. Edit book's data \n"\
		"	6. Search books \n"\
		"	7. Issue book \n"\
		"	8. Return book \n"\
		"	9. log out and go to login page \n"\
		"	0. Change password \n"\
		"	11. show issued books with student\n");
	printf("\n\tyour choice is :- ");
	scanf("%d", &choice);
	return choice;		
}

/* this function convert string to lower case */
void lower_string(char *string)
{
	while(*string)
	{
		if ( *string >= 'A' && *string <= 'Z' )
		{
			*string = *string + 32;
		}
		string++;
	}
}
 
/* this function counts total no. of books and students present */
void refreshcnt(int *cntbook, int *cntstud) 
{			/* function for refreshing count */
	FILE *fp;
	student s;
	book b;
	fp = fopen("student.txt", "a+");
	if(fp != NULL) {
		while(fread(&s,sizeof(s),1,fp)==1)
			(*cntstud)++;
	}
	fclose(fp);
	fp = fopen("book.txt", "a+");
	if(fp != NULL) {
			while(fread(&b,sizeof(b),1,fp)==1)
				(*cntbook)+= b.quantity;
		}
	fclose(fp);
}
