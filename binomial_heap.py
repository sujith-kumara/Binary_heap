"""
Min Heap Implementation in Python
"""
class MinHeap:
	def __init__(self):
		"""
		On this implementation the heap list is initialized with a value
		"""
		self.heap_list = [0]
		self.current_size = 0

	def sift_up(self, i):
		"""
		Moves the value up in the tree to maintain the heap property.
		"""
		# While the element is not the root or the left element
		Stop = False
		while (i // 2 > 0) and Stop == False:
			# If the element is less than its parent swap the elements
			if self.heap_list[i] < self.heap_list[i // 2]:
				self.heap_list[i], self.heap_list[i // 2] = self.heap_list[i // 2], self.heap_list[i]
			else:
				Stop = True
			# Move the index to the parent to keep the properties
			i = i // 2

	def insert(self, k):
		"""
		Inserts a value into the heap
		"""
		# Append the element to the heap
		self.heap_list.append(k)
		# Increase the size of the heap.
		self.current_size += 1
		# Move the element to its position from bottom to the top
		self.sift_up(self.current_size)

	def sift_down(self, i):
		# if the current node has at least one child
		while (i * 2) <= self.current_size:
			# Get the index of the min child of the current node
			mc = self.min_child(i)
			# Swap the values of the current element is greater than its min child
			if self.heap_list[i] > self.heap_list[mc]:
				self.heap_list[i], self.heap_list[mc] = self.heap_list[mc], self.heap_list[i]
			i = mc

	def min_child(self, i):
		# If the current node has only one child, return the index of the unique child
		if (i * 2)+1 > self.current_size:
			return i * 2
		else:
			# Herein the current node has two children
			# Return the index of the min child according to their values
			if self.heap_list[i*2] < self.heap_list[(i*2)+1]:
				return i * 2
			else:
				return (i * 2) + 1

	def delete_min(self):
		# Equal to 1 since the heap list was initialized with a value
		if len(self.heap_list) == 1:
			return 'Empty heap'

		# Get root of the heap (The min value of the heap)
		root = self.heap_list[1]

		# Move the last value of the heap to the root
		self.heap_list[1] = self.heap_list[self.current_size]

		# Pop the last value since a copy was set on the root
		*self.heap_list, _ = self.heap_list

		# Decrease the size of the heap
		self.current_size -= 1

		# Move down the root (value at index 1) to keep the heap property
		self.sift_down(1)

		# Return the min value of the heap
		return root
"""
Driver program
"""
# Same tree as above example.
def main():
    my_heap = MinHeap()
    while True:
        print("\nMin Heap Operations:")
        print("1. Insert element")
        print("2. Delete minimum element")
        print("3. Print heap elements")
        print("4. Quit")

        choice = input("Enter your choice: ")

        if choice == "1":
            element = int(input("Enter the element to insert: "))
            my_heap.insert(element)
        elif choice == "2":
            min_element = my_heap.delete_min()
            if min_element != 'Empty heap':
                print(f"Deleted minimum element: {min_element}")
            else:
                print("Heap is empty.")
        elif choice == "3":
            print("Heap elements:")
            for i in my_heap.heap_list[1:]:
                print(i, end=" ")
        elif choice == "4":
            print("Goodbye!")
            break
        else:
            print("Invalid choice. Please select a valid option.")

if __name__ == "__main__":
    main()