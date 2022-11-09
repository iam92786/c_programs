//write a function to find nth node from the last in Linked list

#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0

typedef int bool_t; 

typedef struct node{

		int data;
		struct node *next;//self refrencial pointer
}node_t;

typedef struct list{
		struct node *head;//head of linked list
		int node_count;

}list_t;

//Function Declaration
void remove_multiple_occure_num_from_list(list_t *lptr);
void init_list(list_t *lptr);
bool_t list_empty(list_t *lptr);
node_t *creat_node (int data);
void add_node_at_first_pos(list_t *lptr, int data);
void add_node_at_last_pos(list_t *lptr, int data);
void add_node_at_specific_pos(list_t *lptr, int data, int pos);
void free_list(list_t* lptr);
void delete_node_at_last_pos(list_t *lptr);
void delete_node_at_first_pos(list_t *lptr);
void delete_node_at_specific_pos(list_t *lptr, int pos);
void Display_list(list_t *lptr);
int menu(void);

int main (void)
{
	int pos, data;
	list_t l1;
	init_list(&l1);

	while( 1 )
    {
        int choice = menu();
        switch( choice )
        {
            case 0:
                free_list(&l1);
                exit(0);
            
            case 1:
                printf("enter the data: ");
                scanf("%d", &data);
                add_node_at_first_pos(&l1,data);
                break;

            case 4: //Add_node_at_specific_position
               while( 1 ){
                    //accpt position from the user
                    printf("enter the position : ");
                    scanf("%d", &pos);
                    //validate position
                    //position is valid only if => ( pos >= 1 && pos <= count_nodes + 1 )
                    if( pos >= 1 && pos <= l1.node_count + 1 )
                        break;//while loop gets breaked due to entering valid position

                    printf("invalid position !!!\n");
                }

                printf("enter the data: ");
                scanf("%d", &data);
                //if pos is valid then we can add node into the list at that valid position
                add_node_at_specific_pos(&l1, data, pos);
                break;

            case 2:
                delete_node_at_last_pos(&l1);
                break;

            case 3:
                Display_list(&l1);
                break;

            case 5:
                remove_multiple_occure_num_from_list(&l1);
                break;

			default:
				printf("Invalid Input \n");
				break;
			}

        }

		return 0;
}

/*
void remove_multiple_occure_num_from_list(list_t *lptr)
{
    //Remove multiple occure number from the list
        node_t *trav1, *trav2;
        int node_pos, flag;
        for (trav1 = lptr->head; trav1 != NULL; trav1 = trav1->next)
        {
                //temp1 = trav1->data;
                flag = 0;
                node_pos = 0;
                for(trav2 = lptr->head; trav2 != NULL; trav2 = trav2->next)
                {
                        node_pos++;

                        if (trav1->data == trav2->data)
                        {
                            if(flag > 0)
                            {
                                    printf(" 2nd time Dup : %d and its pos = %d\n",trav2->data,node_pos);
                                    delete_node_at_specific_pos(lptr, node_pos);
                            }
                            flag++;
                        }
                                      
                }
                Display_list(lptr);
        }
        
}
*/

void remove_multiple_occure_num_from_list(list_t *lptr)
{
		node_t *trav1, *trav2, *prev;
		int node_pos, flage;
		for(trav1 = lptr->head; trav1; trav1 = trav1->next)
		{
				flage = 0;
				for(trav2 = lptr->head; trav2; trav2 = trav2->next)
				{
						//printf(">> trav1 = %d, trav2 = %d\n",trav1->data, trav2->data);

						if (trav1->data == trav2->data)
						{
								if(flage)
								{
										//printf(">>>mult occurance : %d\n",trav2->data);
										//printf(">>>*prev val : %d\n",prev->data);

										//write logic for delete node here

										prev->next = trav2->next;
										free(trav2);
										lptr->node_count--;
										continue;
								}
								flage++; //if number occure more than two times.
						}
						
						//At the end of current iterartion
						prev = trav2;
		
				}
				printf("\n");
		}
}

void delete_node_at_first_pos(list_t *lptr)
{
            //check list is empty or not
            if(list_empty(lptr))
            {
                    printf("Linked list is empty ! ! !\n");
            }
            else
            {   
                    //Linked list is not empty
                    node_t *temp;

                    //stored head value in trav pointer variable
                    temp = lptr->head;

                    //update head value of linked list
                    lptr->head = lptr->head->next;

                    //free the memory
                    free(temp);
                    temp = NULL;

                    //decrement node count
                    lptr->node_count--;


            }
            //if list is not empty then delete first node

}
void delete_node_at_specific_pos(list_t *lptr, int pos)
{
        int i;
        //check Linked list is empty or not
        if (list_empty(lptr))
        {
                printf("Linked list is empty ! ! !\n");

        }
        else
        {
                //if Linked list is not empty then check pos variable value
                if(pos == 1)
                {
                        //if pos == 1 then call del_at_first_position
                        delete_node_at_first_pos(lptr);
                }
                else if(pos == lptr->node_count)
                {
                        //if pos val == lptr->node_count then call del_node_at_last_pos
                        delete_node_at_last_pos(lptr);
                }
                else
                {
                        //else ,code for in between position
                        node_t *trav, *temp;
                        trav = lptr->head;

                        //traverse to reach node position given by users
                        while (i < pos-1)
                        {
                                i++;
                                trav = trav->next;
                        }

                        //delet the node
                        temp = trav->next;
                        trav->next = trav->next->next;

                        //free memory
                        free(temp);

                        temp = NULL;

                        //decrement node count
                        lptr->node_count--;


                }
        }
        
}

