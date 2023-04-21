#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    struct Trie *children[ALPHABET_SIZE];
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;

    if (pTrie == NULL) {
        pTrie = (struct Trie*) malloc(sizeof(struct Trie));
        pTrie->count = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pTrie->children[i] = NULL;
        }
        *ppTrie = pTrie;
    }

    while (*word) {
        int index = *word - 'a';
        if (pTrie->children[index] == NULL) {
            pTrie->children[index] = (struct Trie*) malloc(sizeof(struct Trie));
            pTrie->children[index]->count = 0;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                pTrie->children[index]->children[i] = NULL;
            }
        }
        pTrie = pTrie->children[index];
        ++word;
    }

    ++pTrie->count;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (pTrie == NULL) {
        return 0;
    }

    while (*word) {
        int index = *word - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
        ++word;
    }

    return pTrie->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;
    char *words[] = {"notaword", "ucf", "no", "note", "corg"};
    int n = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < n; i++) {
        insert(&trie, words[i]);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}

