#include <stdio.h>
#include "hash.h"
#include "blockchain.h"

int main(void) {

	//test cases
	unsigned char* helloWorld = "HelloWorld";
	unsigned char* robOlson = "RobOlson";
	unsigned char* csec = "CSEC";

	//technical documentation
	unsigned char* Rob = "Rob";
	unsigned char* James = "James";
	unsigned char* Luke = "Luke";

	unsigned char* helloWorldHash = SHA_40(helloWorld, strlen(helloWorld));
	unsigned char* robOlsonHash = SHA_40(robOlson, strlen(robOlson));
	unsigned char* csecHash = SHA_40(csec, strlen(csec));
	unsigned char* robHash = SHA_40(Rob, strlen(Rob));
	unsigned char* jamesHash = SHA_40(James, strlen(James));
	unsigned char* lukeHash = SHA_40(Luke, strlen(Luke));

	//printing hashes
	//printf("HelloWorld Hash: ");
	//printDigest((struct Digest*)helloWorldHash);
	//printf("RobOlson Hash: ");
	//printDigest((struct Digest*)robOlsonHash);
	//printf("CSEC Hash: ");
	//printDigest((struct Digest*)csecHash);
	printf("Rob Hash: ");
	printDigest((struct Digest*)robHash);
	printf("James Hash: ");
	printDigest((struct Digest*)jamesHash);
	printf("CSEC Hash: ");
	printDigest((struct Digest*)csecHash);
	printf("Luke Hash: ");
	printDigest((struct Digest*)lukeHash);

	if (digest_equal((struct Digest*)robHash, (struct Digest*)robHash) == 1) {
		printf("Rob and Rob: True\n");
	}
	else {
		printf("Rob and Rob: False\n");
	}
	if (digest_equal((struct Digest*)robHash, (struct Digest*)jamesHash) == 1) {
		printf("Rob and James: True\n");
	}
	else {
		printf("Rob and James: False\n");
	}
	//printf("Rob and Rob: %d\n", digest_equal((struct Digest*)robHash, (struct Digest*)robHash));
	//printf("Rob and James: %d\n", digest_equal((struct Digest*)robHash, (struct Digest*)jamesHash));


	//blockchain testing
	testBlockChain();

	return 1;
}