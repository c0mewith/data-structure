#include <stdlib.h> // malloc, atoi
#include <stdio.h>
#include <ctype.h> // isdigit
#include <assert.h> // assert

#define MAX_STACK_SIZE	50

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{   
	char		data;
	struct node	*left;
	struct node	*right;
} NODE;

typedef struct
{
	NODE	*root;
} TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a tree head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
TREE *createTree( void);

/* Deletes all data in tree and recycles memory
*/
void destroyTree( TREE *pTree);

static void _destroy( NODE *root);

/*  Allocates dynamic memory for a node and returns its address to caller
	return	node pointer
			NULL if overflow
*/
static NODE *_makeNode( char ch);

/* converts postfix expression to binary tree
	return	1 success
			0 invalid postfix expression
*/
int postfix2tree( char *expr, TREE *pTree);

/* Print node in tree using inorder traversal
*/
void traverseTree( TREE *pTree);

/* internal traversal function
	an implementation of ALGORITHM 6-6
*/
static void _traverse( NODE *root);

/* Print tree using inorder right-to-left traversal
*/
void printTree( TREE *pTree);

/* internal traversal function
*/
static void _infix_print( NODE *root, int level);

/* evaluate postfix expression
	return	value of expression
*/
float evalPostfix( char *expr);

////////////////////////////////////////////////////////////////////////////////
void destroyTree( TREE *pTree)
{
	if (pTree)
	{
		_destroy( pTree->root);
	}
		
	free( pTree);
}

////////////////////////////////////////////////////////////////////////////////
void printTree( TREE *pTree)
{
	_infix_print(pTree->root, 0);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
void traverseTree( TREE *pTree)
{
	_traverse(pTree->root);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	TREE *tree;
	char expr[1024];
	
	fprintf( stdout, "\nInput an expression (postfix): ");
	
	while (fscanf( stdin, "%s", expr) == 1)
	{
		// creates a null tree
		tree = createTree();
		
		if (!tree)
		{
			printf( "Cannot create tree\n");
			return 100;
		}
		
		// postfix expression -> expression tree
		int ret = postfix2tree( expr, tree);
		if (!ret)
		{
			fprintf( stdout, "invalid expression!\n");
			destroyTree( tree);
			fprintf( stdout, "\nInput an expression (postfix): ");
			continue;
		}
		
		// expression tree -> infix expression
		fprintf( stdout, "\nInfix expression : ");
		traverseTree( tree);
		
		// print tree with right-to-left infix traversal
		fprintf( stdout, "\n\nTree representation:\n");
		printTree(tree);
		
		// evaluate postfix expression
		float val = evalPostfix( expr);
		fprintf( stdout, "\nValue = %f\n", val);
		
		// destroy tree
		destroyTree( tree);
		
		fprintf( stdout, "\nInput an expression (postfix): ");
	}
	return 0;
}

TREE *createTree( void)
{
	TREE* head=(TREE*)malloc(sizeof(TREE));
	head->root = NULL;
	return head;
}



static void _destroy( NODE *root)
{
	if(root != NULL) {
		_destroy(root->left);
		_destroy(root->right);
		free(root);
		root = NULL;
	}
	
}


static NODE *_makeNode( char ch)
{
	NODE* nnode=(NODE*)malloc(sizeof(NODE));
	nnode->data = ch;
	nnode->right = NULL;
	nnode->left =NULL;
	return nnode;
}


int postfix2tree( char *expr, TREE *pTree)
{
	NODE* stack[MAX_STACK_SIZE]={0};
	int top=-1;
	for(int i=0;expr[i]!='\0';i++){
		NODE *nnode=_makeNode(expr[i]);
		
		if(expr[i]=='+'||expr[i]=='-'||expr[i]=='*'||expr[i]=='/') //연산자일 경우 pop2번
		{
			if(top!=-1)//첫번째 pop
			{
				nnode->right = stack[top];
				top--;
			}
			else //invalid
			{
					_destroy(nnode);
					return 0;
			}
			
			if(top!=-1)//두번째 pop
			{
				nnode->left = stack[top];
				top--;
			}
			else //invalid
			{
					_destroy(nnode);
					return 0;
			}
		}
		//(피연산자일경우 stack에 push & top 증가)
		//(연산자일경우 연산자의 left right 자식을 단체로 stack 에 대입)
			top ++;
			stack[top]=nnode;
			
	}//for문 end
	
		if(top==0)
		{
			pTree->root = stack[0];
			return 1;
		}
		else{//invalid
			for(int i=0;i<=top;i++){
				_destroy(stack[i]);
				return 0;
			}
		}
		
	
	
}
	



void traverseTree( TREE *pTree);


static void _traverse( NODE *root)
{
	if(root !=NULL)
	{
		//연산자일경우 subtree에서 traverse
		if(root->data=='+'||root->data=='*'||root->data=='/'||root->data=='-')
		{
			printf("(");
			_traverse(root->left);
			printf("%c",root->data);
			_traverse(root->right);
			printf(")");
		}
			
		else//피연산자일경우 출력
			printf("%c",root->data);
		
	}
}


void printTree( TREE *pTree);



static void _infix_print( NODE *root, int level)
{
	if(root!=NULL)
	{
		level++;
		_infix_print(root->right,level);
		for(int i=1;i<level;i++)//level에따라 tab수 정해주기
		{
			printf("\t");
		}
		printf("%c\n",root->data);
		_infix_print(root->left,level);
	}
	
}

 
float evalPostfix( char *expr)
{
	float stack[MAX_STACK_SIZE];
	int top=-1;
	float n1,n2;
	float result;
	int size = sizeof(expr)/sizeof(char);
	
	for(int i=0;expr[i]!='\0';i++)
	{
		if(expr[i]>='0'&&expr[i]<='9')//피연산자일경우 stack에 push
		{
			top++;
			char num=expr[i];
			stack[top]=(float)atoi(&num);
		}
		else if (expr[i]=='+' ||expr[i]=='/' ||expr[i]=='*' ||expr[i]=='-')//연산자일경우 pop두번후 연산진행
		{
			n1=stack[top];
			top--;
			n2=stack[top];
			top--;
			switch(expr[i])
			{
				case'+':
					
					result=n1+n2;
					
					break;
				case'-':
					result=n1-n2;
					break;
				case'*':
					result=n1*n2;
					break;
				case'/':
					result=n1/n2;
					break;
			}
			top++;
			stack[top]=result;//result값 다시 push
		}
	}
	return stack[top];
}