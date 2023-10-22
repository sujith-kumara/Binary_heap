import math

class FibonacciTree:
    def __init__(self, value):
        self.value = value
        self.child = []
        self.order = 0

    def add_at_end(self, t):
        self.child.append(t)
        self.order = self.order + 1

class FibonacciHeap:
    def __init__(self):
        self.trees = []
        self.least = None
        self.count = 0

    def insert_node(self, value):
        new_tree = FibonacciTree(value)
        self.trees.append(new_tree)
        if (self.least is None or value < self.least.value):
            self.least = new_tree
        self.count = self.count + 1

    def get_min(self):
        if self.least is None:
            return None
        return self.least.value

    def extract_min(self):
        smallest = self.least
        if smallest is not None:
            for child in smallest.child:
                self.trees.append(child)
            self.trees.remove(smallest)
            if self.trees == []:
                self.least = None
            else:
                self.least = self.trees[0]
                self.consolidate()
            self.count = self.count - 1
            return smallest.value

    def consolidate(self):
        aux = (floor_log(self.count) + 1) * [None]

        while self.trees != []:
            x = self.trees[0]
            order = x.order
            self.trees.remove(x)
            while aux[order] is not None:
                y = aux[order]
                if x.value > y.value:
                    x, y = y, x
                x.add_at_end(y)
                aux[order] = None
                order = order + 1
            aux[order] = x

        self.least = None
        for k in aux:
            if k is not None:
                self.trees.append(k)
                if (self.least is None or k.value < self.least.value):
                    self.least = k

    def display_elements(self):
        elements = []
        for tree in self.trees:
            elements.extend(self._traverse_tree(tree))
        return elements

    def _traverse_tree(self, tree):
        elements = [tree.value]
        for child in tree.child:
            elements.extend(self._traverse_tree(child))
        return elements

def floor_log(x):
    return math.frexp(x)[1] - 1

def main():
    fibonacci_heap = FibonacciHeap()

    while True:
        print("\nFibonacci Heap Operations:")
        print("1. Insert element")
        print("2. Get minimum element")
        print("3. Extract minimum element")
        print("4. Display heap elements")
        print("5. Quit")

        choice = input("Enter your choice: ")

        if choice == "1":
            element = int(input("Enter the element to insert: "))
            fibonacci_heap.insert_node(element)
        elif choice == "2":
            min_element = fibonacci_heap.get_min()
            if min_element is not None:
                print(f"Minimum element: {min_element}")
            else:
                print("Heap is empty.")
        elif choice == "3":
            min_element = fibonacci_heap.extract_min()
            if min_element is not None:
                print(f"Extracted minimum element: {min_element}")
            else:
                print("Heap is empty.")
        elif choice == "4":
            elements = fibonacci_heap.display_elements()
            print("Heap elements:", elements)
        elif choice == "5":
            print("Goodbye!")
            break
        else:
            print("Invalid choice. Please select a valid option.")

if __name__ == "__main__":
    main()
