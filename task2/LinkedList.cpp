#include "LinkedList.h"
#define MAX_SIZE 1000

// create and push new node with data at the end
void List::pushHead(const std::string &data) {
  ListNode *node = new ListNode(data);

  if (tail != nullptr) {
    node->prev = tail;
    tail->next = node;
  } else {
    head = node;
  }
  tail = node;

  count++;
}

// push new node at the end
void List::pushNode(ListNode *node) {
  if (tail != nullptr) {
    node->prev = tail;
    tail->next = node;
  } else {
    head = node;
  }
  tail = node;
  count++;
}

/* file content:
 count
 index1
 randIndex1 (or 0)
 dataSize1
 data1
 index2
 randIndex2 (or 0)
 dataSize2
 data2
 ...
 */

void List::Serialize(FILE *file) {
  // filling file with data
  fwrite(&count, sizeof(int), 1, file);

  ListNode *node = head;
  while (node) {
    std::uintptr_t nodeUId =
        reinterpret_cast<std::uintptr_t>(node);
    std::uintptr_t randUId =
        reinterpret_cast<std::uintptr_t>(node->rand);

    std::string dataStr(node->data);
    int dataSize = dataStr.size();

    fwrite(&nodeUId, sizeof(std::uintptr_t), 1, file);
    fwrite(&randUId, sizeof(std::uintptr_t), 1, file);

    // size of data field to deserialize it
    fwrite(&dataSize, sizeof(int), 1, file);
    fwrite(dataStr.c_str(), sizeof(char), dataSize, file);
    node = node->next;
  }
}

void List::Deserialize(FILE *file) {
  int size;
  std::uintptr_t index;
  std::uintptr_t randIndex;
  int dataSize;
  char dataBuffer[MAX_SIZE];

  ListNode *node;
  // std::vector<int, std::pair<ListNode *, int> > unsorted_map;
  std::map<int, ListNode *> indexToNode;

  // reading file and fill the map of linkedList data (index1: node1, randIndex1; index2: node2, randIndex2; ...)
  fread(&size, sizeof(int), 1, file);

  if (size < 0)
    return;

  for (int i = 0; i < size; ++i) {
    fread(&index, sizeof(std::uintptr_t), 1, file);
    fread(&randIndex, sizeof(std::uintptr_t), 1, file);
    fread(&dataSize, sizeof(int), 1, file);
    fread(dataBuffer, sizeof(char), dataSize, file);

    // create node with filled data field
    node = new ListNode(std::string(dataBuffer, dataSize), randIndex);
    this->pushNode(node);
    indexToNode[index] = node;
  }

  ListNode *curnode = head;
  while (curnode)
  {
    auto it = indexToNode.find(uint64_t(curnode->rand));
    if (it != indexToNode.end()) {
      curnode->rand = it->second;
    }
    else {
      curnode->rand = nullptr;
    }
    curnode = curnode->next;
  }
}

bool List::operator==(List &other) {
  {
    ListNode *fst = head;
    ListNode *snd = other.head;

    while (fst != nullptr && snd != nullptr) {
      if (*fst != *snd)
        return false;

      fst = fst->next;
      snd = snd->next;
    }

    return (fst == nullptr && snd == nullptr);
  }
}

bool List::operator!=(List &other) {
  return !operator==(other);
}

ListNode *List::front() {
  return head;
}

ListNode *List::back() {
  return tail;
}
