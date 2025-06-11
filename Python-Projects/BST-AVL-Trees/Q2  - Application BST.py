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
        """Returns list of strings, width, height, and horizontal coordinate of the root."""
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

class BST:
    def __init__(self):
        self.root = None

    def insert(self, value):
        if self.root is None:
            self.root = TreeNode(value)
        else:
            self._insert_recursive(self.root, value)

    def _insert_recursive(self, node, value):
        if value < node.value:
            if node.left is None:
                node.left = TreeNode(value)
            else:
                self._insert_recursive(node.left, value)
        elif value > node.value:
            if node.right is None:
                node.right = TreeNode(value)
            else:
                self._insert_recursive(node.right, value)

    def pre_order(self, node):
        if node is None:
            return []
        return [node.value] + self.pre_order(node.left) + self.pre_order(node.right)

    def in_order(self, node):
        if node is None:
            return []
        return self.in_order(node.left) + [node.value] + self.in_order(node.right)

    def post_order(self, node):
        if node is None:
            return []
        return self.post_order(node.left) + self.post_order(node.right) + [node.value]

    def leaf_nodes(self, node):
        if node is None:
            return []
        if node.left is None and node.right is None:
            return [node.value]
        return self.leaf_nodes(node.left) + self.leaf_nodes(node.right)

    def non_leaf_nodes(self, node):
        if node is None or (node.left is None and node.right is None):
            return []
        return [node.value] + self.non_leaf_nodes(node.left) + self.non_leaf_nodes(node.right)

    def count_nodes(self, node):
        if node is None:
            return 0
        return 1 + self.count_nodes(node.left) + self.count_nodes(node.right)

    def node_depth(self, node, target, depth=0):
        if node is None:
            return -1
        if node.value == target:
            return depth
        left_depth = self.node_depth(node.left, target, depth + 1)
        if left_depth != -1:
            return left_depth
        return self.node_depth(node.right, target, depth + 1)

    def subtree_depth(self, node):
        if node is None:
            return -1
        return 1 + max(self.subtree_depth(node.left), self.subtree_depth(node.right))

    def search(self, node, value):
        if node is None:
            return None
        if node.value == value:
            return node
        if value < node.value:
            return self.search(node.left, value)
        return self.search(node.right, value)

    def delete_node(self, node, key):
        if node is None:
            return node

        if key < node.value:
            node.left = self.delete_node(node.left, key)
        elif key > node.value:
            node.right = self.delete_node(node.right, key)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left

            temp = self._min_value_node(node.right)
            node.value = temp.value
            node.right = self.delete_node(node.right, temp.value)
        return node

    def _min_value_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current

    def balanced_bst_seq(self, A, B):
        n = len(A)
        if n == 0:
            return B

        if n % 2 == 0:
            middle_index = n // 2
        else:
            middle_index = (n - 1) // 2

        B.append(A[middle_index])
        self.balanced_bst_seq(A[:middle_index], B)
        self.balanced_bst_seq(A[middle_index + 1:], B)
        return B

    def create_balanced_bst(self, A):
        sorted_A = sorted(A)
        B = []
        self.balanced_bst_seq(sorted_A, B)
        
        balanced_bst = BST()
        for value in B:
            balanced_bst.insert(value)
        return balanced_bst

    def calculate_root_index(self, A):
        n = len(A)
        if n == 0:
            return -1
        
        # Calculate the height of the complete tree
        h = 0
        while (1 << (h+1)) - 1 <= n:
            h += 1
        
        # Number of nodes in the last level
        last_level = n - ((1 << h) - 1)
        
        # Maximum possible nodes in last level
        max_last_level = 1 << h
        
        if last_level <= max_last_level // 2:
            return n - 1 - ((1 << (h-1)) - 1)
        else:
            return (1 << h) - 1

    def complete_bst_seq(self, A, B):
        n = len(A)
        if n == 0:
            return B
        
        root_index = self.calculate_root_index(A)
        B.append(A[root_index])
        self.complete_bst_seq(A[:root_index], B)
        self.complete_bst_seq(A[root_index+1:], B)
        return B

    def create_complete_bst(self, A):
        sorted_A = sorted(A)
        B = []
        self.complete_bst_seq(sorted_A, B)
        
        complete_bst = BST()
        for value in B:
            complete_bst.insert(value)
        return complete_bst

