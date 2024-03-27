#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
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
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
 // Write your code here
    if (HashFind(key, hashTable) == -1) {
        int index = hash(key);

        if (hashTable[index].indicator == EMPTY) {
            hashTable[index].key = key;
            hashTable[index].indicator = USED;
            return index;
        } else {
            while (hashTable[index].next != -1) {
                index = hashTable[index].next;
            }
             if (hashTable[index].indicator == EMPTY) {
                 hashTable[index].key = key;
                 hashTable[index].indicator = USED;
                 return index;
             }

            int i;
            int temp;
            for (i = index + 1; i < TABLESIZE + index; i++) {
                if (hashTable[i % TABLESIZE].indicator == EMPTY) {
                    temp = i % TABLESIZE;
                    break;
                }
            }
            if (i == TABLESIZE + index) {
                return TABLESIZE;
            }
            hashTable[index].next = temp;
            hashTable[temp].key = key;
            hashTable[temp].indicator = USED;
            return temp;
        }
        
    }
    return -1;
}


int HashFind(int key, HashSlot hashTable[])
{
 // Write your code here
    int index = hash(key);
    while(index != -1){
        if(hashTable[index].indicator == EMPTY){
            return -1;
        }
        if(hashTable[index].key == key){
            return index;
        }
        index = hashTable[index].next;
    }
    return -1;
}
