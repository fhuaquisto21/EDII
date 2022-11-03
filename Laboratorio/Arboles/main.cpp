#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node {
  public:
    char letra;
    int cantidad;
    Node * next;
    Node * left;
    Node * right;

    Node(char _letra) {
      this->letra = _letra;
      this->cantidad = 1;
      this->next = nullptr;
      this->left = nullptr;
      this->right = nullptr;
    }

    Node(char _letra, int _cantidad) {
      this->letra = _letra;
      this->cantidad = _cantidad;
      this->next = nullptr;
      this->left = nullptr;
      this->right = nullptr;
    }

    ~Node() {}
};

class Tree {
  public:
    Node * head;

    Tree() {
      this->head = nullptr;
    }

    ~Tree() {}

    void add_node(char _letra, int _cantidad) {
      if (this->head != nullptr) {
        this->head = new Node(_letra, _cantidad);
      }
      this->add_node(_letra, _cantidad, this->head);
    }

    void add_node(char _letra, int _cantidad, Node * _current) {
      if (_cantidad > _current->cantidad) {
        if (_current->right != nullptr) {
          return this->add_node(_letra, _cantidad, _current->right);
        }
        _current->right = new Node(_letra, _cantidad);
        return;
      } else {
        if (_current->left != nullptr) {
          return this->add_node(_letra, _cantidad, _current->left);
        }
        _current->left = new Node(_letra, _cantidad);
        return;
      }
    }
};

class List {
  public:
    Node * head;

    List() {
      this->head = nullptr;
    }

    List(char _letra) {
      this->head = new Node(_letra);
    }

    ~List() {}

    void add_node(char _letra) {
      if (this->head == nullptr) {
        this->head = new Node(_letra);
        return;
      }
      Node * aux = this->head;
      while (aux->next != nullptr) {
        if (aux->letra == _letra) {
          aux->cantidad++;
          return;
        }
        aux = aux->next;
      }
      if (aux->letra == _letra) {
        aux->cantidad++;
        return;
      }
      aux->next = new Node(_letra);
    }

    void add_node(Node * _new_node) {
      if (this->head == nullptr) {
        this->head = _new_node;
      }
      Node *aux = this->head;
      while (aux->next != nullptr) {
        if (aux->next->cantidad > _new_node->cantidad) {
          Node *temp = aux->next;
          aux->next = _new_node;
          _new_node->next = temp;
          return;
        }
        aux = aux->next;
      }
      if (aux->cantidad < _new_node->cantidad) {
        Node *temp = aux->next;
        aux->next = _new_node;
        _new_node->next = temp;
        return;
      }
      aux->next = _new_node;
    }

    Node delete_front() {
      if (this->head == nullptr) {
        return 0;
      }
      Node temp = *this->head;
      Node *aux = this->head->next;
      delete this->head;
      this->head = aux;
      temp.next = nullptr;
      return temp;
    }

    void print() {
      if (this->head == nullptr) {
        std::cout << "Lista vacía" << std::endl;
      }
      Node * aux = this->head;
      while(aux->next != nullptr) {
        std::cout << aux->letra << ":" << aux->cantidad << " -> ";
        aux = aux->next;
      }
      std::cout << aux->letra << ":" << aux->cantidad << std::endl;
    }

    void print_inorden() {
      this->print_inorden(this->head);
    }
    
    void print_inorden(Node *_current) {
      if (_current == nullptr) {
        return;
      }
      std::cout << _current->letra << ":" << _current->cantidad << " -> ";
      print_inorden(_current->left);
      print_inorden(_current->right);
    }

    void order() {
      Node * current = this->head;
      Node * next = current->next;
      while (current->next != nullptr) {
        while (next!= nullptr) {
          if (current->cantidad > next->cantidad) {
            int auxI = next->cantidad;
            char auxC = next->letra;
            next->cantidad = current->cantidad;
            next->letra = current->letra;
            current->letra = auxC;
            current->cantidad = auxI;
          }
          next = next->next;
        }
        current = current->next;
        next = current->next;
      }
    }

    List * operator =(const List * _list) {
      List *newList = new List;
      Node *current = _list->head;
      while (current != nullptr) {
        newList->add_node(current);
        current = current->next;
      }
      return newList;
    }
};

List * create_tree(List *_list) {
  if (_list->head->cantidad >= 90) {
    return _list;
  }
  List *list2 = _list;
  list2->print();
  Node aux1 = list2->delete_front();
  Node aux2 = list2->delete_front();
  Node *newNode = new Node(' ', aux1.cantidad + aux2.cantidad);
  newNode->left = &aux1;
  newNode->right = &aux2;
  list2->add_node(newNode);
  return create_tree(list2);
}

int main()
{
  List *list = new List;
  std::string text = "";
  std::ifstream archivo("./texto.txt");
  while (!archivo.eof()) {
    archivo >> text;
  }
  archivo.close();

  for (auto l: text) {
    list->add_node(l);
  }

  list->print();
  list->order();
  list->print();
  List *list2 = create_tree(list);

  /*
	ArbolBinario arbol = NULL;
	cout << "\n ...EJEMPLO DE ARBOL BINARIO... \n";
	insertar(arbol, 4);
	insertar(arbol, 8);
	insertar(arbol, 2);
	insertar(arbol, 9);
	insertar(arbol, 3);
	insertar(arbol, 6);
	insertar(arbol, 1);
	insertar(arbol, 7);
	insertar(arbol, 5);
	cout << "\nRecorridos del ArbolBinario\n";
	cout << "\nEn orden : "; enOrden(arbol);
	cout << "\nPre Orden : "; preOrden(arbol);
	cout << "\nPost Orden : "; postOrden(arbol);
	cout << endl << endl;
	return 0;
  */
}
