#include "LinkedList.h"

int main() {
  List list;

  list.pushHead("Hello");
  list.pushHead("world");
  auto *node = new ListNode("I");
  node->rand = list.back();
  list.pushNode(node);
  node = new ListNode("am");
  node->rand = list.front();
  list.pushNode(node);
  list.pushHead("human\n");

  FILE *file = fopen("../file.txt", "wb");
  list.Serialize(file);
  fclose(file);

  file = fopen("../file.txt", "rb");
  List other;
  other.Deserialize(file);
  fclose(file);

  if (list == other)
    std::cout << "Success" << std::endl;
  else
    std::cout << "Not Success" << std::endl;
}
