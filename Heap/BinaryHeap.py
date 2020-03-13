import uuid
import collections

Data = collections.namedtuple("Data", "data_id data")


class HeapNode:
    def __init__(self, data):
        self.data = Data(data_id=uuid.uuid4(), data=data)
        self.id = data
        self.parent_idx = None
        self.child_idx = None

    def __str__(self):
        return "HeapNode: {}".format(self.data.data)


class Heap:
    BREADTH = 1
    DEPTH = 2

    def __init__(self, comparator_function, iterable_data=None):
        self.__comparator_function = comparator_function

        self.__heap = []
        self.__id_to_idx = {}

        if iterable_data is None:
            return

        self.heapify(iterable_data)

    def __iter__(self):  # fixme can we do a type of iteration? Like breadth or depth first. Also remember __next__
        pass

    def __str__(self):
        return_string = "Heap["
        for node in self.__heap:
            return_string += "{"
            return_string += str(node)
            return_string += "}, "
        return return_string + "]"

    def __len__(self):
        return len(self.__heap)

    def heapify(self, iterable_data):
        for data in iterable_data:
            self.push(data)

    def push(self, data):
        new_node = HeapNode(data)

        self.__heap.append(new_node)
        self.__id_to_idx[new_node.data.data_id] = len(self.__heap) - 1
        self.__get_child_idx(new_node)
        self.__get_parent_idx(new_node)
        self.__percolate_up(new_node)

    def pop(self):
        if len(self.__heap) == 0:
            return None
        top_node_data = self.__heap[0].data

        self.__percolate_down(self.__heap[0])

        return top_node_data.data

    def peek(self):
        if len(self.__heap) == 0:
            return None

        return self.__heap[0].data.data

    def remove(self, data):
        for node in self.__heap:
            if node.data.data == data:
                self.__percolate_down(node)
                return

    def __percolate_up(self, node):
        current_index = self.__id_to_idx[node.data.data_id]

        while self.__heap[current_index].parent_idx is not None:  # If parent_idx is None we have reached root.
            current_node = self.__heap[current_index]
            parent_node = self.__heap[current_node.parent_idx]

            if self.__comparator_function(parent_node.data.data, current_node.data.data) > 0:
                self.__switch_data(parent_node, current_node)
                current_index = current_node.parent_idx
            else:
                return

    def __percolate_down(self, node):
        length = len(self.__heap)
        current_index = self.__id_to_idx[node.data.data_id]

        while self.__heap[current_index].child_idx < length:  # child_idx will go beyond length of heap for bottom nodes
            current_node = self.__heap[current_index]
            child_one_node = self.__heap[current_node.child_idx]
            child_two_node = None if current_node.child_idx+1 >= length else self.__heap[current_node.child_idx+1]

            if child_two_node is None or self.__comparator_function(child_two_node.data.data, child_one_node.data.data) > 0:
                self.__switch_data(current_node, child_one_node)
                current_index = current_node.child_idx
            else:
                self.__switch_data(current_node, child_two_node)
                current_index = current_node.child_idx+1

        current_node = self.__heap[current_index]
        self.__switch_data(self.__heap[-1], current_node)
        self.__heap.pop(-1)

    def __get_child_idx(self, node):
        if len(self.__heap) == 1:
            node.child_idx = 1
        else:
            node.child_idx = self.__heap[-2].child_idx + 2

    def __get_parent_idx(self, node):
        if len(self.__heap) == 1:
            return
        elif len(self.__heap) == 2:
            node.parent_idx = 0
        else:
            if self.__heap[-2].parent_idx == self.__heap[-3].parent_idx:
                node.parent_idx = self.__heap[-2].parent_idx + 1
            else:
                node.parent_idx = self.__heap[-2].parent_idx

    def __switch_data(self, node_one, node_two):
        temporary_index = self.__id_to_idx[node_one.data.data_id]
        self.__id_to_idx[node_one.data.data_id] = self.__id_to_idx[node_two.data.data_id]
        self.__id_to_idx[node_two.data.data_id] = temporary_index

        temporary_data = node_one.data
        node_one.data = node_two.data
        node_two.data = temporary_data


def foo(i, j):
    return i - j


x = [23,24,6,21,6534,34,67,83,7,0,1,5,212]
h = Heap(foo)
h.heapify(x)
for n in x:
    print(h.peek())
    print(h)