def level_1_menu():
    print("\nLevel-1 Menu:")
    print("1. Load a preset sequence of integers to build a BST")
    print("2. Manually enter integer keys one by one to build a BST")
    print("3. Exit")
    choice = input("Enter your choice (1-3): ")
    return choice

def level_2_menu(bst):
    while True:
        print("\nLevel-2 Menu:")
        print("1. Display the tree shape and traversal sequences")
        print("2. Display all leaf nodes and non-leaf nodes")
        print("3. Display a subtree and count its nodes")
        print("4. Display the depth of a given node")
        print("5. Display the depth of a subtree")
        print("6. Insert a new integer key")
        print("7. Delete an integer key")
        print("8. Convert to balanced BST")
        print("9. Convert to complete BST")
        print("10. Return to level-1 menu")
        choice = input("Enter your choice (1-10): ")

        if choice == '1':
            print("\nTree Shape:")
            bst.root.display()
            print("\nPre-order traversal:", bst.pre_order(bst.root))
            print("In-order traversal:", bst.in_order(bst.root))
            print("Post-order traversal:", bst.post_order(bst.root))

        elif choice == '2':
            print("\nLeaf nodes:", bst.leaf_nodes(bst.root))
            print("Non-leaf nodes:", bst.non_leaf_nodes(bst.root))

        elif choice == '3':
            key = int(input("Enter the key value of the subtree root: "))
            subtree_root = bst.search(bst.root, key)
            if subtree_root:
                print("\nSubtree rooted at", key, ":")
                subtree_root.display()
                print("Number of nodes in subtree:", bst.count_nodes(subtree_root))
            else:
                print(f"ERROR: Node {key} not found!")

        elif choice == '4':
            key = int(input("Enter the key value of the node: "))
            depth = bst.node_depth(bst.root, key)
            if depth != -1:
                print(f"Depth of node {key}: {depth}")
            else:
                print(f"ERROR: Node {key} not found!")

        elif choice == '5':
            key = int(input("Enter the key value of the subtree root: "))
            subtree_root = bst.search(bst.root, key)
            if subtree_root:
                depth = bst.subtree_depth(subtree_root)
                print(f"Depth of subtree rooted at {key}: {depth}")
            else:
                print(f"ERROR: Subtree rooted at node {key} not found!")

        elif choice == '6':
            key = int(input("Enter the new integer key to insert: "))
            if bst.search(bst.root, key):
                print(f"ERROR: node key {key} already exists in the BST!")
            else:
                bst.insert(key)
                print("In-order traversal after insertion:", bst.in_order(bst.root))

        elif choice == '7':
            key = int(input("Enter the integer key to delete: "))
            if bst.search(bst.root, key):
                bst.root = bst.delete_node(bst.root, key)
                print("Tree after deletion:")
                bst.root.display()
            else:
                print(f"ERROR: Node {key} not found!")

        elif choice == '8':
            balanced_bst = bst.create_balanced_bst(bst.in_order(bst.root))
            print("\nBalanced BST created:")
            balanced_bst.root.display()
            bst.root = balanced_bst.root

        elif choice == '9':
            complete_bst = bst.create_complete_bst(bst.in_order(bst.root))
            print("\nComplete BST created:")
            complete_bst.root.display()
            bst.root = complete_bst.root

        elif choice == '10':
            return

        else:
            print("Invalid choice. Please try again.")

def main():
    while True:
        choice = level_1_menu()

        if choice == '1':
            preset_data = [67, 93, 77, 32, 47, 91, 35, 26, 33, 115, 
                          104, 57, 97, 63, 59, 60, 62, 58, 3, -7]
            bst = BST()
            for value in preset_data:
                bst.insert(value)
            print("BST created from preset data.")
            level_2_menu(bst)

        elif choice == '2':
            bst = BST()
            print("Enter integers one by one (enter 'done' to finish):")
            while True:
                value = input("Enter an integer: ")
                if value.lower() == 'done':
                    break
                try:
                    bst.insert(int(value))
                except ValueError:
                    print("Please enter a valid integer or 'done' to finish")
            level_2_menu(bst)

        elif choice == '3':
            print("Exiting the program.")
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()