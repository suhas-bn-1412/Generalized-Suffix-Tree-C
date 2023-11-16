#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct tnode
{
	char* str;
	struct tnode* arr;
};

struct tnode* create_node()
{
	struct tnode* node;
	node = (struct tnode*)malloc(sizeof(struct tnode));
	node->str = (char*)malloc(sizeof(char)*4001);
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
	char* p = (char*)malloc(sizeof(char)*4002);
	if(l==r)
	{
		p[0] = "";
		return p;
	}
	for(int i=0; i<r-l; i++)
	{
		p[i] = text[l+i];
	}
	//printf("%s %s %d %d\n",text,p,l,r);
	return p;
}

void insert1(struct tnode** src_ptr, char* text)
{
	//printf("##########  INSERTING:%s  ##########\n",text);

	struct tnode* ptr = *(src_ptr);
	if(text==NULL)
	{
		//printf("text is null\n");
		return;
	}

	int n = strlen(text);
	if(ptr==NULL)
	{
		//printf("tree arr is empty\n");
		ptr = (struct tnode*)malloc(sizeof(struct tnode)*128);
		for(int i = 0; i<128; i++)
		{
			(ptr + i)->str = "";
		}
		
	}
	int i=0;
	int j=0;
	int flag=1;
	struct tnode* matched_node = create_node();
	char* matched_str = (char*)malloc(sizeof(char)*n);
	char* remaining1 = (char*)malloc(sizeof(char)*n);
	char* remaining2 = (char*)malloc(sizeof(char)*n);
	matched_str = "";
	remaining1 = "";
	remaining2 = "";
	while(i<128 && (ptr+i) && flag)//remove i<n
	{
		if((ptr+i)->str[0] == text[0])   //(ptr+i)->str && 
		{
			flag=0;
			matched_node = (ptr+i);
			//printf("there is matched node:%s\n",(tree->arr[i])->str);
			break;
		}
		
		j++;
		if((ptr+i)->str == "")
			j--;
		i++;
	}
	if(flag==0)			//exited because there is a matched node, so recursive calls
	{
		
		int k = 0;
		while(k<min(strlen(matched_node->str),n) && (matched_node->str)[k]==text[k])
		{
			k++;
		}
		//printf("k:%d\n",k);
		//printf("actual_str:%s\n",matched_node->str);
		matched_str = getstr(matched_node->str,0,k);
		//printf("m.str:%s\n",matched_str);
		if(!(k==strlen(matched_node->str)))
			remaining1 = getstr(matched_node->str,k,strlen(matched_node->str));
		//printf("rm1:%s\n",remaining1);
		if(!(k==n))
			remaining2 = getstr(text,k,n);
		//printf("rm2:%s\n",remaining2);	
			
		if(((ptr+j)->arr)==NULL)
		{
			//printf("Creating array\n");
			((ptr+j)->arr) = (struct tnode*)malloc(sizeof(struct tnode)*128);
			for(int i = 0; i<128; i++)
			{
				(((ptr+j)->arr) + i)->str = "";
			}
		}
		
		(*src_ptr + j)->str = matched_str;
		
		if(remaining1!="")
			insert1(&((ptr+j)->arr),remaining1);
		if(remaining2!="")
			insert1(&((ptr+j)->arr),remaining2);
	}
	else				//there are no matches beyond this so create node for remainign and insert in parent
	{
		//printf("there are no matches\n");
		(ptr+j)->str = text;
	}
}


int main()
{
	char* text = (char*)malloc(sizeof(char)*4002);
	scanf("%[^\n]%*c",text);
	int n = strlen(text);
	text[n+1] = text[n];
	text[n] = '$';
	n++;
	if(" "=="")
	printf("text:%s\n",text);
	struct tnode* tree;
	tree = create_node();
	tree->arr = (struct tnode*)malloc(sizeof(struct tnode)*128);
	for(int i = 0; i<128; i++)
	{
		(tree->arr + i)->str = "";
	}
	//tree->str = "";
	//tree->str = getstr(text,0,3);
	if(!tree->arr)
		printf("its empty\n");
	int l=n-1;
	int r=n;
	while(l>=0)
	{
		char* str = (char*)malloc(sizeof(char)*(r-l));
		str = getstr(text,l,r);
		//printf("##########  INSERTING:%s  ##########\n",str);
		insert1(&(tree->arr),str);
		l--;
	}
	
	//char* kkk = (((tree->arr + 1)->arr+1)->arr+1)->str;
	//printf("last::%s\n",kkk);
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
	
	struct node* tree;
	tree = create_node();
	tree->arr = (struct tnode*)malloc(sizeof(struct tnode)*(strlen(text)));
	for(int i = 0; i<strlen(text); i++)
	{
		(tree->arr + i)->str = "";
	}
	//tree->str = "";
	//tree->str = getstr(text,0,3);
	//if(!tree->arr)
		//printf("its empty\n");
	//(tree->arr[1])->str = "checking";
	//insert1(&(tree->arr),text);
	//printf("main:%s\n",((tree->arr + 0))->str);
	//insert1(&(tree->arr),str);
	//printf("main:%s\n",((tree->arr + 0))->str);

	int l=n-1;
	int r=n;
	while(l>=0)
	{
		char* str = (char*)malloc(sizeof(char)*(r-l));
		str = getstr(text,l,r);
		//printf("##########  INSERTING:%s  ##########\n",str);
		insert1(&(tree->arr),str);
		l--;
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
