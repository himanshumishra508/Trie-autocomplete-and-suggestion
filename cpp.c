// C++ program to demonstrate auto-complete feature 
// using Trie data structure. 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (26) 

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

// trie node 
struct TrieNode 
{ 
	struct TrieNode *children[ALPHABET_SIZE]; 

	// isWordEnd is true if the node represents 
	// end of a word 
	bool isWordEnd; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
	struct TrieNode *pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode)); //**************************** 
	pNode->isWordEnd = false; 

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 

// If not present, inserts key into trie. If the 
// key is prefix of trie node, just marks leaf node 
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

	// mark last node as leaf 
	pCrawl->isWordEnd = true; 
} 

// Returns true if key presents in trie, else false 
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

// Returns 0 if current node has a child 
// If all children are NULL, return 1. 
bool isLastNode(struct TrieNode* root) 
{ 
	for (int i = 0; i < ALPHABET_SIZE; i++) 
		if (root->children[i]) 
			return 0; 
	return 1; 
} 

// Recursive function to print auto-suggestions for given 
// node. 
void suggestionsRec(struct TrieNode* root, char currPrefix[]) 
{ 
	// found a string in Trie with the given prefix 
	if (root->isWordEnd) 
	{ 
		//printf("\n\n");
		puts(currPrefix);
		//printf("*****Match Found*****\n\n");

		//cout << currPrefix; 
		//cout << endl; 
	} 

	// All children struct node pointers are NULL 
	if (isLastNode(root)) 
	{
		//int len=strlen(currPrefix);
		//currPrefix[len-1]='\0';
		return; 
	}
int k=0;
	for (int i = 0; i < ALPHABET_SIZE; i++) 
	{ k=0;
		if (root->children[i]) 
		{ 
			// append current character to currPrefix string 
			//currPrefix.push_back(97 + i); 
			int p=97+i;
			char c=(char)p;
			strncat(currPrefix,&c,1);

			// recur over the rest 
			suggestionsRec(root->children[i], currPrefix); 
			int len=strlen(currPrefix);
			currPrefix[len-1]='\0';
		} 
	} 
} 

// print suggestions for given query prefix. 
int printAutoSuggestions(struct TrieNode* root,const char query[]) 
{ 
	struct TrieNode* pCrawl = root; 

	// Check if prefix is present and find the 
	// the node (of last level) with last character 
	// of given string. 
	int level; 
	int n = strlen(query); 
	for (level = 0; level < n; level++) 
	{ 
		int index = CHAR_TO_INDEX(query[level]); 

		// no string in the Trie has this prefix 
		if (!pCrawl->children[index]) 
			return 0; 

		pCrawl = pCrawl->children[index]; 
	} 

	// If prefix is present as a word. 
	bool isWord = (pCrawl->isWordEnd == true); 

	// If prefix is last node of tree (has no 
	// children) 
	bool isLast = isLastNode(pCrawl); 

	// If prefix is present as a word, but 
	// there is no subtree below the last 
	// matching node. 
	if (isWord && isLast) 
	{ 
		printf("\n \n");
		puts(query); 
		printf("*****Match Found*****\n\n");
		return -1; 
	} 

	// If there are are nodes below last 
	// matching character. 
	if (!isLast) 
	{ 
		char prefix[30]; 
		strcpy(prefix,query);
		printf("\n\nMatch Found With Auto Complete:-\n");
		suggestionsRec(pCrawl, prefix); 
		return 1; 
	} 
	return 1;
} 

// Driver Code 
int main() 
{ 

	FILE *fp,*fp2;char word[30];
	fp=fopen("dict.txt","r");
	fp2=fopen("res.txt","w");
	struct TrieNode* root = getNode(); 

	while(!feof(fp))
	{
		fscanf(fp,"%s",word);
		insert(root,word);
		fprintf(fp2,"%s\n",word);
	}
	printf("enter the word to be searched\n");
	char srch[30];
	scanf("%s",srch);
	int comp = printAutoSuggestions(root, srch); 


    if (comp == -1) 
        printf("No other strings found with this prefix\n\n"); 
  
    else if (comp == 0) 
        printf("No string found with this prefix\n\n"); 
    

	return 0; 
} 
