#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct Heap Heap;
typedef struct Node Node;
typedef int (*Comparator)(void* firstVal, void* secondVal);

struct Node {
	void* data;
	Node* parent;
	Node* leftChild;
	Node* rightChild;
};

struct Heap {
	Node* rootNode;
	Node* fillNode;
	Comparator compare;
};

static void printNode(Node* node) {
	// FIXME This is hardcoded just for ints for testing.
	printf("%p %d\n", node, *((int*) node->data));
}

static void printHeap(Heap* heap) {
	
}

static void percolateUp(Heap* heap, Node* node) {
	
}

static void percolateDown(Heap* heap, Node* node) {
	
}

static void switchData(Node* nodeOne, Node* nodeTwo) {
	void* temporaryData = nodeOne->data;
	nodeOne->data = nodeTwo->data;
	nodeTwo->data = temporaryData;
}

static Node* findUnfilledNode(Heap* heap) {
	if(heap->fillNode->leftChild == NULL || heap->fillNode->rightChild == NULL) {
		return heap->fillNode;
	}
	
	if (heap->fillNode == heap->rootNode) {
		return heap->rootNode->leftChild;
	}
	
	while(1){
		if(heap->fillNode == heap->fillNode->parent->rightChild) {  // If the filled node is it's parent's right child ...
			
			if(heap->fillNode->parent == heap->rootNode) {  // If the parent is root, this means the whole bottom layer is filled.
				heap->fillNode = heap->rootNode;
				while(heap->fillNode->leftChild != NULL){  // Find bottom-leftmost node and start a new layer.
					heap->fillNode = heap->fillNode->leftChild;
				}
			} else {  // If parent is not root ...
				heap->fillNode = heap->fillNode->parent;
			}
	
		} else { // If the filled node is it's parent's left child, then the right child is the next to be filled.
			
			heap->fillNode = heap->fillNode->parent->rightChild;
			return heap->fillNode;
			
		}
	}
}

Heap* heapify(void* iterableData) {
	
}

void heappush(Heap* heap, void* data) {
	Node* node = malloc(sizeof(Node));
	node->data = data;
	printNode(node);
	
	printf("before before\n");
	if(heap->rootNode == NULL) {
		printf("Before\n");
		heap->rootNode = node;
		heap->fillNode = node;
		printf("Here\n");
	} else {
		printf("Hereeee???\n");
		Node* parent = findUnfilledNode(heap);
		if(parent->leftChild == NULL) {
			parent->leftChild = node;
		} else {
			parent->rightChild = node;
		}
		node->parent = parent;
	}
}

void heapfree(Heap* heap) {
	
}

void heappop(Heap* heap) {
	
}

void heappeek(Heap* heap) {
	
}

void heapremove(Heap* heap, void* data) {
	
}



int main(int argc, char *argv[]) {
	Heap* heap = malloc(sizeof(Heap));
	int value = 3;
	heappush(heap, &value);
	
	printf("No errors!!\n");
	return 0;
}