#include <ins/avl/AVLTree.h>
#include <stdlib.h>
#include <vector>

const int min_count = 16;
const int max_count = 1024;

void generateRandomKeys(std::vector<int>& keys, int count) {

  // Generate keys
  for (int i = 0; i < count; i++) {
    keys.push_back(i);
  }

  // Randomize keys order
  for (int i = 0; i < count; i++) {
    int x = i;
    int y = rand() % count;
    int tmp = keys[x];
    keys[x] = keys[y];
    keys[y] = tmp;
  }
}

void main()
{
  AVLTree tree;
  std::vector<int> used_keys;
  generateRandomKeys(used_keys, max_count);

  for (int cycle = 0; cycle < 2; cycle++) {

    // Insertions
    for (int key : used_keys) {
      tree.insert(key);
    }
    //tree.printTree();
    //tree.printValues();
    printf("\n");

    // Deletions
    for (int i = min_count; i < max_count; i++) {
      tree.remove(used_keys[i]);
    }
    tree.printTree();
    tree.printValues();
    printf("\n");

    // Remove upper
    tree.removeUpper(220);
    tree.printValues();
    printf("\n");
  }
  getchar();
}
