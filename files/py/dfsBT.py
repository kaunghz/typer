class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def dfs_binary_tree(root):
    if not root:
        return
    stack = [root]
    while stack:
        node = stack.pop()
        print(node.val, end=" ")
        if node.right:
            stack.append(node.right)
        if node.left:
            stack.append(node.left)