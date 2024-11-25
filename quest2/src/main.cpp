#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Node {
  int value;
  Node *left;
  Node *right;
  Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Função para calcular o nível máximo (altura) da árvore
int calculateHeight(Node *root) {
  if (!root)
    return 0; // Árvore vazia
  return 1 +
         std::max(calculateHeight(root->left), calculateHeight(root->right));
}

// Função para inserir um nó na árvore binária
Node *insertNode(Node *root, int value) {
  if (!root)
    return new Node(value);
  if (value < root->value)
    root->left = insertNode(root->left, value);
  else
    root->right = insertNode(root->right, value);
  return root;
}

// Função para encontrar o caminho mais longo (raiz até a folha mais distante)
void findLongestPath(Node *root, std::vector<int> &path,
                     std::vector<int> &longestPath) {
  if (!root)
    return;
  path.push_back(root->value);
  if (!root->left && !root->right) { // É uma folha
    if (path.size() > longestPath.size())
      longestPath = path;
  }
  findLongestPath(root->left, path, longestPath);
  findLongestPath(root->right, path, longestPath);
  path.pop_back();
}

// Função para imprimir a árvore
void printTree(Node *root, int level = 0) {
  if (!root)
    return;
  printTree(root->right, level + 1);
  for (int i = 0; i < level; ++i)
    std::cout << "   ";
  std::cout << root->value << "\n";
  printTree(root->left, level + 1);
}
void analyzeGrowth(const std::vector<int> &balancedInsertions,
                   const std::vector<int> &unbalancedInsertions) {
  Node *balancedRoot = nullptr;
  Node *unbalancedRoot = nullptr;
  std::vector<int> balancedHeights, unbalancedHeights;

  std::cout << "\nAnálise de Crescimento:\n";
  std::cout << std::setw(10) << "Inserção" << std::setw(20)
            << "Altura (Equilibrada)" << std::setw(20)
            << "Altura (Desbalanceada)" << std::setw(20) << "Diferença (%)\n";

  for (size_t i = 0; i < balancedInsertions.size(); ++i) {
    // Inserir elementos nas árvores
    balancedRoot = insertNode(balancedRoot, balancedInsertions[i]);
    unbalancedRoot = insertNode(unbalancedRoot, unbalancedInsertions[i]);

    // Calcular alturas
    int balancedHeight = calculateHeight(balancedRoot);
    int unbalancedHeight = calculateHeight(unbalancedRoot);

    // Salvar alturas para análise
    balancedHeights.push_back(balancedHeight);
    unbalancedHeights.push_back(unbalancedHeight);

    // Calcular diferença percentual
    double percentageDifference =
        ((double)(unbalancedHeight - balancedHeight) / balancedHeight) * 100.0;

    // Imprimir resultados
    std::cout << std::setw(10) << (i + 1) << std::setw(20) << balancedHeight
              << std::setw(20) << unbalancedHeight << std::setw(20)
              << std::fixed << std::setprecision(2) << percentageDifference
              << "%\n";
  }

  std::cout << "\nResumo da análise:\n";
  std::cout << "- Altura final da árvore equilibrada: "
            << balancedHeights.back() << "\n";
  std::cout << "- Altura final da árvore desbalanceada: "
            << unbalancedHeights.back() << "\n";
  std::cout << "- Diferença percentual final: " << std::fixed
            << std::setprecision(2)
            << ((double)(unbalancedHeights.back() - balancedHeights.back()) /
                balancedHeights.back()) *
                   100.0
            << "%\n";

  std::cout << "\nObserve que a árvore desbalanceada cresce mais rapidamente "
               "devido à ausência de balanceamento automático.\n";
  std::cout << "Este comportamento reflete o aumento do custo de operações em "
               "árvores desbalanceadas.\n";
}
bool searchNode(Node *root, int value) {
  if (!root)
    return false; // Árvore vazia ou valor não encontrado
  if (root->value == value)
    return true; // Valor encontrado
  if (value < root->value)
    return searchNode(root->left, value); // Busca no lado esquerdo
  return searchNode(root->right, value);  // Busca no lado direito
}
double measureSearchPerformance(Node *root, const std::vector<int> &elements) {
  auto start = std::chrono::high_resolution_clock::now();

  for (int element : elements) {
    searchNode(root, element);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

  // Retorna o tempo total como um número double (em nanosegundos)
  return static_cast<double>(elapsed.count());
}

int main() {
  Node *root = nullptr;
  std::vector<int> balancedInsertions = {50, 25, 75, 15, 35, 65, 85, 10, 20, 30,
                                         40, 60, 70, 80, 90, 5,  12, 18, 28, 38,
                                         45, 55, 68, 72, 78, 88, 92, 95};

  std::vector<int> unbalancedInsertions = {
      1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
      15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

  std::cout << "Construindo árvore equilibrada:\n";
  for (int value : balancedInsertions) {
    root = insertNode(root, value);
    std::cout << "Árvore após inserir " << value << ":\n";
    printTree(root);
    std::cout << "Altura atual: " << calculateHeight(root) << "\n";
  }

  Node *unbalancedRoot = nullptr;
  std::cout << "\nConstruindo árvore desbalanceada:\n";
  for (int value : unbalancedInsertions) {
    unbalancedRoot = insertNode(unbalancedRoot, value);
    std::cout << "Árvore após inserir " << value << ":\n";
    printTree(unbalancedRoot);
    std::cout << "Altura atual: " << calculateHeight(unbalancedRoot) << "\n";
  }

  std::vector<int> path, longestPath;
  findLongestPath(root, path, longestPath);

  std::cout << "\nCaminho mais longo da árvore equilibrada: ";
  for (int value : longestPath)
    std::cout << value << " ";
  std::cout << "\nComprimento: " << longestPath.size() << "\n";

  path.clear();
  longestPath.clear();
  findLongestPath(unbalancedRoot, path, longestPath);

  std::cout << "\nCaminho mais longo da árvore desbalanceada: ";
  for (int value : longestPath)
    std::cout << value << " ";
  std::cout << "\nComprimento: " << longestPath.size() << "\n";

  analyzeGrowth(balancedInsertions, unbalancedInsertions);
  double unbalancedTimeResult =
      measureSearchPerformance(unbalancedRoot, unbalancedInsertions);
  double balancedTimeResult =
      measureSearchPerformance(root, balancedInsertions);

  // Calcula a diferença percentual
  double percentageDifference =
      ((unbalancedTimeResult - balancedTimeResult) / balancedTimeResult) *
      100.0;

  // Exibe os resultados
  std::cout << "Tempo total de busca (árvore equilibrada): "
            << balancedTimeResult << " nanosegundos\n";
  std::cout << "Tempo total de busca (árvore desbalanceada): "
            << unbalancedTimeResult << " nanosegundos\n";
  std::cout << "Diferença percentual: " << percentageDifference << "%\n";

  return 0;
}
