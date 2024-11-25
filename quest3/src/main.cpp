#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Estrutura para armazenar as palavras associadas a um prefixo
struct WordNode {
  string word;
  string meaning;

  WordNode(const string &w, const string &m) : word(w), meaning(m) {}
};

// Nó da árvore de prefixos AVL
struct PrefixNode {
  string prefix;
  vector<WordNode> words;
  PrefixNode *left, *right;
  int height;

  PrefixNode(const string &p)
      : prefix(p), left(nullptr), right(nullptr), height(1) {}
};

// Função para obter a altura de um nó
int getHeight(PrefixNode *node) { return node ? node->height : 0; }

// Função para obter o fator de balanceamento de um nó
int getBalance(PrefixNode *node) {
  return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Rotação à esquerda
PrefixNode *rotateLeft(PrefixNode *x) {
  PrefixNode *y = x->right;
  x->right = y->left;
  y->left = x;

  // Atualiza as alturas
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}

// Rotação à direita
PrefixNode *rotateRight(PrefixNode *y) {
  PrefixNode *x = y->left;
  y->left = x->right;
  x->right = y;

  // Atualiza as alturas
  y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

  return x;
}

// Função para balancear a árvore após inserção
PrefixNode *balance(PrefixNode *node) {
  int balanceFactor = getBalance(node);

  // Caso 1: Desbalanceamento à direita
  if (balanceFactor < -1) {
    if (getBalance(node->right) > 0)
      node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  // Caso 2: Desbalanceamento à esquerda
  if (balanceFactor > 1) {
    if (getBalance(node->left) < 0)
      node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  return node;
}

// Insere um prefixo na árvore AVL
PrefixNode *insertPrefix(PrefixNode *root, const string &prefix,
                         const string &word, const string &meaning) {
  if (!root) {
    root = new PrefixNode(prefix);
    root->words.push_back(WordNode(word, meaning));
    return root;
  }

  if (prefix < root->prefix) {
    root->left = insertPrefix(root->left, prefix, word, meaning);
  } else if (prefix > root->prefix) {
    root->right = insertPrefix(root->right, prefix, word, meaning);
  } else {
    root->words.push_back(WordNode(word, meaning));
  }

  // Atualiza a altura do nó
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));

  // Balanceia o nó
  return balance(root);
}

// Função para buscar palavras por prefixo
void searchPrefix(PrefixNode *root, const string &prefix,
                  vector<string> &results) {
  if (!root) {
    return;
  }

  if (prefix.find(root->prefix) == 0 || root->prefix.find(prefix) == 0) {
    for (const auto &wordNode : root->words) {
      if (wordNode.word.find(prefix) == 0) {
        results.push_back(wordNode.word);
      }
    }
  }

  searchPrefix(root->left, prefix, results);
  searchPrefix(root->right, prefix, results);
}

// Mapa para armazenar árvores de prefixos para cada letra do alfabeto
unordered_map<char, PrefixNode *> alphabetTrees;

void insertWord(const string &word, const string &meaning) {
  char firstLetter = word[0];
  string prefix = word.substr(0, 1);

  if (alphabetTrees.find(firstLetter) == alphabetTrees.end()) {
    alphabetTrees[firstLetter] = nullptr;
  }

  alphabetTrees[firstLetter] =
      insertPrefix(alphabetTrees[firstLetter], prefix, word, meaning);
}

void displayTree(PrefixNode *root) {
  if (!root)
    return;

  cout << "Prefixo: " << root->prefix << " | Palavras: ";
  for (const auto &wordNode : root->words) {
    cout << wordNode.word << "(" << wordNode.meaning << ") ";
  }
  cout << endl;

  displayTree(root->left);
  displayTree(root->right);
}

vector<string> findWordsByPrefix(const string &prefix) {
  vector<string> results;
  if (prefix.empty()) {
    cout << "Prefixo vazio fornecido!" << endl;
    return results;
  }

  // Obtém a letra inicial do prefixo
  char firstLetter = prefix[0];

  // Verifica se existe uma árvore para a letra inicial
  if (alphabetTrees.find(firstLetter) != alphabetTrees.end()) {
    cout << "Buscando palavras com o prefixo '" << prefix << "'..." << endl;
    searchPrefix(alphabetTrees[firstLetter], prefix, results);
  } else {
    cout << "Nenhuma árvore encontrada para a letra '" << firstLetter << "'!"
         << endl;
  }

  return results;
}
// Função para testar o tempo de inserção e busca
void runTests() {
  auto start = chrono::high_resolution_clock::now();

  // Inserir um grande número de palavras (exemplo com 10.000 palavras)
  for (int i = 0; i < 10000; i++) {
    string word = "word" + to_string(i);
    insertWord(word, "Definition of " + word);
  }

  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> duration = end - start;
  cout << "Tempo de inserção: " << duration.count() << " segundos" << endl;

  start = chrono::high_resolution_clock::now();

  // Realizar busca com prefixo
  vector<string> results = findWordsByPrefix("word");
  end = chrono::high_resolution_clock::now();
  duration = end - start;
  cout << "Quantidade de palavras com prefixo word: " << results.size() << endl;
  cout << "Tempo de busca por prefixo: " << duration.count() << " segundos"
       << endl;
}
int main() {
  insertWord("apple", "A fruit");
  insertWord("apricot", "A fruit");
  insertWord("banana", "A tropical fruit");
  insertWord("berry", "Small fruit");

  for (const auto &entry : alphabetTrees) {
    cout << "Árvore para a letra " << entry.first << ":\n";
    displayTree(entry.second);
  }

  // Exemplos de busca por prefixos
  vector<string> results = findWordsByPrefix("app");
  cout << "Palavras encontradas para o prefixo 'app':\n";
  for (const string &word : results) {
    cout << word << endl;
  }

  results = findWordsByPrefix("ba");
  cout << "Palavras encontradas para o prefixo 'ba':\n";
  for (const string &word : results) {
    cout << word << endl;
  }

  runTests();

  return 0;
}
