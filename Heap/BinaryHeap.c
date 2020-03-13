#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct Heap Heap;
typedef struct Node Node;
typedef void* (*Method)(void* argv);

struct Node {
	void* data;
	Node* parent;
	Node* child_one;
	Node* child_two;
};

struct Heap {
	Node* root;
	Method comparator;
};

Heap* heapify(void* iterableData) {
	
}

void heappush(Heap* heap, void* data) {
	
}

void heappop(Heap* heap) {
	
}

void heappeek(Heap* heap) {
	
}

void heapremove(Heap* heap, void* data) {
	
}

static void percolateUp(Heap* heap, Node* node) {
	
}

static void percolateDown(Heap* heap, Node* node) {
	
}

static void switchData(Node* nodeOne, Node* nodeTwo) {
	
}

int main(int argc, char *argv[]) {
	Heap heap;
	
	
	printf("No errors!!\n");
	return 0;
}