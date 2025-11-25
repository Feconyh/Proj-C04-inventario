#include <iostream>
#include <complex>
#include <list>
#include <string>
#include <locale>
#include <cmath>
#define MAXV 1000    // Máximo de vértices no grafo
using namespace std;
//Struct dos itens magicos
struct Itens {
    string name;
    string owner;
    string property;
    int id;
    int rarity;
};
typedef int KeyType;
typedef Itens ValueType;
// Estrutura armazenada na árvore
struct Datatype {
    KeyType key;    // Raridade do item
    ValueType value;
};
//No da árvore binária de busca
struct Node {
    Datatype data;
    Node *left;
    Node *right;
};
struct Aresta {
    int origem, destino, peso;
};
void insertBTree(Node * & curr, Datatype data) {
    if (curr == NULL) {
        curr = new Node;
        curr->data = data;
        curr->left = NULL;
        curr->right = NULL;
    }
    else if (data.key < curr->data.key)
        insertBTree(curr->left, data);
    else
        insertBTree(curr->right, data);
}
// Buscando pela chave(raridade)  do item
Node * searchBTree(Node * curr, int key) {
    if (curr == NULL) return NULL;
    else if (key == curr->data.key) return curr;
    else if (key < curr->data.key) return searchBTree(curr->left, key);
    else return searchBTree(curr->right, key);
}
// Encontra o menor no na subarvore da direita
Node * search_less_point_right(Node * & curr) {
    Node * temp = curr;
    if (curr->left == NULL) {
        curr = curr->right;
        return temp;
    }
    return search_less_point_right(curr->left);
}
bool removeBTree(Node * & curr, int key) {
    if (curr == NULL) return false;

    if (key == curr->data.key) {
        Node * temp = curr;

        if (curr->left == NULL)
            curr = curr->right;
        else if (curr->right == NULL)
            curr = curr->left;
        else {  
            // dois filhos / pega menor da direita
            temp = search_less_point_right(curr->right);
            curr->data = temp->data;
        }
        delete temp;
        return true;
    }
    if (key < curr->data.key)
        return removeBTree(curr->left, key);
    else
        return removeBTree(curr->right, key);
}
//Imprime apenas o nome do item
void print_value(ValueType value) {
    cout << value.name << endl;
}
void in_order(Node * curr) {
    if (curr != NULL) {
        in_order(curr->left);
        print_value(curr->data.value);
        in_order(curr->right);
    }
}
void in_level(Node * curr) {
    if (curr == NULL) return;

    list<Node*> fila;
    fila.push_back(curr);

    while (!fila.empty()) {
        curr = fila.front();
        fila.pop_front();

        print_value(curr->data.value);

        if (curr->left != NULL) fila.push_back(curr->left);
        if (curr->right != NULL) fila.push_back(curr->right);
    }
}
// Liberação da árvore
void destruct(Node *& curr) {
    if (curr != NULL) {
        destruct(curr->left);
        destruct(curr->right);
        delete curr;
    }
}
void grafo(list<Aresta> listas_adj[], int arestas)
{
    int origem, destino, similaridade;

    cout << "Insira origem destino similaridade:\n";

    for (int i = 0; i < arestas; i++) {
        cin >> origem >> destino >> similaridade;
        listas_adj[origem].push_back({origem, destino, similaridade});
        listas_adj[destino].push_back({destino, origem, similaridade});
    }
}
// Produto vetorial 2D
double cross_double(double ax, double ay,
                    double bx, double by,
                    double cx, double cy)
{
    return (bx - ax)*(cy - ay) - (by - ay)*(cx - ax);
}
// Verificando se o ponto esta dentro do polígono convexo
int ponto_interior_poligono_convexo(double polyX[], double polyY[],
                                    int n, double px, double py)
{
    if (n < 3) return 0;
    double s = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i+1) % n;
        double c = cross_double(polyX[i], polyY[i],
                                polyX[j], polyY[j],
                                px, py);
        if (i == 0) s = c;
        else {
            if ((s > 0 && c < -1e-9) || (s < 0 && c > 1e-9))
                return 0; //Se der 0, esta fora
        }
    }
    return 1; //dentro
}
//Ordenando a lista alfabeticamente
void list_alpha(Itens itens[], int &n_itens) {
    if (n_itens <= 0) {
        cout << "Nenhum item cadastrado." << endl;
        return;
    }
    int idx[1000];
    for (int i = 0; i < n_itens; ++i) idx[i] = i;

    //
    for (int i = 0; i < n_itens - 1; ++i) {
        int mini = i;
        for (int j = i+1; j < n_itens; ++j)
            if (itens[idx[j]].name < itens[idx[mini]].name)
                mini = j;
        swap(idx[i], idx[mini]);
    }
    //Saida dos itens
    for (int k = 0; k < n_itens; ++k) {
        int i = idx[k];
        cout << "Item " << i << endl;
        cout << "Nome: " << itens[i].name << endl;
        cout << "Dono: " << itens[i].owner << endl;
        cout << "Propriedade Magica: " << itens[i].property << endl;
        cout << "Raridade: " << itens[i].rarity << endl << endl;
    }
}
// Verificando existência pelo nome do item
void existe(Itens itens[], int &n_itens, string search_name)
{
    for (int i = 0; i < n_itens; ++i)
        if (itens[i].name == search_name) {
            cout << "Item encontrado!" << endl;
            return;
        }
    cout << "Item não encontrado!\n";
}
//Listando por raridade
void list_rarity(Itens itens[], int &n_itens)
{
    if (n_itens <= 0) {
        cout << "Nenhum item cadastrado." << endl;
        return;
    }
    int idx[1000];
    for (int i = 0; i < n_itens; ++i) idx[i] = i;

    //Ordenando por raridade
    for (int i = 0; i < n_itens - 1; ++i) {
        int best = i;
        for (int j = i+1; j < n_itens; ++j) {
            if (itens[idx[j]].rarity > itens[idx[best]].rarity)
                best = j;
            else if (itens[idx[j]].rarity == itens[idx[best]].rarity &&
                     itens[idx[j]].name < itens[idx[best]].name)
                best = j;
        }
        swap(idx[i], idx[best]);
    }
    //Saida dos items
    for (int k = 0; k < n_itens; ++k) {
        int i = idx[k];
        cout << "Item " << i << endl;
        cout << "Nome: " << itens[i].name << endl;
        cout << "Dono: " << itens[i].owner << endl;
        cout << "Propriedade Magica: " << itens[i].property << endl;
        cout << "Raridade: " << itens[i].rarity << endl << endl;
    }
}
//Contando quantos itens tem uma certa propriedade
void count_property(Itens itens[], int &n_itens)
{
    if (n_itens <= 0) {
        cout << "Nenhum item cadastrado." << endl;
        return;
    }
    cout << "Digite a propriedade magica: ";
    string p;
    cin.ignore();
    getline(cin, p);
    int cnt = 0;
    for (int i = 0; i < n_itens; ++i)
        if (itens[i].property == p)
            cnt++;
    cout << "Itens com \"" << p << "\": " << cnt << endl;
}
//Removendo itens com raridade menor que R
void remove_common(Itens itens[], int &n_itens)
{
    cout << "Digite raridade minima: ";
    int R;
    cin >> R;
    int j = 0;
    for (int i = 0; i < n_itens; ++i)
        if (itens[i].rarity >= R)
            itens[j++] = itens[i];
    cout << (n_itens - j) << " itens removidos.\n";
    n_itens = j;
}
// Lendo um polígono convexo e verificando se a posição do item está dentro dele
void readPolygon(Itens &temp_item, bool &should_insert)
{
    cout << "Deseja verificar se o item cabe na bolsa (poligono convexo)? (s/n): ";
    char c;
    cin >> c;
    if (c == 'n' || c == 'N') {
        should_insert = true;
        return;
    }
    int n;
    cout << "Quantos pontos tem o poligono? ";
    cin >> n;
    if (n < 3) {
        cout << "Poligono invalido.\n";
        should_insert = false;
        return;
    }
    double polyX[1000], polyY[1000];
    for (int i = 0; i < n; ++i) {
        cout << "Ponto " << i << " (x y): ";
        cin >> polyX[i] >> polyY[i];
    }
    double px, py;
    cout << "Digite posicao (x y) do item: ";
    cin >> px >> py;
    int inside = ponto_interior_poligono_convexo(polyX, polyY, n, px, py);
    should_insert = inside;
    if (inside) cout << "Item cabe dentro da bolsa.\n";
    else cout << "Item NAO cabe na bolsa.\n";
}
//Lendo os dados do item e chamando verificação do polígono
void insert(Itens itens[], int &n_itens, Node * root)
{
    cout << "Nome do item: ";
    cin.ignore();
    getline(cin, itens[n_itens].name);
    cout << "Dono: ";
    getline(cin, itens[n_itens].owner);
    cout << "Propriedade magica: ";
    getline(cin, itens[n_itens].property);
    cout << "ID: ";
    cin >> itens[n_itens].id;
    cout << "Raridade: ";
    cin >> itens[n_itens].rarity;
    bool inserir = true;
    Itens tmp = itens[n_itens];
    readPolygon(tmp, inserir);
    if (!inserir) {
        cout << "Insercao cancelada.\n";
        return;
    }
    n_itens++;
    insertBTree(root, { itens[n_itens-1].rarity, itens[n_itens-1] });
    cout << "Item cadastrado com sucesso.\n";
}
//Mostrando arestas do grafo
void define_related(list<Aresta> listas_adj[], int arestas)
{
    grafo(listas_adj, arestas);
    cout << "Lista de similaridades:\n";
    for (int i = 0; i < MAXV; i++) {
        if (!listas_adj[i].empty()) {
            cout << i << ": ";
            for (auto &ar : listas_adj[i])
                cout << "(" << ar.destino << ", " << ar.peso << ") ";
            cout << endl;
        }
    }
}
//Buscando itens relacionados por similaridade e dono diferente
void search_related(list<Aresta> listas_adj[],
                    Itens itens[],
                    int vertices,
                    int origem,
                    int similaridade_min,
                    string proibido)
{
    bool visitado[MAXV] = {false};
    for (auto &ar : listas_adj[origem]) {
        if (ar.peso >= similaridade_min) {
            int v = ar.destino;

            if (!visitado[v] && itens[v].owner != proibido) {
                visitado[v] = true;

                cout << "Item " << v << endl;
                cout << "Nome: " << itens[v].name << endl;
                cout << "Dono: " << itens[v].owner << endl;
                cout << "Propriedade Mágica: " << itens[v].property << endl;
                cout << "Raridade: " << itens[v].rarity << endl << endl;
            }
        }
    }
}
//Buscando item por nome
void search(Itens itens[], int &n_itens, string search_name)
{
    for (int i = 0; i < n_itens; i++)
        if (itens[i].name == search_name) {
            cout << "Item " << i << endl;
            cout << "Nome: " << itens[i].name << endl;
            cout << "Dono: " << itens[i].owner << endl;
            cout << "Propriedade Magica: " << itens[i].property << endl;
            cout << "Raridade: " << itens[i].rarity << endl << endl;
        }
}
//Menu principal
void menu()
{
    cout << "Menu:\n0 - Sair\n"
         << "1 - Inserir Item\n2 - Definir Relacoes\n"
         << "3 - Buscar Relacionados\n4 - Procurar Item\n"
         << "5 - Listar (Alfabetico)\n6 - Listar (Raridade)\n"
         << "7 - Contar propriedade\n8 - Deletar menos raros\n";
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Itens itens[1000];
    Node * root = NULL;
    list<Aresta> listas_adj[MAXV];

    int control, n_itens = 0;

    string search_name, dono_proibido;

    int arestas, origem, simmin, codigo;

    menu();

    while (cin >> control && control != 0)
    {
        switch (control)
        {
            case 1:
                insert(itens, n_itens, root);
                break;

            case 2:
                cout << "Quantas relacoes? ";
                cin >> arestas;
                define_related(listas_adj, arestas);
                break;

            case 3:
                cout << "Jogador proibido, item origem, similaridade min: ";
                cin >> dono_proibido >> codigo >> simmin;
                search_related(listas_adj, itens, n_itens, codigo, simmin, dono_proibido);
                break;

            case 4:
                cout << "Nome a procurar: ";
                cin.ignore();
                getline(cin, search_name);
                search(itens, n_itens, search_name);
                break;

            case 5:
                list_alpha(itens, n_itens);
                break;

            case 6:
                list_rarity(itens, n_itens);
                break;

            case 7:
                count_property(itens, n_itens);
                break;

            case 8:
                remove_common(itens, n_itens);
                break;

            default:
                cout << "Opcao invalida.\n";
        }

        menu();
    }

    return 0;
}
// João Vitor Souza Aldet - 660 - GES
//Lucas Naressi Guerra - 588 - GES
//Carlos Eduardo Carvalho Vilas Boas - 441 - GES
//Tales Henrique Moreira Carvalho - 518 - GES
//Felipe Lamy Rosa Rennó - 507 - GES




