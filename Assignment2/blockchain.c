/*
 * CSEC-201
 * Authors: CSEC-201 Instructors
 * Semester: 2221
 * Purpose: Blockchain implementation
 */

#include "blockchain.h"

 /*
  * Name: initialize
  * Purpose: Creates and returns a pointer to an empty blockchain
  * Parameters: None
  * Returns: pointer to Blockchain
  */
struct Blockchain* initialize()
{
    struct Blockchain* chain = (struct Blockchain*)malloc(sizeof(struct Blockchain));
    chain->size = 0;
    chain->head = NULL;
    return chain;
}

/*
 * Name: print_blockchain
 * Purpose: Prints blockchain
 * Parameters: Pointer to Blockchain
 * Returns: None
 */
void print_blockchain(struct Blockchain* blockchain)
{
    printf("Printing...\n");
    struct Block* current = blockchain->head;
    while (current) {
        printf("{height: %d, data: %d, prev_hash: %d %d %d %d %d}\n",
            current->height, current->data, current->prev_hash.hash0, current->prev_hash.hash1,
            current->prev_hash.hash2, current->prev_hash.hash3, current->prev_hash.hash4);
        current = current->prev_block;
    }
}

/*
 * Name: test
 * Purpose: Test functions above
 */
int testBlockChain(void)
{

    //Create, print, and verify blockchain
    struct Blockchain* blockchain = initialize();
    for (int i = 1; i <= 5; i++)
    {
        add(blockchain, 10 * i);
    }
    
    //Test cases
    //Test 1
    print_blockchain(blockchain);
    verify(blockchain);

    //Test 2
    //Alter the value in a block, print, and verify blockchain
    alter_block(blockchain, 2, 300);
    print_blockchain(blockchain);
    verify(blockchain);

    //Test 3
    //Comment out Test 2, and uncomment the following three code lines
    //Alter the value in a block and the hash value tracked for
    //that altered block
    //alter_2_blocks(blockchain, 1, 200);
    //print_blockchain(blockchain);
    //verify(blockchain);

    //Test 4
    //Comment out Test 2 and 3, and uncomment the following three code lines
    //delete_at(blockchain, 1);
    //print_blockchain(blockchain);
    //verify(blockchain);

    return 0;
}

void set_digest(struct Digest* digest, struct Block* block) {
    struct Digest* computedHash = (struct Digest*)SHA_40((BYTE*)block, BLOCK_SIZE);
    digest->hash0 = computedHash->hash0;
    digest->hash1 = computedHash->hash1;
    digest->hash2 = computedHash->hash2;
    digest->hash3 = computedHash->hash3;
    digest->hash4 = computedHash->hash4;
}

void add(struct Blockchain* chain, int data) {
    struct Block* newblock = (struct Block*)malloc(BLOCK_SIZE);
    if (chain->head != NULL) {
        newblock->prev_block = chain->head;
        set_digest(&newblock->prev_hash, newblock->prev_block);
    }
    else {
        newblock->prev_block = NULL;
        newblock->prev_hash.hash0 = 0;
        newblock->prev_hash.hash1 = 0;
        newblock->prev_hash.hash2 = 0;
        newblock->prev_hash.hash3 = 0;
        newblock->prev_hash.hash4 = 0;
    }
    newblock->data = data;
    chain->head = newblock;
    newblock->height = chain->size;
    chain->size++;
}

void verify(struct Blockchain* chain) {
    struct Block* currentblock = chain->head;

    while (currentblock->prev_block != NULL) {
        struct Digest temp;
        set_digest(&temp, currentblock->prev_block);
        if (digest_equal(&temp, &currentblock->prev_hash) == 1) {
            printf("Block %d passed\n", currentblock->height);
        }
        else {
            printf("Block %d failed\n", currentblock->height);
            return;
        }
        //printDigest(&temp); test code
        //printDigest(&currentblock->prev_hash);
        currentblock = currentblock->prev_block;
    }
    
    printf("Block 0 passed\n");
    printf("All blocks have been verified\n");
}

void delete_at(struct Blockchain* chain, int height) {
    printf("Deleting...\n");
    if (chain->head->height == height) {
        struct Block* temp = chain->head;
        chain->head = temp->prev_block;
        chain->size--;
        free(temp);
    }
    else {
        struct Block* temp = chain->head;
        while (temp->prev_block != NULL)
        {
            if (temp->prev_block->height == height) {
                struct Block* blockToDelete = temp->prev_block;
                temp->prev_block = blockToDelete->prev_block;
                free(blockToDelete);
                printf("Block %d deleted\n", height);
                chain->size--;
                return;
            }
            temp = temp->prev_block;
        }
    }
}

void alter_block(struct Blockchain* chain, int height, int data) {
	struct Block* temp = chain->head;
	while (temp != NULL) {
		if (temp->height == height) {
            printf("Altering a block...\n");
			temp->data = data;
            printf("Block %d altered containing now %d\n", temp->height, temp->data);
            return;
		}
		temp = temp->prev_block;
	}
}

void alter_2_blocks(struct Blockchain* chain, int height, int data) {
    struct Block* temp = chain->head;
    while (temp != NULL) {
        if (temp->height == height) {
            printf("Altering two blocks...\n");
            temp->data = data;
            printf("Block %d altered containing now %d\n", temp->height, temp->data);
            struct Digest new_digest;
            set_digest(&new_digest, temp);

            //find block before
            struct Block* nextblock = chain->head;
            while (nextblock->prev_block != temp) {
                nextblock = nextblock->prev_block;
            }
            nextblock->prev_hash = new_digest;
            printf("Block %d altered too\n", temp->height+1);
            return;
        }
        temp = temp->prev_block;
    }
}