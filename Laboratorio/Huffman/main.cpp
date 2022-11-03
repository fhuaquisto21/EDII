#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

class Code {
  public:
    char character;
    int count;

    Code(char ch, int cn): character(ch), count(cn) {}
    Code() {}

    bool operator <(Code cd2) {
      if (this->count < cd2.count) {
        return true;
      }
      return false;
    }
    bool operator >(Code cd2) {
      if (this->count > cd2.count) {
        return true;
      }
      return false;
    }

    bool operator ==(Code cd2) {
      if (this->character == cd2.character) {
        return true;
      }
      return false;
    }

    void operator ++() {
      this->count++;
    }

    void operator +=(Code cd2) {
      this->count += cd2.count;
    }

    Code operator =(Code vl) {
      this->character = vl.character;
      this->count = vl.count;
      return *this;
    }
};

std::ostream& operator<<(std::ostream& os, const Code& cd1)
{
  //os << cd1.character << ":" << cd1.count;
  os << cd1.character;
  return os;
}

Code operator +(Code c1, Code c2) {
  return Code('0', c1.count + c2.count);
}

template <typename T>
class Node {
  public:
    T value;
    Node<T> * next;
    Node<T> * left;
    Node<T> * right;
    Node(T vl) {
      this->value = vl;
      this->next = nullptr;
      this->left = nullptr;
      this->right = nullptr;
    }

    void print_inorden() {
      std::cout << this->value << " -> ";
      if (this->left != nullptr) {
        std::cout << this->left->value << " -> ";
      }
      if (this->right != nullptr) {
        std::cout << this->right->value << " -> ";
      }
      std::cout << std::endl;
    }
};

template <typename T>
class List {
  public:
    Node<T> * head;
    int size;

    List(T vl) {
      this->head = new Node<T>(vl);
      this->size = 0;
    }
    List() {
      this->head = nullptr;
      this->size = 0;
    }

    void push_next(T vl, Node<T> *&current) {
      if (current == nullptr) {
        current = new Node<T>(vl);
        this->size++;
        return;
      }
      if (current->value == vl) {
        current->value += vl;
        return;
      }
      this->push_next(vl, current->next);
    }

    void push_next(T vl) {
      this->push_next(vl, this->head);
    }

    void push(Node<T> * code, Node<T> *&current) {
      if (current == nullptr) {
        current = code;
        this->size++;
        return;
      }
      if (current->next == nullptr) {
        return this->push(code, current->next);
      }
      if (current->value > code->value && current == this->head) {
        code->next = current;
        this->head = code;
        this->size++;
        return;
      }
      if (current->next->value > code->value) {
        code->next = current->next;
        current->next = code;
        this->size++;
        return;
      }
      this->push(code, current->next);
    }

    void push(Node<T> * code) {
      this->push(code, this->head);
    }

    void order() {
      Node<T> * current = this->head;
      Node<T> * next = current->next;
      while (current->next != nullptr) {
        while (next != nullptr) {
          if (current->value > next->value) {
            T aux = next->value;
            next->value = current->value;
            current->value = aux;
          }
          next = next->next;
        }
        current = current->next;
        next = current->next;
      }
    }

    Node<T> delete_front() {
      if (this->head == nullptr) {
        return Node<T>(Code(' ', 0));
      }
      Node<T> tmp = *this->head;
      Node<T> * aux = this->head->next;
      delete this->head;
      this->head = aux;
      this->size--;
      tmp.next = nullptr;
      return tmp;
    }

    void print() {
      Node<T> *aux = this->head;
      while (aux != nullptr) {
        std::cout << aux->value << " ";
        aux = aux->next;
      }
      std::cout << std::endl;
    }

    void print_inorden(Node<T> * current) {
      if (current == nullptr) {
        return;
      }
      std::cout << current->value << " -> ";
      this->print_inorden(current->left);
      this->print_inorden(current->right);
    }

    void print_inorden() {
      this->print_inorden(this->head);
      std::cout << std::endl;
    }

    void find_huffman(Code c, std::string &code, Node<T> * current, bool &terminate) {
      if (current == nullptr)
        return;
      if (current->value == c)
        terminate = true;
      if (!terminate)
        code += '0';
      this->find_huffman(c, code, current->left, terminate);
      if (!terminate) {
        code.pop_back();
        code += '1';
      }
      this->find_huffman(c, code, current->right, terminate);
      if (!terminate)
        code.pop_back();
    }

    void find_huffman(char c, std::string &code) {
      bool terminate = false;
      this->find_huffman(Code(c, 0), code, this->head, terminate);
    }

    List<T> * operator =(const List<T> *list) {
      Node<T> * current = list->head;
      while (current != nullptr) {
        Node<T> * auxNode = new Node<T>(current->value);
        this->push(auxNode);
        current = current->next;
      }
      return this;
    }
};

void read_file(std::string file, std::string &text) {
  std::ifstream archivo(file);
  for (std::string line; std::getline(archivo, line);) {
    text += line;
    text += '\n';
  }
  archivo.close();
}

template <typename T>
List<T> * huffman(List<T> * list) {
  if (list->size == 1) {
    return list;
  }
  Node<T> a1 = list->delete_front();
  Node<T> a2 = list->delete_front();
  Node<T> *newNode = new Node<T>(a1.value + a2.value);
  newNode->left = new Node<T>(a1);
  newNode->right = new Node<T>(a2);
  list->push(newNode);
  return huffman(list);
}


template <typename T>
void read_huffman(List<T> * list, std::vector<bool> dirs) {
  Node<T> * tmp = list->head;
  for (int i = 0; i < dirs.size(); ++i) {
    if (dirs[i]) {
      if (tmp->right != nullptr) {
        tmp = tmp->right;
        continue;
      }
    } else {
      if (tmp->left != nullptr) {
        tmp = tmp->left;
        continue;
      }
    }
    std::cout << tmp->value;
    tmp = list->head;
    i--;
  }
  std::cout << tmp->value <<std::endl;
}

int main()
{
  /*
  List<Code> *list = new List<Code>;
  std::string text = "";
  read_file("./texto.txt", text);
  for (auto c : text) {
    if (c != '\n') {
      list->push_next(Code(c, 1));
    }
  }
  list->order();
  list = huffman(list);
  std::vector<bool> w1 = { 0, 0, 0 };
  std::vector<bool> w2 = { 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1 };
  std::vector<bool> w3 = { 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1 };
  read_huffman(list, w1);
  read_huffman(list, w2);
  read_huffman(list, w3);

  std::string code = "";
  list->find_huffman('d', code);
  std::cout << std::endl;
  std::cout << code << std::endl;
  std::cout << std::endl;
  */

  List<Code> * list2 = new List<Code>;
  std::string encode = "";
  read_file("./encode.txt", encode);
  for (auto c : encode) {
    if (c != '\n') {
      list2->push_next(Code(c, 1));
    }
  }
  list2->order();
  list2 = huffman(list2);
  std::string code = "";
  for (auto c: encode) {
    list2->find_huffman(c, code);
  }
  std::cout << "Comprimido:" << std::endl;
  std::cout << code << std::endl;
  std::vector<bool> codeAux;
  for (auto c: code) {
    if (c == '1') {
      codeAux.push_back(1);
    } else {
      codeAux.push_back(0);
    }
  }
  std::cout << std::endl;
  std::cout << "Descomprimido:" << std::endl;
  read_huffman(list2, codeAux);
}
