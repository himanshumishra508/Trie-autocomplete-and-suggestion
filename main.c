#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define ALPHABET_SIZE (26)  
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 


struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 
	bool isWordEnd; 
}; 
 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode)); 
	pNode->isWordEnd = false; 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 

void insert(struct TrieNode *root, char key[]) 
{ 
	struct TrieNode *pCrawl = root; 
	for (int level = 0; level < strlen(key); level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 

	pCrawl->isWordEnd = true; 
} 
 
bool search(struct TrieNode *root, char key[]) 
{ 
	int length = strlen(key); 
	struct TrieNode *pCrawl = root; 
	for (int level = 0; level < length; level++) 
	{ 
		int index = CHAR_TO_INDEX(key[level]); 

		if (!pCrawl->children[index]) 
			return false; 

		pCrawl = pCrawl->children[index]; 
	} 

	return (pCrawl != NULL && pCrawl->isWordEnd); 
} 

bool isLastNode(struct TrieNode* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 

void suggestionsRec(struct TrieNode* root, char currPrefix[]) 
{ 
	if (root->isWordEnd) 
	{
		puts(currPrefix);
	} 
	if (isLastNode(root)) 
	{
		return; 
	}
	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ 
		if (root->children[i]) 
		{ 
			int p=97+i;
			char c=(char)p;
			strncat(currPrefix,&c,1);
			suggestionsRec(root->children[i], currPrefix); 
			int len=strlen(currPrefix);
			currPrefix[len-1]='\0';
		} 
	} 
} 

int printAutoSuggestions(struct TrieNode* root,const char query[]) 
{ 
	struct TrieNode* pCrawl = root; 
	int level; 
	int n = strlen(query); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 
		if (!pCrawl->children[index]) 
			return 0; 

		pCrawl = pCrawl->children[index]; 
	}
	
    bool isWord = (pCrawl->isWordEnd == true); 

	bool isLast = isLastNode(pCrawl); 

	if (isWord && isLast) 
	{ 
		printf("\n \n");
		puts(query); 
		printf("*****MATCH FOUND*****\n\n");
		return -1; 
	} 

	if (!isLast) 
	{ 
		char prefix[30]; 
		strcpy(prefix,query);
		printf("\n\nMATCH FOUND With AUTO COMPLETE:-\n");
		suggestionsRec(pCrawl, prefix); 
		return 1; 
	} 
	return 1;
} 

int main() 
{ 

	FILE *fp,*fp2,*art,*sign;
	char word[30];
    
    art=fopen("art.txt","r");
    char read_string[500];
    while(!feof(art))
    {
        fgets(read_string,500,art);
        printf("%s",read_string);
    }printf("\n");

    sign=fopen("sign.txt","r");
    while(!feof(sign))
    {
        fgets(read_string,500,sign);
        printf("%s",read_string);
    }
    printf("\n");
    printf("\n");

	
    
    fp=fopen("dict.txt","r");
	fp2=fopen("dict.txt","a");
	struct TrieNode* root = getNode(); 

	while(!feof(fp))
	{
		fscanf(fp,"%s",word);
		insert(root,word);
	}
	char srch[30];
    int y=1,opt;
    while(y)
    {
        printf("enter the word to be searched\n");
        scanf("%s",srch);
        int comp = printAutoSuggestions(root, srch); 

        if (comp == -1) 
        {
            printf("\nNO OTHER STRINGS FOUND WITH THIS PREFIX\n\n"); 
        }
        else if (comp == 0) 
        {
            printf("\nNO STRINGS FOUND WITH THIS PREFIX\n\n");
            printf("Do you want to add this word in dictionary\n\nIF YES , PRESS 1\nIF NO , PRESS 0\n\n");
            scanf("%d",&opt);
            while(opt!=0 && opt!=1)
            {
                printf("invalid entry\n\nEnter again!\n");
                scanf("%d",&opt);
            }
            if(opt==1)
            {
                fprintf(fp2,"%s\n",srch);
                insert(root,srch);
            }

        }
         
        printf("\nWant to search more words\n\nIF YES , PRESS 1\nIF NO , PRESS 0\n\n");
        scanf("%d",&y);
        while(y!=0 && y!=1)
        {
            printf("invalid entry\n\nEnter again!\n");
            scanf("%d",&y);
        }
    }
	return 0; 
} 
