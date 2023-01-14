#pragma once

#include <iostream>
#include <map>

struct ListNode {
  ListNode *prev;
  ListNode *next;
  ListNode *rand;// указатель на произвольный элемент данного списка либо NULL
  std::string data;

  explicit ListNode(std::string data, std::uint64_t randIndex) : prev(nullptr), next(nullptr), rand(reinterpret_cast<ListNode *>(randIndex)), data(std::move(data)){};

  explicit ListNode(std::string data) : prev(nullptr), next(nullptr), rand(nullptr), data(std::move(data)){};

  // for tests
  ListNode(const ListNode &) = delete;
  void operator=(const ListNode &) = delete;

  bool operator==(ListNode &other) {
    if (data != other.data) {
      std::cout << data << " " << other.data << std::endl;
      return false;
    }
    if (rand != nullptr && other.rand != nullptr)
      if (rand->data != other.rand->data)
        return false;
    return !((rand != nullptr || other.rand != nullptr) && (rand == nullptr || other.rand == nullptr));
  }

  bool operator!=(ListNode &other) {
    return !operator==(other);
  }
  // for tests
};

class List {
 public:
  List() : head(nullptr), tail(nullptr), count(0) {}
  List(const List &) = delete;
  void operator=(const List &) = delete;

  void Serialize(FILE *file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
  void Deserialize(FILE *file);// загрузка из файла (файл открыт с помощью fopen(path, "rb"))

  void pushNode(ListNode *node);

  // for tests
  void pushHead(const std::string &data);
  bool operator==(List &other);
  bool operator!=(List &other);

  ListNode *front();
  ListNode *back();
  // for tests

 private:
  ListNode *head;
  ListNode *tail;
  int count;
};
