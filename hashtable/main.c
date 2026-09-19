#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLESIZE 101

static struct hashBin {
    char* key;
    double value;
    struct hashBin* next;
};

static struct hashBin* table[TABLESIZE];

static int hash(char* keyPointer) {
    unsigned int hash = 0;

    while (*++keyPointer != '\0'){ 
        hash = hash << 1;
        hash = hash ^ *keyPointer;
    }

    return hash % TABLESIZE;
}

//Places the key-value pair in the hashmap.
//If an item already exists with the same key,
//it's value is updated.
void insert(char* key, double value) {
    struct hashBin* walker; 

    for (walker = table[hash(key)]; walker != NULL; walker = walker->next)
        if(strcmp(walker->key, key) == 0){
            walker->value = value;
            return;
        }
    walker = (struct hashBin *) malloc(sizeof(struct hashBin));
    walker->key = key;
    walker->value = value;
    walker->next = table[hash(key)];
    table[hash(key)] = walker;
}

//Searches for key in hashmap and returns the value 
//stored to the value pointer passed.
//Returns 0 if successful, returns -1 elsewise
int search(char* key, double* value){
    struct hashBin* walker; 

    for (walker = table[hash(key)]; walker != NULL; walker = walker->next)
        if(strcmp(walker->key, key) == 0){
            *value = walker->value;
            return 0;
        }
    return -1;
}
//    int index = hash(key);
//    struct hashBin* hbp = table[index];
//
//    while (hbp->key != NULL) 
//        if (strcmp(key, hbp->key) == 0){
//            *value = hbp->value;
//            return 0;
//        }
//        else if (hbp->next != NULL)
//            hbp = hbp->next;
//        else
//            break;
//    return -1;
//}

//Finds if a value is associated with the key given 
//and deletes it. Returns 0 if a value was found,
//-1 elsewise.
//int delete(char* key) {
//    int index = hash(key);
//    struct hashBin* hbp = &table[index];
//
//    while (hbp->key != NULL) 
//        if (strcmp(key, hbp->key) == 0)
//            if (hbp->next == NULL) {
//                hbp->key == NULL;
//                hbp->value == 0;
//                return 0;
//            } else {
//                *hbp = *(hbp->next);
//            }
//}

int main() {
    printf("testing the hash function\n");
    char key1[] = "Recipe Name";
    char key2[] = "Grain Matrix";
    printf("Key: %s, hash:%d\n", key1, hash(key1));
    printf("Key: %s, hash:%d\n", key2, hash(key2));

    insert("OG", 1.062);
    insert("OG", 1.056);
    double result;
    
    if (search("OG", &result) == 0)
        printf("the value associated with the key %s, is %f\n","OG", result);
    else
        printf("key does not exist in the hashmap");
    if (search("FG", &result) == 0)
        printf("the value associated with the key %s, is %f\n","OG", result);
    else
        printf("key does not exist in the hashmap\n");
    insert("FG", 1.008);
}