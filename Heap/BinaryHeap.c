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

static void printNode(Node* node, int printChildren) {
	// FIXME This is hardcoded just for ints for testing.
	printf("%p %d\n", node, *((int*) node->data));
	
	if(printChildren) {
		if(node->leftChild != NULL) {
			printNode(node->leftChild, 1);
		}
		
		if(node->rightChild != NULL) {
			printNode(node->rightChild, 1);
		}
	}
}

static void printHeap(Heap* heap) {
	printNode(heap->rootNode, 1);
}

static void switchData(Node* nodeOne, Node* nodeTwo) {
	void* temporaryData = nodeOne->data;
	nodeOne->data = nodeTwo->data;
	nodeTwo->data = temporaryData;
}

static void percolateUp(Heap* heap, Node* node) {
	Node* currentNode = node;
	while(currentNode->parent != NULL) {
		if(heap->compare(currentNode->data, currentNode->parent->data) < 0) {
			switchData(currentNode, currentNode->parent);
			currentNode = currentNode->parent;
		} else {
			return;
		}
	}
}

static void percolateDown(Heap* heap, Node* node) {
	
}

static Node* findUnfilledNode(Heap* heap) {
	if(heap->fillNode->leftChild == NULL || heap->fillNode->rightChild == NULL) {
		return heap->fillNode;
	}
	
	if (heap->fillNode == heap->rootNode) {
		heap->fillNode = heap->rootNode->leftChild;
		return heap->rootNode->leftChild;
	}
	
	while(1){
		if(heap->fillNode == heap->fillNode->parent->rightChild) {  // If the filled node is it's parent's right child ...
			
			if(heap->fillNode->parent == heap->rootNode) {  // If the parent is root, this means the whole bottom layer is filled.
				heap->fillNode = heap->rootNode;
				while(heap->fillNode->leftChild != NULL){  // Find bottom-leftmost node and start a new layer.
					heap->fillNode = heap->fillNode->leftChild;
				}
				return heap->fillNode;
				
			} else {  // If parent is not root ...
			
				heap->fillNode = heap->fillNode->parent;
				
			}
	
		} else { // If the filled node is it's parent's left child, then the right child is the next to be filled.	
		
			heap->fillNode = heap->fillNode->parent->rightChild;
			while(heap->fillNode->leftChild != NULL) {
				heap->fillNode = heap->fillNode->leftChild;
			}
			return heap->fillNode;
			
		}
	}
}

void heappush(Heap* heap, void* data) {
	Node* node = malloc(sizeof(Node));
	node->data = data;
	
	if(heap->rootNode == NULL) {
		heap->rootNode = node;
		heap->fillNode = node;
	} else {
		Node* parent = findUnfilledNode(heap);
		if(parent->leftChild == NULL) {
			parent->leftChild = node;
		} else {
			parent->rightChild = node;
		}
		node->parent = parent;
		
		percolateUp(heap, node);
	}
}

Heap* heapify(Comparator compare, void* iterableData, int length, int size) {
	Heap* heap = malloc(sizeof(Heap));
	heap->compare = compare;
	for(unsigned int i = 0; i < length*size; i+=size) {
		heappush(heap, &iterableData[i]);
	}
	return heap;
}

void heapfree(Heap* heap) {
	void freenode(Node* node) {
		if(node->leftChild != NULL) {
			freenode(node->leftChild);
		}
		if(node->rightChild != NULL) {
			freenode(node->rightChild);
		}
		printf("Freeing ");
		printNode(node, 0);
		free(node);
	}
	if(heap->rootNode != NULL) {
		freenode(heap->rootNode);
	}
	free(heap);
}

void heappop(Heap* heap) {
	
}

void* heappeek(Heap* heap) {
	if(heap->rootNode == NULL) {
		return NULL;
	}
	
	return heap->rootNode->data;
}

void heapremove(Heap* heap, void* data) {
	
}



int testCompare(void* val1, void* val2) {
	return *((int*) val1) - *((int*) val2);
}

int main(int argc, char *argv[]) {
	int values[] = {3, 5, 1, 52, 2, 33, 51, 0, 522, 23};
	
	Heap* heap = heapify(testCompare, values, sizeof(values)/sizeof(values[0]), sizeof(int));			
	
	printf("Peeking = %d\n", *((int*) heappeek(heap)));
	printf("\n");
	printHeap(heap);
	
	heapfree(heap);
	
	printf("No errors!!\n");
	return 0;
}