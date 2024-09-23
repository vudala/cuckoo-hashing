#include <bits/stdc++.h>
using namespace std;

#define M           11
#define NULO        -1
#define HASH1(key)  key % M
#define HASH2(key)  (int) M * (key * 0.9f - (int)(key * 0.9f))

vector<int> nest_1 (M, NULO);
vector<int> nest_2 (M, NULO);

// Procura pelo elemento
pair<int, int> search(int key)
{
  int h1 = HASH1(key);
  
  // Achou no primeiro nest
  if (nest_1[h1] == key)
    return {0, h1};

  int h2 = HASH2(key);

  // Achou no segundo nest
  if (nest_2[h2] == key)
    return {1, h2};

  // Não achou
  return {NULO, NULO};
}

// Verifica se o elemento já está inserido
bool exist(int key)
{
  auto el = search(key);
  return el.first != NULO;
}

// Insere um elemento
void include(int key)
{
  if (exist(key)) return;

  int h1 = HASH1(key);
  int h2 = HASH2(key);
  
  if (nest_1[h1] < 0) {
    nest_1[h1] = key;
  }
  else {
    int el = nest_1[h1];
    nest_2[HASH2(el)] = el;
    nest_1[h1] = key;
  }
}

// Remove um elemento
void remove(int key)
{
  if (! exist(key)) return;
  auto el = search(key);

  // Decide se remove do primeiro ou segundo nest
  if (el.first == 0)
    nest_1[HASH1(key)] = NULO;
  else
    nest_2[HASH2(key)] = NULO;
}

int main()
{
  char op;
  int key;

  // Realiza as operações
  while (cin >> op) {
    cin >> key;
    if (op == 'i')
      include(key);
    else if (op == 'r')
      remove(key);
  }

  // Colets os elementos para saída
  vector<int> elements;
  for (int x : nest_1)
    if (x != NULO) elements.push_back(x);
  for (int x : nest_2)
    if (x != NULO) elements.push_back(x);

  // Ordena os elementos para saída
  sort(elements.begin(), elements.end());

  // Imprime
  for (int x : elements) {
    auto el = search(x);
    cout << x << ',';
    cout << (el.first == 0 ? "T1," : "T2,") << el.second << endl;
  }
}
