#include <stdio.h>
#include <stdlib.h>

typedef struct node_tag{		//structure
	char name[30];
	char degree[30];
	int StudNum;
	struct node_tag *next;
	struct node_tag *prev;
	struct node_tag *friends;
}node;

void printMenu(){						// prints the menu
	printf("\n************************* MENU ****************************\n\n");
	printf("\t[1] Add Student\n");
	printf("\t[2] Add a Friend on Student\n");
	printf("\t[3] Edit Student\n");
	printf("\t[4] Delete Student\n");
	printf("\t[5] Delete A Friend Of A Student\n");
	printf("\t[6] Delete All Students Including Friends\n");
	printf("\t[7] Delete All Friends Of A Student\n");
	printf("\t[8] View Students\n");
	printf("\t[9] View Friends Of A Student\n");
	printf("\t[10] Load Data\n");
	printf("\t[11] Save Data\n");
	printf("\t[12] Exit\n\n");
	printf("***********************************************************\n\n");
}

void AddStudent(node *h, node *t){	// adds a student in the linked list(in ascending student numbers)
	node *temp, *newnode;
	temp = h;

	newnode = (node *)malloc(sizeof(node));	// newnode creation
    printf("\nEnter Student Number: ");
	scanf("%d", &newnode->StudNum);
	printf("Enter Name: ");
	scanf("%s", newnode->name);
	printf("Enter Course: ");
    scanf("%s", newnode->degree);
	newnode->next = newnode->prev = NULL;
	newnode->friends = (node *)malloc(sizeof(node));
    newnode->friends->next = (node *)malloc(sizeof(node));
	newnode->friends->next->next = newnode->friends->prev = newnode->friends->friends = newnode->friends->next->friends = NULL;
	newnode->friends->next->prev = newnode->friends;

	while(temp->next!=t && newnode->StudNum > temp->next->StudNum) temp=temp->next;	// lets temp point to the node before the place where the newnode will be inserted
	newnode->next = temp->next;		// newnode insertion
	newnode->prev = temp;
	temp->next->prev = newnode;
	temp->next = newnode;
	
	printf("Student successfully added!\n");
}

void AddFriend(node *h, node *t){		// adds a friend to a student (in a mutual/symmetric manner)
	node *newnode1, *newnode2, *temp1, *temp2, *temp3;
	int sn1, sn2;
	temp1 = h->next;
	temp2 = h->next;
	
	if(h->next == t){	// if dummy nodes points to each other
		printf("\nNo student added yet!\n");
		return;
	}
	
	printf("\nEnter Student Number You Want To Add Friends To: ");
	scanf("%d", &sn1);

	while(temp1->next != NULL && sn1 != temp1->StudNum) temp1=temp1->next;	// lets temp1 point to the node containing the specified student number 
	if(temp1->next == NULL) printf("Student Not Found.\n");	// prints if the desired value is not in the linked list
	else{					// if student is found
        printf("Enter Student Number Of Friend You Want To Add: ");
		scanf("%d", &sn2);
		
		if(sn1 == sn2){	// if student added himself/herself as a friend
			printf("A student cannot add himself/herself as a friend!\n");
            return;
		}
        
        while(temp2->next != NULL && sn2 != temp2->StudNum) temp2=temp2->next;	// lets temp2 point to the node containing the friend's student number

        if(temp2->next == NULL) printf("Target Friend Not Found!\n");	// if friend is not in the linked list
		else{					// creation of newnode1(for student's studNum) and newnode2(for friend's studNum)
			newnode1 = (node *)malloc(sizeof(node));
			newnode2 = (node *)malloc(sizeof(node));
			newnode1->StudNum = temp1->StudNum;
			newnode2->StudNum = temp2->StudNum;
			newnode1->next = newnode2->next = newnode1->prev = newnode2->prev = newnode1->friends = newnode2->friends = NULL;

			temp3 = temp1->friends;	// lets temp3 point to the list of friends of the student.
			while(temp3->next->next != NULL && sn2 > temp3->next->StudNum) temp3=temp3->next;	// lets temp point to the node before the place where the newnode will be inserted
			newnode2->next = temp3->next;	// friend insertion in the friends list of student
			newnode2->prev = temp3;
			temp3->next->prev = newnode2;
			temp3->next = newnode2;
                  
			temp3 = temp2->friends;	// lets temp3 point to the list of friends of friend specified
			while(temp3->next->next != NULL && sn1 > temp3->next->StudNum) temp3=temp3->next;	// lets temp point to the node before the place where newnode will be inserted
			newnode1->next = temp3->next;	// student inssertion in the friends list of friend
			newnode1->prev = temp3;
			temp3->next->prev = newnode1;
			temp3->next = newnode1;
			printf("%d and %d are now friends.\n", sn1, sn2);
		}
    }
}

