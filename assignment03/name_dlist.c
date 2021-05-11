#include <stdlib.h> // malloc
#include <stdio.h>
#include <string.h> // strdup, strcmp
#include <ctype.h> // toupper

#define QUIT			1
#define FORWARD_PRINT	2
#define BACKWARD_PRINT	3
#define SEARCH			4
#define DELETE			5
#define COUNT			6

// User structure type definition
typedef struct 
{
	char	*name;
	int		freq;
} tName;

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{
	void		*dataPtr;	//tName		*dataPtr;
	struct node	*llink;
	struct node	*rlink;
} NODE;

typedef struct
{
	int		count;
	NODE	*pos; // unused
	NODE	*head;
	NODE	*rear;
	int		(*compare)(const void *, const void *); // used in _search function
} LIST;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a list head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
LIST *createList( int (*compare)(const void *, const void *));

/* Deletes all data in list and recycles memory
*/
void destroyList( LIST *pList, void (*callback)(void *));

/* Inserts data into list
	return	0 if overflow
			1 if successful
			2 if duplicated key
*/
int addNode( LIST *pList, void *dataInPtr, void (*callback)(const void *, const void *)); //tName

/* Removes data from list
	return	0 not found
			1 deleted
*/
int removeNode( LIST *pList, void *keyPtr, void **dataOut); //tName

/* interface to search function
	Argu	key being sought
	dataOut	contains found data
	return	1 successful
			0 not found
*/
int searchList( LIST *pList, void *pArgu, void **dataOutPtr); //tName

/* returns number of nodes in list
*/
int countList( LIST *pList);

/* returns	1 empty
			0 list has data
*/
int emptyList( LIST *pList);

/* traverses data from list (forward)
*/
void traverseList( LIST *pList, void (*callback)(const void *));

/* traverses data from list (backward)
*/
void traverseListR( LIST *pList, void (*callback)(const void *));

/* internal insert function
	inserts data into a new node
	return	1 if successful
			0 if memory overflow
*/
static int _insert( LIST *pList, NODE *pPre, void *dataInPtr); //tName

/* internal delete function
	deletes data from a list and saves the (deleted) data to dataOut
*/
static void _delete( LIST *pList, NODE *pPre, NODE *pLoc, void **dataOutPtr); //tName

/* internal search function
	searches list and passes back address of node
	containing target and its logical predecessor
	return	1 found
			0 not found
*/
static int _search( LIST *pList, NODE **pPre, NODE **pLoc, void *pArgu);

////////////////////////////////////////////////////////////////////////////////
/* Allocates dynamic memory for a name structure, initialize fields(name, freq) and returns its address to caller
	return	name structure pointer
			NULL if overflow
*/
tName *createName( char *str, int freq); 

/* Deletes all data in name structure and recycles memory
*/
void destroyName( void *pNode); //tName

////////////////////////////////////////////////////////////////////////////////
/* gets user's input
*/
int get_action()
{
	char ch;
	scanf( "%c", &ch);
	ch = toupper( ch);
	switch( ch)
	{
		case 'Q':
			return QUIT;
		case 'F':
			return FORWARD_PRINT;
		case 'B':
			return BACKWARD_PRINT;
		case 'S':
			return SEARCH;
		case 'D':
			return DELETE;
		case 'C':
			return COUNT;
	}
	return 0; // undefined action
}

// compares two names in name structures
// for createList function
int cmpName( const void* pName1, const void* pName2)
{
	return strcmp( ((tName *)pName1)->name, ((tName *)pName2)->name);
}

// prints name and freq in name structure
// for traverseList and traverseListR functions
void print_name(const void *dataPtr)
{
	printf( "%s\t%d\n", ((tName *)dataPtr)->name, ((tName *)dataPtr)->freq);
}

// increases freq in name structure
// for addNode function
void increse_freq(const void *dataOutPtr, const void *dataInPtr)
{
	((tName *)dataOutPtr)->freq += ((tName *)dataInPtr)->freq;
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	LIST *list;
	
	char str[1024];
	int freq;
	
	tName *pName;
	int ret;
	FILE *fp;
	
	if (argc != 2){
		fprintf( stderr, "usage: %s FILE\n", argv[0]);
		return 1;
	}
	
	fp = fopen( argv[1], "rt");
	if (!fp)
	{
		fprintf( stderr, "Error: cannot open file [%s]\n", argv[1]);
		return 2;
	}
	
	// creates an empty list
	//list = createList( cmpName);
	//if (!list)
	{
		//printf( "Cannot create list\n");
		//return 100;
	}
	
	void *p;
	
	while(fscanf( fp, "%*d\t%s\t%*c\t%d", str, &freq) != EOF)
	{
		//pName = createName( str, freq);
		
		//ret = addNode( list, pName, increse_freq);
		
		//if (ret == 2) // duplicated
		{
			//destroyName( pName);
		}
	}
	
	fclose( fp);
	
	fprintf( stderr, "Select Q)uit, F)orward print, B)ackward print, S)earch, D)elete, C)ount: ");
	
	while (1)
	{
		void *p;
		int action = get_action();
		
		switch( action)
		{
			case QUIT:
				//destroyList( list, destroyName);
				return 0;
			
			case FORWARD_PRINT:
				//traverseList( list, print_name);
				break;
			
			case BACKWARD_PRINT:
				//traverseListR( list, print_name);
				break;
			
			case SEARCH:
				fprintf( stderr, "Input a string to find: ");
				fscanf( stdin, "%s", str);

				//pName = createName( str, 0);

				//if (searchList( list, pName, &p))
				{
					//print_name( p);
				}
				//else fprintf( stdout, "%s not found\n", str);
				
				//destroyName( pName);
				break;
				
			case DELETE:
				fprintf( stderr, "Input a string to delete: ");
				fscanf( stdin, "%s", str);
				
				//pName = createName( str, 0);

				//if (removeNode( list, pName, &p))
				{
					//fprintf( stdout, "(%s, %d) deleted\n", ((tName *)p)->name, ((tName *)p)->freq);
					//destroyName( (tName *)p);
				}
				//else fprintf( stdout, "%s not found\n", str);
				
				//destroyName( pName);
				break;
			
			case COUNT:
				//fprintf( stdout, "%d\n", countList( list));
				break;
		}
		
		if (action) fprintf( stderr, "Select Q)uit, F)orward print, B)ackward print, S)earch, D)elete, C)ount: ");
	}
	return 0;
}
