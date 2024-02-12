// Item Details using LinkedList

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "ItemDetails.dat"
#define ItemMSG "Enter Items"
#define ID_LENGTH 20
#define NAME_LENGTH 50

struct ItemDetails
{
	char ItemId[ID_LENGTH];
	char ItemName[NAME_LENGTH];
	int ItemPrice;
	
}ItemDetails;

typedef struct ItemDetails ItemsDetails;

struct Node 
{
	ItemsDetails Record;
	struct Node *Next;
};

typedef struct Node Node;


Node *Start = NULL, *LastNode, *NewNode, *temperoryNode;

FILE *FpItemsDetails;

void showMenu();
void addItem();
void LoadList();
void showAllItems();
Node* getItemLocation(char *);
void updateItemDetails(char *);
void removeItem(char *);
void saveList();


void printSucessMsg(char *Content, char *ItemId)
{
	printf("\nSucessfully %s item with id %s\n", Content, ItemId);
}


void printNoRecordFound()
{
	printf("\nThere is no items in the file.\n");
}

void printItemNotFound(char *ItemId)
{
	printf("\nItem with id %s not found.\n", ItemId);
}

void creatNode()
{
	NewNode = malloc(sizeof(Node));
	NewNode->Next = NULL;
}

char* getItemId()
{
	char *ItemId = (char*) malloc(sizeof(char) * ID_LENGTH);
	printf("Enter Item Id: ");
	scanf("%s", ItemId);

	return ItemId;
}

void addNode()
{
	if (Start == NULL)
		Start = NewNode;
	else
		LastNode->Next = NewNode;

	LastNode = NewNode;

}

void showItem()
{
	printf("\n\t Item Id: %s\n", ItemDetails.ItemId);
	printf("\t Item Name: %s\n", ItemDetails.ItemName);
	printf("\t Item Price: %d\n", ItemDetails.ItemPrice);
}



void main()
{
	temperoryNode = (Node*) malloc(sizeof(Node));

	LoadList();

	while(1)
	{
		showMenu();
	}

	free(temperoryNode);
}

void showMenu()
{
	int Choice;
	printf("\n 1. New Item\n 2. Show all Item\n 3. Search\n 4. Update Price\n 5. Remove Item\n 6. EXIT\n");
	printf("Enter your choice: ");
	scanf("%d", &Choice);

	switch (Choice)
	{
		case 1: addItem();
				break;

		case 2: showAllItems();
				break;

		case 3:	printf("To Search.\n");
				Node *SearchedNode;
				if (SearchedNode = getItemLocation(getItemId()))
				{
					ItemDetails = SearchedNode->Next->Record;
					showItem();	
				}
				break;

		case 4:	printf("\nTo update Item price\n");
		 		updateItemDetails(getItemId());
				break;

		case 5:	printf("\n To remove Item\n");
				removeItem(getItemId());
				break;

		case 6:	exit(0);

		default: printf("\n\tINVALID Choice\t\n\t TRY AGAIN\t");
				 break;

}

}


void LoadList()
{
	FpItemsDetails = fopen(FILE_NAME, "r");

	while(fread(&ItemDetails, sizeof(ItemDetails), 1, FpItemsDetails ))
	{
		creatNode();
		NewNode->Record = ItemDetails;
		addNode();

	}

	fclose(FpItemsDetails);
}

void addItem()
{
	creatNode();

	printf("\n %s ID: ", ItemMSG);
	scanf("%s", NewNode->Record.ItemId);

	printf("\n %s name: ", ItemMSG);
	scanf(" %[^\n]s", NewNode->Record.ItemName);

	printf("\n %s Price: ", ItemMSG);
	scanf("%d", &NewNode->Record.ItemPrice);

	addNode();

	saveList();

}


void saveList()
{
	FpItemsDetails = fopen(FILE_NAME, "w");

	Node *Current = Start;

	while (Current != NULL)
	{
		fwrite(&Current->Record, sizeof(ItemDetails), 1, FpItemsDetails);
		Current = Current->Next;
	}

	fclose(FpItemsDetails);

}


void showAllItems()
{
	Node *Smallest;
	Node *Current = Start;  

	int Counter = 0;

	while (Current != NULL)
	{ 
		Smallest = temperoryNode;
		Smallest->Next = Start;
		while (Current->Next != NULL)
		{
			if (strcmp(Smallest->Next->Record.ItemId, Current->Next->Record.ItemId) > 0)
			{
				Smallest = Current;
			}

			Current = Current->Next;
		}

		ItemDetails = Smallest->Next->Record;
		printf("\nItem %d: ", Counter + 1);
		showItem();

		if (Smallest->Next == Start)
		{
			Start = Start->Next;
		}

		else
		{
			Smallest->Next = Smallest->Next->Next;
		}

		Current = Start;
		Counter++;

	}
	if (Counter == 0)
	{
		printNoRecordFound();
	}
	else
		LoadList();

}

void updateItemDetails(char *ItemId)
{
	Node *Current;
	if (Current = getItemLocation(ItemId))
	{
		printf("Enter new Item price: ");
		scanf("%d", &Current->Next->Record.ItemPrice);
		printSucessMsg("Updated", ItemId);
		saveList();
	}

}

void removeItem(char *ItemId)
{
	Node *Current, *NodeToFree = NULL;

	if (Current = getItemLocation(ItemId))
	{
		if (Current->Next == Start)
		{
			NodeToFree = Start;
			Start = Start->Next;
		}
		else if (Current->Next == LastNode)
		{
			NodeToFree = LastNode;
			LastNode = Current;
			Current->Next = NULL;
		}
		else
		{
			Current->Next = Current->Next->Next;
		}

		printSucessMsg("removed", ItemId);
		saveList();
	}
}

Node* getItemLocation(char *ItemId)
{
	Node *Current = temperoryNode;

	if (Start != NULL)
	{
		Current->Next = Start;

		while( Current->Next != NULL )
		{
			if (!strcmp(Current->Next->Record.ItemId, ItemId))
				return Current;

			Current = Current->Next;
		}

			printItemNotFound(ItemId);	
	}

	else
		printNoRecordFound();


	return NULL;
}