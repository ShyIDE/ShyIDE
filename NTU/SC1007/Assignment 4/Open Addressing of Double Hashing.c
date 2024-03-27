#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED,DELETED};

typedef struct _slot{
    int key;
    enum Marker indicator;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashDelete(int key, HashSlot hashTable[]);


int hash1(int key);
int hash2(int key);

int main()
{
    int opt;
    int i;
    int key;
    int comparison;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].indicator = EMPTY;
        hashTable[i].key = 0;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Delete a key from the hash table|\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");
    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            comparison = HashInsert(key,hashTable);
            if(comparison <0)
                printf("Duplicate key\n");
            else if(comparison < TABLESIZE)
                printf("Insert: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Key Comparisons: %d. Table is full.\n",comparison);
            break;
        case 2:
            printf("Enter a key to be deleted:\n");
            scanf("%d",&key);
            comparison = HashDelete(key,hashTable);
            if(comparison <0)
                printf("%d does not exist.\n", key);
            else if(comparison <= TABLESIZE)
                printf("Delete: %d Key Comparisons: %d\n",key, comparison);
            else
                printf("Error\n");
            break;
        case 3:
            for(i=0;i<TABLESIZE;i++) printf("%d: %d %c\n",i, hashTable[i].key,hashTable[i].indicator==DELETED?'*':' ');
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int hash1(int key)
{
    return (key % TABLESIZE);
}

int hash2(int key)
{
    return (key % PRIME) + 1;
}

int HashInsert(int key, HashSlot hashTable[])
{
    int hash = hash1(key);
    int insertAt, i = 0;
    int comparisons = 0;

    while (hashTable[hash].indicator == USED && hashTable[hash].key != key && i < TABLESIZE) {
        hash = (hash + hash2(key)) % TABLESIZE;
        i++;
        comparisons++;
    }
    if (i >= TABLESIZE) {
        return comparisons ;  // Table is full, count initial comparison
    }

    insertAt = hash;   // Save the insertion point first
    // We will continue probing till the end (i.e. hitting an EMPTY slot)
    // to check if the key is indeed not in the hashTable

    while (hashTable[hash].indicator != EMPTY && i < TABLESIZE) {
        if (hashTable[hash].indicator == USED) {    // Do a key compare if slot is in use
            comparisons++;
            if (hashTable[hash].key == key) // Key already exists
                return -1;
        }
        hash = (hash + hash2(key)) % TABLESIZE;
        i++;
    }

    hashTable[insertAt].key = key;
    hashTable[insertAt].indicator = USED;
    return comparisons ;  // Count initial comparison
}

int HashDelete(int key, HashSlot hashTable[])
{
    int hash = hash1(key);
    int i = 0;
    int comparisons = 0;    // Number of comparisons should start from 0

    while (hashTable[hash].indicator != EMPTY && i < TABLESIZE) {
        if (hashTable[hash].indicator == USED) {
            comparisons++;      // Only compare when the slot is USED
            if (hashTable[hash].key == key) {
                hashTable[hash].indicator = DELETED;
                return comparisons;
            }
        }
        hash = (hash + hash2(key)) % TABLESIZE;
        i++;
    }

    return -1;  // Key not found
}
