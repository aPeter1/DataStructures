#include<stdio.h>
#include<stdlib.h>

// Definitions

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
	int size;
	Node* rootNode;
	Node* fillNode;
	Node* lastNode;
	Comparator compare;
};

// Private Functions

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

static Node* findPreviousNode(Heap* heap) {
	Node* currentNode = heap->lastNode;
	
	if(currentNode == heap->rootNode) {
		return NULL;
	}
	
	if(currentNode->parent->rightChild == currentNode) {
		return currentNode->parent->leftChild;
	}
	
	Node* rootNode = heap->rootNode;
	while(1) {
		currentNode = currentNode->parent;
		
		if(currentNode == rootNode) {
			while(currentNode->rightChild != NULL) {
				currentNode = currentNode->rightChild;
			}
			return currentNode;
		}
		
		if(currentNode->parent->rightChild == currentNode) {
			currentNode = currentNode->parent->leftChild;
			while(currentNode->rightChild != NULL) {
				currentNode = currentNode->rightChild;
			}
			return currentNode;
		}
	}
}

static void percolateDown(Heap* heap, Node* node) {
	Node* currentNode = node;
	while(currentNode->leftChild != NULL) {
		if(currentNode->rightChild != NULL && heap->compare(currentNode->rightChild->data, currentNode->leftChild->data) < 0) {
			switchData(currentNode, currentNode->rightChild);
			currentNode = currentNode->rightChild;
		} else {
			switchData(currentNode, currentNode->leftChild);
			currentNode = currentNode->leftChild;
		}
	}
	
	Node* lastNode = heap->lastNode;
	
	if(lastNode != NULL) {	
		switchData(currentNode, lastNode);
		
		heap->lastNode = findPreviousNode(heap);
		
		if(lastNode->parent->leftChild == lastNode) {
			lastNode->parent->leftChild = NULL;
		} else {
			lastNode->parent->rightChild = NULL;
		}
		
		if(lastNode != currentNode) {
			percolateUp(heap, currentNode);
		}
		lastNode = NULL;
	}
}

// Public Functions

void heappush(Heap* heap, void* data) {	
	Node* node = malloc(sizeof(Node));
	node->data = data;
	
	if(heap->rootNode == NULL) {
		heap->rootNode = node;
		heap->fillNode = node;
		heap->size = 0;
	} else {
		Node* parent = findUnfilledNode(heap);
		if(parent->leftChild == NULL) {
			parent->leftChild = node;
		} else {
			parent->rightChild = node;
		}
		node->parent = parent;
		heap->lastNode = node;
		
		percolateUp(heap, node);
	}
	heap->size++;
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
		if(node != NULL && node->leftChild != NULL) {
			freenode(node->leftChild);
		}
		
		if(node != NULL && node->rightChild != NULL) {
			freenode(node->rightChild);
		}
		free(node);
	}
	
	if(heap->rootNode != NULL) {
		freenode(heap->rootNode);
	}
	free(heap);
}

void* heappop(Heap* heap) {
	
	
	if(heap->rootNode == NULL) {
		return NULL;
	} else if (heap->rootNode->leftChild == NULL) {
		void* data = heap->rootNode->data;
		heap->rootNode = NULL;
		heap->lastNode = NULL;
		heap->fillNode = NULL;
		heap->size--;
		return data;
	}
	
	void* data = heap->rootNode->data;
		
	percolateDown(heap, heap->rootNode);
	
	heap->size--;
	return data;
}

void* heappeek(Heap* heap) {
	if(heap->rootNode == NULL) {
		return NULL;
	}
	
	return heap->rootNode->data;
}

int heaplen(Heap* heap) {
	return heap->size;
}
