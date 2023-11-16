#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct tnode
{
	char* str;
	int index;
	struct tnode* arr;
};

struct tnode* create_node()
{
	struct tnode* node;
	node = (struct tnode*)malloc(sizeof(struct tnode));
	node->str = (char*)malloc(sizeof(char)*4001);
	node->str = "";
	node->index=-2;
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

void print_leaves(struct tnode* ptr)
{
	int i = 0;
	while(i<128)
	{
		if((ptr+i)->index != -2)
		{
			if((ptr+i)->index != -1)
				printf("%d ",(ptr+i)->index);
			else if((ptr+i)->index == -1)
				print_leaves((ptr+i)->arr);
		}	
		i++;
	}
}

void insert1(struct tnode** src_ptr, char* text, int index)
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
			(ptr + i)->index = -2;
		}
		
	}
	int i=0;
	int j=0;
	int flag=1;
	struct tnode* matched_node = create_node();
	char* matched_str = (char*)malloc(sizeof(char)*n);
	int matched_index = -1;
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
		matched_index = matched_node->index;
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
				(((ptr+j)->arr) + i)->index = -2;
			}
		}
		
		(*src_ptr + j)->str = matched_str;
		(*src_ptr + j)->index = -1;
		if(remaining1!="")
			insert1(&((ptr+j)->arr),remaining1,matched_index);
		if(remaining2!="")
			insert1(&((ptr+j)->arr),remaining2,index);
	}
	else				//there are no matches beyond this so create node for remainign and insert in parent
	{
		//printf("there are no matches\n");
		(ptr+j)->str = text;
		(ptr+j)->index = index;
	}
}

void search(char* patt, struct tnode* ptr)
{
	int i = 0;
	int j = 0;
	int flag = 1;
	
	while(i<128 && (ptr+i)->str!="" && flag)
	{
		if((ptr+i)->str[0] == patt[0])
		{
			int k = 0;
			while(k<min(strlen((ptr+i)->str),strlen(patt)) && ((ptr+i)->str)[k]==patt[k])
			{
				k++;
			}
			if(k == strlen(patt))
			{
				flag = 0;
				break;
			}
			else if(k == strlen((ptr+i)->str))
			{
				ptr = (ptr+i)->arr;
				i = 0;
				patt = getstr(patt, k, strlen(patt));
			}
			else if(k < strlen(patt))
			{
				printf("%d\n",-1);
				return;
			}
		}
		else
			i++;
	}
	if(flag == 0)
	{
		if((ptr+i)->index == -1)
		{
			print_leaves((ptr+i)->arr);
			printf("\n");
		}
		else if((ptr+i)->index >= 0)
		{
			printf("%d\n",(ptr+i)->index);
		}
	}
	else
	{
		printf("%d\n",-1);
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
	
	for(int i = 0; i<strlen(text); i++)
		text[i] = tolower(text[i]);
	//printf("%s\n",text);
	struct tnode* tree;
	tree = create_node();
	tree->arr = (struct tnode*)malloc(sizeof(struct tnode)*128);
	for(int i = 0; i<128; i++)
	{
		(tree->arr + i)->str = "";
		(tree->arr + i)->index = -2;
	}
	//tree->str = "";
	//tree->str = getstr(text,0,3);
	if(!tree->arr)
		printf("its empty\n");
	int l=n-1;
	int r=n;
	int index = n-1;
	while(l>=0)
	{
		char* str = (char*)malloc(sizeof(char)*n);
		str = getstr(text,l,r);
		//printf("##########  INSERTING:%s  ##########\n",str);
		insert1(&(tree->arr),str,index);
		l--;
		index--;
	}
	
	int k;
	scanf("%d\n",&k);
	while(k > 0)
	{
		char* patt = (char*)malloc(sizeof(char)*1001);
		scanf("%[^\n]%*c",patt);
		for(int i = 0; i<strlen(patt); i++)
			patt[i] = tolower(patt[i]);
		//printf("%s\n",patt);	
		search(patt , tree->arr);
	
		free(patt);
		k = k-1;
	}
	free(text);	
}

