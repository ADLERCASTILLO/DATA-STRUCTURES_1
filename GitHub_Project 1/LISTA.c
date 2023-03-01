/*    LINKED LIST
    Copyright (C) 2023  Adlerx36

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.*/




#include <stdio.h>
#include <stdlib.h> //Use of the functions malloc, calloc, realloc and free.

struct listNode{   //Struct
  char data;   //char call data
  struct listNode *nextPtr;  //pointer to Struct 
};

typedef struct listNode LISTNODE; // From struct listNode we generate a new data type call 'LISTNODE' (alias)
typedef LISTNODE *LISTNODEPTR; //Pointer to a struct of LISTNODE type

void insert (LISTNODEPTR *, char);     //add function
char delete (LISTNODEPTR *, char);     //delete function
int isEmpty (LISTNODEPTR);             //verify if the list is empty
void printList (LISTNODEPTR);          //Print list
void instructions (void);              //Menu

int main()
{
  LISTNODEPTR startPtr=NULL; //StartPtr is generated from LISTNODEPTR
  int choice;   //option
  char item;    //A-Z

  instructions(); //Invocation of instructions. Menu on screen.

  while (choice != 3)
    {
      printf("? ");
      scanf("%d", &choice);
      switch (choice)
	{
	case 1:
	  printf("Enter a character: ");
	  scanf("\n%c", &item);
	  insert(&startPtr, item);
	  printList(startPtr);
	  break;
	case 2:
	  if (!isEmpty(startPtr)){
	    printf("Enter character to be deleted: ");
	    scanf("\n%c", &item);

	    if (delete(&startPtr, item)){ //Invocation of the 'delete  function' and send a direction to it.
	      printf("%c deleted.\n", item);
	      printList(startPtr);
	    }
	    else
	      printf("List is empty or the element doesn't exist.\n\n");

	    break;
	  default:
	    printf("Invalid choice.\n\n");
	    instructions();
	    break;
	  }

	  printf("? ");
	  scanf("%d", &choice);
	}

    }
  printf("End of run.\n");
  return 0;

}

void instructions(void)
{
  printf("Enter your choice:\n"
	 "	1 to insert an element into the list.\n"
	 "	2 to delete an element from the list.\n"
	 "	3 to end.\n");
}

void insert (LISTNODEPTR *sPtr, char value) //START
{
  LISTNODEPTR newPtr, previousPtr, currentPtr;  //Three pointers
  
  newPtr = malloc(sizeof(LISTNODE));

  if (newPtr != NULL){  //Generates a valid direction
  	
    newPtr->data = value;    
    newPtr->nextPtr = NULL;

    previousPtr = NULL;
    currentPtr = *sPtr;
    //printf("contenido newPtr %p \n",newPtr);
	//printf("contenido previousPtr %p \n",previousPtr);
    //printf("contenido currentPtr %p \n",currentPtr);
    //printf("contenido sPtr %p \n",*sPtr);
    
   
    while (currentPtr !=NULL && value > currentPtr->data){ //Comparing letters. Both conditions are met (&&)
      previousPtr = currentPtr;  
      currentPtr = currentPtr->nextPtr;
    
         }

    if (previousPtr == NULL){       // This group of lines only applies with the first element.
      newPtr->nextPtr = *sPtr;
      *sPtr = newPtr;
      printf("contenido sPtr2 %p \n",*sPtr);
         }
         
    else{
      previousPtr->nextPtr = newPtr;
      newPtr->nextPtr = currentPtr;
    }
  }
  else
    printf("%c not inserted. No memory available.\n", value);
}  //END

char delete(LISTNODEPTR *sPtr, char value)
{
  LISTNODEPTR previousPtr, currentPtr, tempPtr; //3 struct ponters

  //if (value == (*sPtr)->data){
  if(value == (*sPtr)->data){  //This 'if' is for the fist element.
    *sPtr = (*sPtr)->nextPtr;
    free(tempPtr);
    return value;
  }
  else{ //Otherwise
    previousPtr = *sPtr;  
    currentPtr = (*sPtr)->nextPtr;

    while (currentPtr != NULL && currentPtr->data != value){
      previousPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
    }

    if (currentPtr != NULL){
      tempPtr = currentPtr;
      previousPtr->nextPtr = currentPtr->nextPtr;
      free(tempPtr);  //Free space [free(Memory Direction)]
      return value;
    }
  }
  return '\0'; // It means that the added element is not on the list.
}              // Because it returns a character type, and end of chain is put

int isEmpty(LISTNODEPTR sPtr)
{
  return sPtr == NULL;
}

void printList(LISTNODEPTR currentPtr)
{
  if (currentPtr == NULL)
    printf("List is empty. \n\n");

  while (currentPtr != NULL){
    printf("%c --> ", currentPtr->data);
    currentPtr = currentPtr->nextPtr;
  }
  printf("NULL\n\n");
}
