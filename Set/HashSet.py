# Not Functional

class SetBin:
    def __init__(self):
        self.bin = []


class HashSet:
    def __init__(self, iterable_data=None):

        if iterable_data is None:
            self.__set = [None] * 100

        self.__set = [None] * (len(iterable_data) * 4)


