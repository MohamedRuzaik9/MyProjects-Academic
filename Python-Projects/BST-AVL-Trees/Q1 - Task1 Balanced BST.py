class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def display(self):
        lines, *_ = self._display_aux()
        for line in lines:
            print(line)

    def _display_aux(self):
        # No child
        if self.right is None and self.left is None:
            line = str(self.value)
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle

        # Only left child
        if self.right is None:
            lines, n, p, x = self.left._display_aux()
            s = str(self.value)
            u = len(s)
            first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s
            second_line = x * ' ' + '/' + (n - x - 1 + u) * ' '
            shifted_lines = [line + u * ' ' for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, n + u // 2

        # Only right child
        if self.left is None:
            lines, n, p, x = self.right._display_aux()
            s = str(self.value)
            u = len(s)
            first_line = s + x * '_' + (n - x) * ' '
            second_line = (u + x) * ' ' + '\\' + (n - x - 1) * ' '
            shifted_lines = [u * ' ' + line for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, u // 2

        # Two children
        left, n, p, x = self.left._display_aux()
        right, m, q, y = self.right._display_aux()
        s = str(self.value)
        u = len(s)
        first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s + y * '_' + (m - y) * ' '
        second_line = x * ' ' + '/' + (n - x - 1 + u + y) * ' ' + '\\' + (m - y - 1) * ' '
        if p < q:
            left += [n * ' '] * (q - p)
        elif q < p:
            right += [m * ' '] * (p - q)
        zipped_lines = zip(left, right)
        lines = [first_line, second_line] + [a + u * ' ' + b for a, b in zipped_lines]
        return lines, n + m + u, max(p, q) + 2, n + u // 2

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def balanced_bst_seq(A, B):
    n = len(A)
    if n == 0:
        return B
    
    middle_index = n // 2
    
    B.append(A[middle_index])
    balanced_bst_seq(A[:middle_index], B)
    balanced_bst_seq(A[middle_index+1:], B)
    
    return B

def create_balanced_bst(A):
    # Step 1: Sort the input array
    sorted_A = merge_sort(A)    
    # Step 2: Generate balanced insertion sequence
    B = []
    balanced_bst_seq(sorted_A, B)    
    # Step 3: Build BST from the balanced sequence
    if not B:
        return None
    
    root = TreeNode(B[0])
    for value in B[1:]:
        insert_into_bst(root, value)    
    return root, B

def insert_into_bst(node, value):
    if value < node.value:
        if node.left is None:
            node.left = TreeNode(value)
        else:
            insert_into_bst(node.left, value)
    else:
        if node.right is None:
            node.right = TreeNode(value)
        else:
            insert_into_bst(node.right, value)

def demonstrate_algorithm(dataset_name, dataset):
    print(f"\n--------------------- Demonstration ----------------------------")
    print("Original array:")
    print(dataset)    
    root, balanced_sequence = create_balanced_bst(dataset.copy())    
    print("\nRe-arranged sequence for balanced BST:")
    print(balanced_sequence)    
    print("\nTree Visualization:")
    root.display()

# Main program
if __name__ == "__main__":
    # First dataset
    A = [19, -1, 45, 6, 8, 21, 34, 5, 55, 65, 543, 2, 18, 90, 122, 132, 0, 66, 100, -12, 17]
    demonstrate_algorithm("Dataset A", A)    
    # Second dataset
    B = [7, 4, 16, 3, 5, 12, 20]
    demonstrate_algorithm("Dataset B", B)