void edit(node *h, node *t){	// allows editting of student information except his/her student number
	int sn1;
	node *temp;
	temp = h->next;
	
	printf("Enter Student Number: ");
	scanf("%d", &sn1);

	while(temp != t && sn1 != temp->StudNum) temp = temp->next;	// lets temp point to the node to be edited
	if(temp == t) printf("Student Not Found.\n");	// if student number specified doesn't exist
	else{			// if student was found
		printf("Previous name: %s\n", temp->name);	// editing porion
		printf("Enter new name: ");
		scanf("%s", temp->name);
		printf("Previous Course: %s\n", temp->degree);
		printf("Enter new name: ");
		scanf("%s", temp->degree);
		printf("Edit Successful.\n");
	}
}

void delete(node *h, node *t){		// deletes a student along with his/her friends list(in a mutual/symmetric manner)
	int sn1, sn2;
	node *temp1, *temp2, *temp3, *temp4;
	temp1 = h->next;

	printf("Enter Student Number: ");
	scanf("%d", &sn1);

	while(temp1 != t && sn1 != temp1->StudNum) temp1 = temp1->next;	// lets temp1 point to the node to be deleted
	if(temp1 == t) printf("Student Not Found.\n");	// if specified student number doesn't exist
	else{
		temp2 = temp1->friends;	// lets temp2 point to the friends list of the student to be deleted
		while(temp2->next->next != NULL){	// while the friends list of the student is not empty
			sn2 = temp2->next->StudNum;	// equates sn2 to the student number of the friend of student to be deleted
			temp3 = h->next;
			while(sn2 != temp3->StudNum) temp3 = temp3->next;	// lets temp3 point to the friend of student
			temp4 = temp3->friends->next;
			while(temp4->StudNum != sn1) temp4 = temp4->next;	// lets temp4 point to the student to be deleted in the friends list of other students
			temp4->prev->next = temp4->next;	// deleting student in other's friends list
			temp4->next->prev = temp4->prev;
			free(temp4);
			temp2->next = temp2->next->next;	// deleting the friends of student to be deleted
			free(temp2->next->prev);
			temp2->next->prev = temp2;
		}
		free(temp2->next);		// deleting dummy nodes in friends list
		free(temp2);
		temp1->prev->next = temp1->next;	// deleting the student to be deleted
		temp1->next->prev = temp1->prev;
		free(temp1);
		printf("Delete Successful.\n");
	}
}

void deleteAFriend(node *h, node *t){	// deletes a friend of a student (in a mutual/symmetric manner)
	int sn1, sn2;
	node *temp1, *temp2;
	temp1 = h->next;

	printf("Enter Student Number: ");
	scanf("%d", &sn1);

	while(temp1 != t && sn1 != temp1->StudNum) temp1 = temp1->next;	// lets temp1 point to the node where a friend is to be deleted
	if(temp1 == t) printf("Student Not Found.\n");	// if student number specified is not in the linked list
	else{
		printf("Enter Student Number Of Friend: ");
		scanf("%d", &sn2);
		temp2 = temp1->friends->next;
		while(temp2->next != NULL && temp2->StudNum != sn2) temp2 = temp2->next;	// lets temp2 point to the friend of student to be deleted
		if(temp2->next == NULL) printf("Friend Not Found.\n");	// if specified friend's student number is not in the linked list
		else{
            temp2->prev->next = temp2->next;	// deletes the friend in the student's list of friends
			temp2->next->prev = temp2->prev;
			free(temp2);
			temp1 = h->next;
			while(temp1->StudNum != sn2) temp1 = temp1->next;	// lets temp1 point to the friend deleted in the student's friends list
			temp2 = temp1->friends->next;
			while(temp2->StudNum != sn1) temp2 = temp2->next;	// lets temp2 point to the student in the friends list of the friend
			temp2->prev->next = temp2->next;	// deletes the student in the friend's list of friends
			temp2->next->prev = temp2->prev;
			free(temp2);
			printf("Delete Successful.\n");
		}
    }
}

