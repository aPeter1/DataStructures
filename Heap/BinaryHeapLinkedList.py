
class HeapNode:
    def __init__(self, value, parent=None):
        self.value = value
        self.parent = parent
        self.child_one = None
        self.child_two = None
        
    def __str__(self):
        return "HeapNode - {}, parent={}, child_one={}, child_two={}".format(self.value, self.parent,
                                                                             self.child_one, self.child_two)

    def is_filled(self):
        return self.child_one is not None and self.child_two is not None


class HeapLinkedList:
    def __init__(self, iterable_data=None):
        self.root = None
        self.__last = None
    
        if iterable_data is None:
            return
            
        for value in iterable_data:
            self.insert(value)
        
    def insert(self, value):
        new_node = HeapNode(value)

        if self.root is None:
            self.root = new_node
            self.__last = self.root

    def pop(self):
        pass

    def push(self, value):
        pass

    def remove(self, value):
        pass

    def change_key(self, value):
        pass

    def __percolate(self, node: HeapNode):
        pass

    def __find_unfilled(self, node: HeapNode) -> HeapNode:
        pass
