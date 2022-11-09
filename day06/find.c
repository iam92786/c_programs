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
void Find_nth_node_from_last(list_t* lptr);
void init_list(list_t *lptr);
bool_t list_empty(list_t *lptr);
node_t *creat_node (int data);
void add_node_at_first_pos(list_t *lptr, int data);
void add_node_at_last_pos(list_t *lptr, int data);
void add_node_at_specific_pos(list_t *lptr, int data, int pos);
void free_list(list_t* lptr);
void delete_node_at_last_pos(list_t *lptr);
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

			case 4:
				Find_nth_node_from_last(&l1);
				break;

			default:
				printf("Invalid Input \n");
				break;
			}

        }

		return 0;
}
void Find_nth_node_from_last(list_t* lptr)
{
        //find nth node from the last
        int nth,count, i;

		while(1)
		{
				//Take input from the user
				printf("Total node count is : %d \n>>Enter nth node position from last : ",lptr->node_count);
        		scanf("%d",&nth);

				//check Is it valid or not
				if(nth >= 1 && nth <= lptr->node_count)
				{
						break;
				} 
				else
				{
		                printf("invalid position !!!\n");

				}
		}
        if(list_empty(lptr))
        {
                //list is empty
                printf("Linked List is Empty\n");
        }
        else
        {
                //list is not empty
				node_t *trav;
				trav = lptr->head;
				count = lptr->node_count - nth;

				for(i = 0; i < count; ++i)
				{
						trav = trav->next;
				}
				printf(">> Node at nth Position %d From the Last is = %d\n",nth,trav->data);

                
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
    printf("1. add node at specific position\n");
    printf("2. delete node at last position\n");
    printf("3. display list\n");
    printf("4. Find Nth node From the last\n");

    //accept choice from user
    printf("Enter the choice : ");
    scanf("%d", &choice);

    //return user entered choice to the callin function i.e. to main() function
    return choice;
}
