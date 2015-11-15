/*****************************************************************************
 * Copyright (c) barkha kawna bkawana707@gmail.com
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

 /* this is main() function in program, it calls the login function
			 and ends the program when login function returns  */

#include<stdio.h>
#include"project.h"
int cntbook = 0, cntstud = 0;	
int main(int argc, char *argv[])
{
	refreshcnt(&cntbook, &cntstud);	
	system("clear");
	int choice;
	printf("\n\n\n\t\t-----------------------------------------------------------------------------------------------------------\n");
	printf("\t\t*************************** WELCOME TO HOME PAGE OF LIBRARY SYSTEM *****************************************\n");
	printf("\t\t_____________________________________________________________________________________________________________\n\n\n\n");
	printf("\t\t\t\t###### TOTAL NUMBER OF BOOKS AVILABLE ######\n");
	printf("\t\t\t\t------------------- %d -----------------------\n\n", cntbook);
	printf("\t\t\t\t######  TOTAL NUMBER OF STUDENT ENROLLED #####\n");
	printf("\t\t\t\t------------------- %d -----------------------\n\n\n", cntstud);
	printf("\tDO you want to login : (1 for YES or 2 for NO) ::-- ");
	level :	
	scanf("%d", &choice);
	if(choice == 1) {		
		return login();
	}
	else if(choice == 2) {
		return 0;
	}
	else {
		printf("\twrong choice re-enter choice\n");
		goto level;
	}
}
