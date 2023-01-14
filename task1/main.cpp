#include <iostream>

void printBinary(signed int dec)
{
  for (int i = 0; i < sizeof(signed int) * 8; i++)
  {
    std::cout << ((dec >> i) & 1);
  }
}

int main()
{
  printBinary(10);
  std::cout << "\n\n";
  printBinary(-10);
  std::cout << "\n\n";

  return 0;
}