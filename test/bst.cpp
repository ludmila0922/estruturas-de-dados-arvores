#include "../include/bst.hpp"

#include <gtest/gtest.h>

// ---------- Casos Gerais ----------

TEST(BSTTest, InserirEEncontrarElementos) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(18);

  EXPECT_TRUE(tree.contain(3));
  EXPECT_TRUE(tree.contain(18));
  EXPECT_FALSE(tree.contain(99));  // não existe
}

TEST(BSTTest, InsercaoDeDuplicatasIgnorada) {
  BST<int> tree;
  EXPECT_TRUE(tree.insert(10));
  EXPECT_TRUE(tree.insert(5));
  EXPECT_FALSE(tree.insert(5));  // ignorado
  EXPECT_TRUE(tree.contain(5));
}

// ---------- Casos de Borda ----------

TEST(BSTTest, InserirNaArvoreVazia) {
  BST<int> tree;
  EXPECT_TRUE(tree.insert(42));
  EXPECT_TRUE(tree.contain(42));
}

TEST(BSTTest, MinEmArvoreComUmUnicoNo) {
  BST<int> tree;
  tree.insert(10);
  EXPECT_TRUE(tree.contain(10));
}

TEST(BSTTest, MaxEmArvoreComUmUnicoNo) {
  BST<int> tree;
  tree.insert(10);
  EXPECT_TRUE(tree.contain(10));
}

TEST(BSTTest, RemoverRaizSemFilhos) {
  BST<int> tree;
  tree.insert(10);
  EXPECT_TRUE(tree.remove(10));
  EXPECT_FALSE(tree.contain(10));
}

TEST(BSTTest, RemoverRaizComUmFilho) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  EXPECT_TRUE(tree.remove(10));
  EXPECT_TRUE(tree.contain(5));
  EXPECT_FALSE(tree.contain(10));
}

TEST(BSTTest, RemoverRaizComDoisFilhos) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  EXPECT_TRUE(tree.remove(10));
  EXPECT_TRUE(tree.contain(5));
  EXPECT_TRUE(tree.contain(15));
  EXPECT_FALSE(tree.contain(10));
}

TEST(BSTTest, RemoverFolha) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(3);  // folha
  EXPECT_TRUE(tree.remove(3));
  EXPECT_FALSE(tree.contain(3));
}

TEST(BSTTest, RemoverNoComDoisFilhos) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);  // 5 tem dois filhos
  EXPECT_TRUE(tree.remove(5));
  EXPECT_FALSE(tree.contain(5));
  EXPECT_TRUE(tree.contain(3));
  EXPECT_TRUE(tree.contain(7));
}

TEST(BSTTest, RemoverElementoInexistente) {
  BST<int> tree;
  tree.insert(10);
  EXPECT_FALSE(tree.remove(999));  // não existe
  EXPECT_TRUE(tree.contain(10));
}

TEST(BSTTest, InserirNumerosNegativos) {
  BST<int> tree;
  tree.insert(0);
  tree.insert(-10);
  tree.insert(-5);
  EXPECT_TRUE(tree.contain(-10));
  EXPECT_TRUE(tree.contain(-5));
}

TEST(BSTTest, InserirValoresIguaisDeTiposCompatíveis) {
  BST<double> tree;
  EXPECT_TRUE(tree.insert(10.0));
  EXPECT_TRUE(tree.insert(5.0));
  EXPECT_FALSE(tree.insert(10.0));  // já existe
  EXPECT_TRUE(tree.contain(10.0));
  EXPECT_TRUE(tree.contain(5.0));
}

// ---------- Teste para operador < apenas ----------

struct OnlyLess {
  int val;
  explicit OnlyLess(int v) : val(v) {}

  bool operator<(const OnlyLess& other) const { return val < other.val; }

  // NÃO define operator== nem operator>
};

TEST(BSTTest, FuncionaApenasComOperadorMenor) {
  BST<OnlyLess> tree;
  EXPECT_TRUE(tree.insert(OnlyLess(10)));
  EXPECT_TRUE(tree.insert(OnlyLess(5)));
  EXPECT_TRUE(tree.insert(OnlyLess(15)));
  EXPECT_TRUE(tree.contain(OnlyLess(5)));
  EXPECT_TRUE(tree.remove(OnlyLess(10)));
  EXPECT_FALSE(tree.contain(OnlyLess(10)));
}

TEST(BSTTest, InOrderTraversal) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);

  auto result = tree.in_order();
  std::vector<int> expected = {3, 5, 7, 10, 15};

  EXPECT_EQ(result, expected);
}

TEST(BSTTest, PreOrderTraversal) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);

  auto result = tree.pre_order();
  std::vector<int> expected = {10, 5, 3, 7, 15};

  EXPECT_EQ(result, expected);
}

TEST(BSTTest, PostOrderTraversal) {
  BST<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);

  auto result = tree.post_order();
  std::vector<int> expected = {3, 7, 5, 15, 10};

  EXPECT_EQ(result, expected);
}