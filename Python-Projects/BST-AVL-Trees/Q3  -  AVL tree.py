class AVLNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.height = 1

    def display(self):
        lines, *_ = self._display_aux()
        for line in lines:
            print(line)

    def _display_aux(self):
        """Returns list of strings, width, height, and horizontal coordinate of the root."""
        # No child
        if self.right is None and self.left is None:
            line = f"{self.value}(h={self.height}, bf={self.balance_factor()})"
            width = len(line)
            height = 1
            middle = width // 2
            return [line], width, height, middle

        # Only left child
        if self.right is None:
            lines, n, p, x = self.left._display_aux()
            s = f"{self.value}(h={self.height}, bf={self.balance_factor()})"
            u = len(s)
            first_line = (x + 1) * ' ' + (n - x - 1) * '_' + s
            second_line = x * ' ' + '/' + (n - x - 1 + u) * ' '
            shifted_lines = [line + u * ' ' for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, n + u // 2

        # Only right child
        if self.left is None:
            lines, n, p, x = self.right._display_aux()
            s = f"{self.value}(h={self.height}, bf={self.balance_factor()})"
            u = len(s)
            first_line = s + x * '_' + (n - x) * ' '
            second_line = (u + x) * ' ' + '\\' + (n - x - 1) * ' '
            shifted_lines = [u * ' ' + line for line in lines]
            return [first_line, second_line] + shifted_lines, n + u, p + 2, u // 2

        # Two children
        left, n, p, x = self.left._display_aux()
        right, m, q, y = self.right._display_aux()
        s = f"{self.value}(h={self.height}, bf={self.balance_factor()})"
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

    def balance_factor(self):
        left_height = self.left.height if self.left else 0
        right_height = self.right.height if self.right else 0
        return left_height - right_height

class AVLTree:
    def __init__(self):
        self.root = None

    def insert(self, value):
        self.root = self._insert_recursive(self.root, value)

    def _insert_recursive(self, node, value):
        if node is None:
            return AVLNode(value)
        
        if value < node.value:
            node.left = self._insert_recursive(node.left, value)
        else:
            node.right = self._insert_recursive(node.right, value)
        
        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))
        
        return self._rebalance(node)

    def delete_node(self, value):
        self.root = self._delete_recursive(self.root, value)

    def _delete_recursive(self, node, value):
        if node is None:
            return node
        
        if value < node.value:
            node.left = self._delete_recursive(node.left, value)
        elif value > node.value:
            node.right = self._delete_recursive(node.right, value)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                temp = self._min_value_node(node.right)
                node.value = temp.value
                node.right = self._delete_recursive(node.right, temp.value)
        
        if node is None:
            return node
        
        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))
        
        return self._rebalance(node)

    def _min_value_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current

    def _get_height(self, node):
        if node is None:
            return 0
        return node.height

    def _rebalance(self, node):
        balance = node.balance_factor()
        
        # Left Left Case
        if balance > 1 and node.left.balance_factor() >= 0:
            return self._right_rotate(node)
        
        # Right Right Case
        if balance < -1 and node.right.balance_factor() <= 0:
            return self._left_rotate(node)
        
        # Left Right Case
        if balance > 1 and node.left.balance_factor() < 0:
            node.left = self._left_rotate(node.left)
            return self._right_rotate(node)
        
        # Right Left Case
        if balance < -1 and node.right.balance_factor() > 0:
            node.right = self._right_rotate(node.right)
            return self._left_rotate(node)
        
        return node

    def _left_rotate(self, z):
        y = z.right
        T2 = y.left
        
        y.left = z
        z.right = T2
        
        z.height = 1 + max(self._get_height(z.left), self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        
        return y

    def _right_rotate(self, z):
        y = z.left
        T3 = y.right
        
        y.right = z
        z.left = T3
        
        z.height = 1 + max(self._get_height(z.left), self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        
        return y

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

    def search(self, value):
        return self._search_recursive(self.root, value)

    def _search_recursive(self, node, value):
        if node is None or node.value == value:
            return node
        if value < node.value:
            return self._search_recursive(node.left, value)
        return self._search_recursive(node.right, value)

    def node_depth(self, value):
        return self._node_depth_recursive(self.root, value, 0)

    def _node_depth_recursive(self, node, value, depth):
        if node is None:
            return -1
        if node.value == value:
            return depth
        left_depth = self._node_depth_recursive(node.left, value, depth + 1)
        if left_depth != -1:
            return left_depth
        return self._node_depth_recursive(node.right, value, depth + 1)

    def get_statistics(self):
        stats = {}
        self._collect_stats(self.root, 0, stats)
        return stats

    def _collect_stats(self, node, depth, stats):
        if node is None:
            return
        if depth not in stats:
            stats[depth] = 0
        stats[depth] += 1
        self._collect_stats(node.left, depth + 1, stats)
        self._collect_stats(node.right, depth + 1, stats)

def level_1_menu():
    print("\nLevel-1 Menu:")
    print("1. Pre-load a sequence of integers to build AVL tree")
    print("2. Manually enter integer keys one by one to build AVL tree")
    print("3. Exit")
    choice = input("Enter your choice (1-3): ")
    return choice

def level_2_menu(avl_tree):
    while True:
        print("\nLevel-2 Menu:")
        print("1. Display the AVL tree with height and balance factor")
        print("2. Print traversal sequences (pre-order, in-order, post-order)")
        print("3. Print leaf nodes and non-leaf nodes")
        print("4. Insert a new integer key")
        print("5. Delete an integer key")
        print("6. Display the statistic table")
        print("7. Return to level-1 menu")
        choice = input("Enter your choice (1-7): ")

        if choice == '1':
            print("\nAVL Tree Structure:")
            avl_tree.root.display()

        elif choice == '2':
            print("\nPre-order traversal:", avl_tree.pre_order(avl_tree.root))
            print("In-order traversal:", avl_tree.in_order(avl_tree.root))
            print("Post-order traversal:", avl_tree.post_order(avl_tree.root))

        elif choice == '3':
            print("\nLeaf nodes:", avl_tree.leaf_nodes(avl_tree.root))
            print("Non-leaf nodes:", avl_tree.non_leaf_nodes(avl_tree.root))

        elif choice == '4':
            key = int(input("Enter the new integer key to insert: "))
            if avl_tree.search(key):
                print(f"ERROR: node key {key} already exists in the AVL tree!")
            else:
                avl_tree.insert(key)
                print(f"Key {key} inserted successfully.")
                print("In-order traversal after insertion:", avl_tree.in_order(avl_tree.root))

        elif choice == '5':
            key = int(input("Enter the integer key to delete: "))
            if avl_tree.search(key):
                avl_tree.delete_node(key)
                print(f"Key {key} deleted successfully.")
                print("Tree after deletion:")
                avl_tree.root.display()
            else:
                print(f"ERROR: Node {key} not found!")

        elif choice == '6':
            stats = avl_tree.get_statistics()
            max_depth = max(stats.keys()) if stats else 0
            print("\nTable 1: The Statistic table (for nodes of different depths)")
            print("+--------------+------------------------------+")
            print("| Depth of nodes | Number of nodes in AVL tree |")
            print("+--------------+------------------------------+")
            for depth in range(max_depth + 1):
                count = stats.get(depth, 0)
                print(f"| {depth:<12} | {count:<28} |")
            print("+--------------+------------------------------+")

        elif choice == '7':
            return

        else:
            print("Invalid choice. Please try again.")

def main():
    while True:
        choice = level_1_menu()

        if choice == '1':
            preset_data = [55, 79, -31, 18, 40, 75, 29, 5, -1, -4, 95, 93, 43, 84, 53, 46, 47, 48, 44, 74, 90]
            avl_tree = AVLTree()
            for value in preset_data:
                avl_tree.insert(value)
            print("AVL tree created from preset data.")
            level_2_menu(avl_tree)

        elif choice == '2':
            avl_tree = AVLTree()
            print("Enter integers one by one (enter 'done' to finish):")
            while True:
                value = input("Enter an integer: ")
                if value.lower() == 'done':
                    break
                try:
                    avl_tree.insert(int(value))
                except ValueError:
                    print("Please enter a valid integer or 'done' to finish")
            level_2_menu(avl_tree)

        elif choice == '3':
            print("Exiting the program.")
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()