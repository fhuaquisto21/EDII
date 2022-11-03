#include <iostream>
#include <vector>
#include <algorithm>

char nodes[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

void kruskal(int a[8][8], int size) {
  std::vector<char> auxNodes;
  std::vector<std::vector<int>> aristas;
  int min = 100000;
  for (int i = 0; i < size; i++) {
    for (int y = 0; y < size; y++) {
      if (y > i) {
        if (a[i][y] < min && a[i][y] > 0) {
          min = a[i][y];
          auxNodes.push_back(nodes[i]);
          aristas.push_back({ i, y });
        }
      }
    }
  }
  int next = min + 1;
  std::cout << next << std::endl;
  bool reset = false;
  while (auxNodes.size() < 8) {
    for (int i = 0; i < size; i++) {
      for (int y = 0; y < size; y++) {
        if (y > i) {
          std::cout << a[i][y] << std::endl;
          if (a[i][y] == next && std::find(auxNodes.begin(), auxNodes.end(), nodes[i]) != auxNodes.end()) {
            std::cout << next << std::endl;
            min = next;
            next = min + 1;
            auxNodes.push_back(nodes[i]);
            aristas.push_back({ i, y });
            reset = true;
            break;
          }
        }
      }
      if (reset) {
        reset = false;
        break;
      }
    }
    break;
  }
  for (auto a: auxNodes) {
    std::cout << a << std::endl;
  }
}

int main() {
  int aux[8][8] = {
    { 0, 1, 13, 6, 0, 5, 0, 0 },
    { 0, 0, 5, 14,3, 0, 0, 0 },
    { 0, 0, 0, 0, 4, 0, 0, 15 },
    { 0, 0, 0, 0, 0, 7, 9, 0},
    { 0, 0, 0, 0, 0, 0, 11, 8},
    { 0, 0, 0, 0, 0, 0, 2, 16},
    { 0, 0, 0, 0, 0, 0, 0, 10},
    { 0, 0, 0, 0, 0, 0, 0, 0}
  };
  kruskal(aux, 8);

  return 0;
}