void Display_list(list_t *lptr)
{
		printf("\nLinked List Elements : ");

		if(list_empty(lptr))
		{
				//list is Empty
				printf("Linked List is empty !!!\n");
		}
		else
		{
			//linked list is not Empty
			node_t *trav;
			trav = lptr->head;
			while(trav)
			{
				printf("-> %d ",trav->data);
				trav = trav->next;
			}
			printf("-> NULL\n");
			printf("No. of nodes in Linked list are : %d\n",lptr->node_count);
		}
}

void delete_node_at_last_pos(list_t *lptr)
{
		if (list_empty(lptr))
		{
				printf("List is Emptr\n");
		}
		else
		{
			//only one node
			if(lptr->head->next == NULL)
			{
					free(lptr->head);
					lptr->head = NULL;
					lptr->node_count = 0;
			}
			else
			{
					//more than one node
					node_t *trav;
					trav = lptr->head;

					//start traverse to find last node
					while(trav->next->next != NULL)
					{
							trav = trav->next;
					}
					//delete last node
					free(trav->next);

					//make NULL, next of last node 
					trav->next = NULL;

					//decrement the node count
					lptr->node_count--;

			}
		}
}

void free_list(list_t *lptr)
{
		if(list_empty(lptr))
		{
				//Linked List is Empty
				printf("Linked List is Empty !!!\n");
		}
		else
		{
				//Linked LIst is not Empty 
				while (!list_empty(lptr))
				{
						delete_node_at_last_pos(lptr);
				}
				printf("Linke List Freed Successfully !, All node are Released\n");

				
		}
}

void add_node_at_specific_pos(list_t *lptr, int data, int pos)
{
	int i;
	if(pos == 1)
	{
			//add node at first pos
			add_node_at_first_pos(lptr, data);
	}
	else if(pos == lptr->node_count + 1)
	{
			//add node at last pos
			add_node_at_last_pos(lptr, data);
	}
	else
	{
			//add node in between first and last pos
			//creat node
            //printf(">>>>>line no : 317\n");
            
			node_t *new_node;
			new_node = creat_node(data);

			//start traverse of list from first position
			node_t *trav;
			trav = lptr->head;

			//traverse till position (pos - 1)
			i = 1;
			while(1 < pos - 1)
			{
				i++;
				trav = trav->next;
			}
			//add node at specific position
			new_node->next = trav->next;
			trav->next = new_node;
			//increment node count
			lptr->node_count++;			


	}

}

void add_node_at_last_pos(list_t *lptr, int data)
{
		//create node
		node_t *new_node;
		new_node = creat_node (data);

		//first check list is empty or not
		if (list_empty(lptr))
		{
				//list is empty
				lptr->head = new_node;
				lptr->node_count++;
		}
		else
		{
				//list is not empty
				node_t *trav;
				trav = lptr->head;

				while (trav->next != NULL)
				{
					//traverse the list till last node
						trav = trav->next;
				}
				//add node at last position
				trav->next = new_node;
				lptr->node_count++;
				
		}
		
}

void add_node_at_first_pos(list_t *lptr, int data)
{
		//create node
		node_t *new_node;
		new_node = creat_node(data);

		//first check list is empty
		if(list_empty(lptr))
		{
				//empty linked list
				lptr->head = new_node;
				++lptr->node_count;
		}
		else
		{
				//list is not empty
				new_node->next = lptr->head;
				lptr->head = new_node;
				lptr->node_count++;

		}
}

node_t *creat_node (int data)
{
		node_t *new_node;
        new_node = (node_t*) calloc(1, sizeof(node_t));
        if(new_node == NULL)
        {
                perror("new_node : Calloc Failed !");
                exit(1);
        }
		new_node->next = NULL;
        new_node->data = data;
        return new_node;

}

void init_list(list_t *lptr)
{
		lptr->head = NULL;
		lptr->node_count = 0;
}

bool_t list_empty(list_t *lptr)
{
		if(lptr->head == NULL)
		{
				return true;
		}
		else
		{
				return false;
		}
}

int menu(void)
{
    int choice;

    //display menu list
	printf("\n______________________________________________\n");
    printf("||***Singly linear linked list operations***||\n");
    printf("0. exit\n");
    printf("1. add node at First position\n");
    printf("2. delete node at last position\n");
    printf("3. display list\n");
    printf("4. add node at specific position\n");
    printf("5. Remove multiple occure of number in Linked list\n");

    
    //accept choice from user
    printf(">>Enter the choice : ");
    scanf("%d", &choice);

    //return user entered choice to the callin function i.e. to main() function
    return choice;
}