void deleteAll(node *h, node *t){			// deletes all students including their friends
	node *temp1, *temp2;
	temp1 = h; 
	if(h->next == t) printf("\nNo student to be deleted. \n");	// if linked list is empty
	else{
		while(h->next != t){
			temp2 = temp1->next->friends;
			
            while(temp2->next->next != NULL){
				temp2->next = temp2->next->next;	// deletes friends list of student
				free(temp2->next->prev);
				temp2->next->prev = temp2;
			}
		
			temp1->next = temp1->next->next;	// deletes student	
			free(temp1->next->prev);
			temp1->next->prev = temp1;			
		}printf("\nAll students deleted.\n");
	}
}

void deleteFriends(node *h, node *t){	// deletes all friends of a student
	int sn1, sn2;
	node *temp1, *temp2, *temp3, *temp4;
	temp1 = h->next;

	printf("\nEnter Student Number: ");
	scanf("%d", &sn1);

	while(temp1 != t && sn1 != temp1->StudNum) temp1 = temp1->next;	// lets temp point to the student where friends are to be deleted
	if(temp1 == t) printf("Student Not Found.\n");	// if student number doesn't exist
	else{
		temp2 = temp1->friends;
		while(temp2->next->next != NULL){
			sn2 = temp2->next->StudNum;	// equates sn2 to the student number of the friend of the student
			temp3 = h->next;
			while(sn2 != temp3->StudNum) temp3 = temp3->next;	// lets temp3 point to the friend of the student
			temp4 = temp3->friends->next;
			while(temp4->StudNum != sn1) temp4 = temp4->next;	// lets temp4 point to the student in the friends list of friend
			temp4->prev->next = temp4->next;	// removes student in the friends list of friend
			temp4->next->prev = temp4->prev;
			free(temp4);
			temp2->next = temp2->next->next;	// removes friend in the friends list of student
			free(temp2->next->prev);
			temp2->next->prev = temp2;
		}printf("All Friends Delete Successful.\n");
	}
}

void view(node *h, node *t){	// views all the students along with their friends list
	node *temp1, *temp2;
	temp1 = h->next;
	
	printf("\n\t\t     STUDENT RECORD:");
	if(temp1 == t) printf("\n\n\t\t\t  EMPTY");	// if recod is empty
	while(temp1 != t){
		temp2 = temp1->friends->next;
		printf("\n\nSTUDENT %d", temp1->StudNum);
		printf("\nName: %s", temp1->name);
		printf("\nCourse: %s", temp1->degree);
		printf("\nFRIENDS: ");
		if(temp2->next == NULL) printf("NONE");	// if friends list is empty
		else{
			do{			// prints friends list
				printf("%d ", temp2->StudNum);
				temp2 = temp2->next;
			}while(temp2->next != NULL);
		}
		temp1 = temp1->next;
	}printf("\n\n");
}

void viewFriends(node *h, node *t){	// prints a student's information and his/her friends list
	node *temp1, *temp2;
	int sn1;
	temp1 = h->next;

	if(temp1 == t) printf("\nRecord is empty.\n");	// if no student was added
	else{
		printf("Enter Student Number: ");
		scanf("%d", &sn1);
		while(temp1 != t && temp1->StudNum != sn1) temp1 = temp1->next;	// lets temp1 point to the student to be viewed
		if(temp1 == t) printf("Student Not Found.");	// if student number specified doesn't exist
		else{
			temp2 = temp1->friends->next;
			printf("FRIENDS: ");
			if(temp2->next == NULL) printf("NONE");	// if friends list is empty
			else{
				do{			// prints friends list of student
					printf("%d ", temp2->StudNum);
					temp2 = temp2->next;
				}while(temp2->next != NULL);
			}
		}putchar('\n');
	}
}

