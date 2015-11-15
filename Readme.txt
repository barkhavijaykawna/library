NAME OF PROJECT: LIBRARY MANAGEMENT SYSTEM

Name: BARKHA KAWNA
misno:141503005

DEscription of project:-

The code is divided into 3 files main.c, project.c and project.h.
main.c  :  It shows total no. of students and books in librarary and for login simply call login function which is present in  project.c .
	
project.h : It contains all function and data type declaration.
	
project.c : It login option of student and admin .In case admin demands password for login .
	It gives following option to Admin through admin() function :-
	1. add student :-  It takes  id , name , year of student as input for enrolling. It first checks for repetation of name and id and then enrolls student.
	2.remove student :- It first finds the student . After student found checks if books are issued to student or not and then confirm before removing student.	
	3. add book :- It takes all data of book and check for repetation . If match not found then directly add book and if match found then ask for adding extra copies of that 			book.
	4. remove book :- It checks if entered book is present . If found and some copies of book are issued , then also doesn't remove book from library.
	5. edit  book :- If entered book is found in library ,then Admin can change name of book, author and publication.
	6. serch book :- It first give choice for searching. In case of string , it gives result  for 	substring also.
	7. issue book :- It takes id is of student and book .It checks for no.of books or issued book to student and availability of book.
	8. return book :- It takes id is of student and book. Check for correctness of data and set fine in case of more than 7 days of limit.
	9. logout :- go to login page.
	0. change password :- It takes current password checks it and then take new password .
	
	It gives only option to search  book to student.
	
	 
	
	
	
