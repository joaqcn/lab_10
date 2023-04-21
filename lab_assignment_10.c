#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie
{
    int count;
    struct Trie *pChildren[26];
};

void insert(struct Trie **ppTrie, char *word)
{
    if (*ppTrie == NULL)
    {
        *ppTrie = (struct Trie *)malloc(sizeof(struct Trie));
        (*ppTrie)->count = 0;
        for (int i = 0; i < 26; i++)
            (*ppTrie)->pChildren[i] = NULL;
    }
    if (*word == '\0')
    {
        (*ppTrie)->count++;
        return;
    }
    int index = *word - 'a';
    insert(&((*ppTrie)->pChildren[index]), word + 1);
}

int numberOfOccurances(struct Trie **ppTrie, char *word)
{
    if (*ppTrie == NULL)
        return 0;
    if (*word == '\0')
        return (*ppTrie)->count;
    int index = *word - 'a';
    return numberOfOccurances(&((*ppTrie)->pChildren[index]), word + 1);
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < 26; i++)
        pTrie->pChildren[i] = deallocateTrie(pTrie->pChildren[i]);
    free(pTrie);
    return NULL;
}
int main()
{
    struct Trie *trie = NULL;
    // read the number of the words in the dictionary
    //  parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(&trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