void load(node *h, node *t){	// loads the saved record and stores it in the linked list
	node *newnode1, *newnode2, *temp1, *temp2;
	int detector, counter;
	FILE *fp;
	temp1 = h;
	
	fp = fopen("fb.txt", "r");
	if(fp != NULL){
		fscanf(fp, "%d ", &detector);
		if(detector == 1){
			while(fp != NULL && !feof(fp)){
				newnode1 = (node *)malloc(sizeof(node));	// newnode1 creation
				fscanf(fp, "%s %d %s ", newnode1->name, &newnode1->StudNum, newnode1->degree);
				fscanf(fp, "%d", &counter);
				newnode1->next = temp1->next;
				newnode1->prev = temp1;
				temp1->next->prev = newnode1;
				temp1->next = newnode1;
				newnode1->friends = NULL;
				temp1 = newnode1;
				newnode1->friends = (node *)malloc(sizeof(node));
				newnode1->friends->next = (node *)malloc(sizeof(node));
				newnode1->friends->next->next = newnode1->friends->prev = newnode1->friends->friends = newnode1->friends->next->friends = NULL;
				newnode1->friends->next->prev = newnode1->friends;
                temp2 = newnode1->friends;
				while(counter!=0){
					newnode2 = (node *)malloc(sizeof(node));	// newnode2 creation(for friends list)
					fscanf(fp, " %d", &newnode2->StudNum);
					counter -= 1;
					newnode2->friends = NULL;
					newnode2->next = temp2->next;
					newnode2->prev = temp2;
					temp2->next->prev = newnode2;
					temp2->next = newnode2;
					temp2 = newnode2;
				}fscanf(fp, "\n");
			}
		}fclose(fp);
		printf("Records Loaded.\n");
	}
}

void save(node *h, node *t){	// saves the students' record to a file
	node *temp1, *temp2;
	int counter=0;
    FILE *fp;
	temp1 = h->next;
	fp = fopen("fb.txt", "w");

	if(h->next == t) fprintf(fp, "0 ");
	else fprintf(fp, "1 ");
	while(temp1->next != NULL){
		temp2 = temp1->friends->next;
        
        while(temp2->next != NULL){	// counts the number of friends a student has
			counter += 1;
			temp2 = temp2->next;
		}
		
		temp2 = temp1->friends->next;
		fprintf(fp, "%s %d %s ", temp1->name, temp1->StudNum, temp1->degree);	// writes students' record to the file
		fprintf(fp, "%d", counter);
		while(counter != 0){	// writes friends list of student
			fprintf(fp, " %d", temp2->StudNum);
			counter -= 1;
			temp2 = temp2->next;
		}fprintf(fp, "\n");
        temp1 = temp1->next;
	}fclose(fp);
	printf("Records Saved!\n");
}

int main(){
	node *head, *tail;
	int choice, value;

	head = (node *)malloc(sizeof(node));	// doubly linked list creation
    tail = (node *)malloc(sizeof(node));
	head->next = tail;
	tail->prev = head;
	head->prev = tail->next = head->friends = tail->friends = NULL;
	
	do{						// functions while the user doesn't choose to exit the program
		printMenu();
       	printf("Choice: ");
		scanf("%d", &choice);
		switch(choice){
			case 1: AddStudent(head, tail);
					break;			
			case 2: AddFriend(head, tail);
					break;
			case 3: edit(head, tail);
					break;
			case 4: delete(head, tail);
					break;
			case 5: deleteAFriend(head, tail);
					break;
			case 6: deleteAll(head, tail);
					break;
			case 7: deleteFriends(head, tail);
					break;
			case 8: view(head, tail);
					break;
			case 9: viewFriends(head, tail); 
                 	break;
			case 10: load(head, tail); 
					break;
			case 11: save(head, tail);
					break;
			case 12: printf("Thank you for using the program.");
					exit(12);
			default: printf("Invalid input! Please choose a valid one.\n");	// if the user's choice is not on the menu
					break;
		}
	}while(choice != 0);
}