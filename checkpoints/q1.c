#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct tnode
{
	char* str;
	struct tnode** arr;
};

struct tnode* create_node()
{
	struct tnode* node;
	node = (struct tnode*)malloc(sizeof(struct tnode));
	node->str = "";
	node->arr = NULL;
	return node;
}

int min(int a, int b)
{
	if(a < b)
		return a;
	return b;
}

char* getstr(char* text, int l, int r)
{
	static char p[4002];
	if(l==r)
	{
		p[0] = NULL;
		return p;
	}
	for(int i=0; i<r-l; i++)
	{
		p[i] = text[l+i];
	}
	return p;
}

void insert(struct tnode* tree, char* text)
{
	if(text==NULL)
	{
		printf("text is null\n");
		return;
	}

	int n = strlen(text);
	if(tree->arr==NULL)
	{
		printf("tree arr is empty\n");
		tree->arr = (struct tnode**)malloc(sizeof(struct tnode*)*(strlen(text)));
		for(int i=0;i<strlen(text);i++)
		{
			tree->arr[i]=NULL;
		}
	}
	int i=0;
	int flag=1;
	struct tnode* matched_node = create_node();
	char* matched_str = (char*)malloc(sizeof(char)*n);
	char* remaining1 = (char*)malloc(sizeof(char)*n);
	char* remaining2 = (char*)malloc(sizeof(char)*n);
	//matched_str = "";
	//remaining1 = "";
	//remaining2 = "";
	while(tree->arr[i] && flag)
	{
		if((tree->arr[i])->str[0] = text[0])
		{
			flag=0;
			matched_node = tree->arr[i];
			//printf("there is matched node:%s\n",(tree->arr[i])->str);
			break;
		}
		i++;
	}
	if(flag==0)			//exited because there is a matched node, so recursive calls
	{
		
		int k = 0;
		while((matched_node->str)[k]==text[k] && k<min(strlen(matched_node->str),n))
		{
			k++;
		}
		
		matched_str = getstr(text,0,k);
		remaining1 = getstr(matched_node->str,k,strlen(matched_node->str));
		remaining2 = getstr(text,k,strlen(text));
		//printf("%s   %s   %s\n",matched_str,remaining1,remaining2);
		matched_node->str = matched_str;
		insert(matched_node,remaining1);
		insert(matched_node,remaining2);
	}
	else				//there are no matches beyond this so create node for remainign and insert in parent
	{
		printf("there are no matches\n");
		tree->arr[i] = create_node();
		(tree->arr[i])->str = (char*)malloc(sizeof(char)*4001); ///DONT DO THIS
		(tree->arr[i])->str = text;
	}
}


int main()
{
	char* text = "banana$";
	char* str = "kbanaka";
	struct tnode* tree;
	tree = create_node();
	tree->arr = (struct tnode**)malloc(sizeof(struct tnode*)*(strlen(text)));
	for(int i=0;i<strlen(text);i++)
	{
		tree->arr[i]=NULL;
	}
	//tree->str = "";
	//tree->str = getstr(text,0,3);
	if(!tree->arr)
		printf("its empty\n");
	//(tree->arr[1])->str = "checking";
	insert(tree,text);
	printf("%s\n",((tree->arr[0]))->str);
	//insert(tree,str);
	printf("%s\n",((tree->arr[0])->arr[0])->str);
}


/*
int main()
{
	//take text input
	char* text = (char*)malloc(sizeof(char)*4002);
	scanf("%[^\n]%*c",text);
	int n = strlen(text);
	text[n] = '$';
	text[n+1] = '\n';
	n++;
	int k;
	scanf("%d\n",&k);

	struct tnode* tree;
	tree = create_node();
	tree->arr = (struct tnode**)malloc(sizeof(struct tnode*)*(strlen(text)));
	for(int i=0;i<strlen(text);i++)
	{
		tree->arr[i]=NULL;
	}
	int l=n-1;
	int r=n;
	while(l>=0)
	{
		char* str = (char*)malloc(sizeof(char)*(r-l));
		str = getstr(text,l,r);
		insert(tree,str);
	}

	//loop for all test cases
	while(k > 0)
	{
		char* patt = (char*)malloc(sizeof(char)*1001);
		scanf("%[^\n]%*c",patt);
		
		
	
		free(patt);
		k = k-1;
	}
	free(text);
}
*/
