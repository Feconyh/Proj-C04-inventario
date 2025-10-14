#include <iostream>
#include <list>
#include <string>
#include <locale>

#define MAXV 1000

using namespace std;

struct Itens{
	string name;
	string owner;
	string property;
    int id;
	int rarity;
};

struct Aresta{
	int origem, destino, peso;
};

void grafo(list<Aresta> listas_adj[], int arestas)
{
	int origem, destino, similaridade;
	cout << "Insira o código de origem da similaridade, depois o de destino e por último a similaridade.\n";
	for (int i = 0; i < arestas; i++) {
		cin >> origem >> destino >> similaridade;
		listas_adj[origem].push_back({origem, destino, similaridade});
		listas_adj[destino].push_back({destino, origem, similaridade});
	}
}

void insert(Itens itens[], int &n_itens) // & para usar a var "n_itens" como referencia
{
	cout << "Nome do item: \n";
	cin.ignore();
	getline(cin, itens[n_itens].name); // input nome do item

	cout << "Quem e o dono do item: \n";
	getline(cin, itens[n_itens].owner); // input dono do item

	cout << "Qual a propriedade magica: \n";
	getline(cin, itens[n_itens].property); // input propriedade magica

    cout << "Qual o numero de identificacao: \n";
	cin >> itens[n_itens].id; // input numero de identificação

	cout << "Qual a raridade: \n";
	cin >> itens[n_itens].rarity; // input raridade (0 a 100)

	n_itens++; // incremento
}
void define_related(list<Aresta> listas_adj[], int arestas)
{
	grafo(listas_adj, arestas);

	list<Aresta>::iterator it;
	cout << "Lista de similaridades:" << endl;

	for (int i = 0; i < MAXV; i++) {
		if (!listas_adj[i].empty()) {
			cout << i << ": ";
			for (it = listas_adj[i].begin(); it != listas_adj[i].end(); ++it) {
				cout << "(" << it->destino + 1 << ", " << it->peso << ") ";
			}
			cout << std::endl;
		}
	}
}

void search_related(list<Aresta> listas_adj[],
					Itens itens[],
					int vertices,
					int origem,
					int similaridade_min,
					string jogador_j)
{
	bool visitado[MAXV] = {false};

	list<Aresta>::iterator it;
	for (it = listas_adj[origem].begin(); it != listas_adj[origem].end(); ++it)
	{
		if (origem < 0 || origem >= vertices) {
			cout << "Origem invalida.\n";
			return;
		}
		if (it->peso >= similaridade_min) {
			int v = it->destino;

			if (v >= 0 && v < vertices) {
				if (itens[v].owner != jogador_j && !visitado[v]) {
					visitado[v] = true;

					cout << "Item " << v << '\n'
							  << "Nome: " << itens[v].name << '\n'
							  << "Dono: " << itens[v].owner << '\n'
							  << "Propriedade Mágica: " << itens[v].property << '\n'
							  << "Raridade: " << itens[v].rarity << "\n\n";
				}
			}
		}
	}
}


void search(Itens itens[], int &n_itens, string search_name) // Faz a busca de um item pelo seu nome
{
	for(int i = 0; i < n_itens; i++)
	{
		if(itens[i].name == search_name){
			cout << "Item " << i << endl;
			cout << "Nome: " << itens[i].name << endl;
			cout << "Dono: " << itens[i].owner << endl;
			cout << "Propriedade Magica: " << itens[i].property << endl;
			cout << "Raridade: " << itens[i].rarity << endl;
			cout << endl;
		}
	}

}
void list_alpha(Itens itens[], int &n_itens) // Fazer em ordem alfabetica (incompleto)
{
	// lista todos itens, na ordem cadastrada !
	for(int i = 0; i < n_itens; i++)
	{
		cout << "Item " << i << endl;
		cout << "Nome: " << itens[i].name << endl;
		cout << "Dono: " << itens[i].owner << endl;
		cout << "Propriedade Magica: " << itens[i].property << endl;
		cout << "Raridade: " << itens[i].rarity << endl;
		cout << endl;
	}
}
void list_rarity()
{
	cout << "Funcionalidade em construção.\n";
}
void count_property()
{
	cout << "Funcionalidade em construção.\n";
}
void remove_common()
{
	cout << "Funcionalidade em construção.\n";
}

void menu()
{
	cout << "Menu:\n" << "0 - Sair\n"
		<< "1 - Inserir Item\n" << "2 - Definir Relação\n"
		<< "3 - Buscar Relacionados\n" << "4 - Verificar item\n"
		<< "5 - Listar (Alfabético)\n" << "6 - Listar (Raridade)\n"
		<< "7 - Contar propriedade\n" << "8 - Deletar menos raros\n";
}

int main()
{
	setlocale(LC_ALL, "Portuguese");

	Itens itens[1000];
	list<Aresta> listas_adj[MAXV];

	int control;
	int n_itens = 0;
	string search_name, jogador_j;

	int vertices, arestas, origem, destino, peso, simmin, codigo;

	menu();
	while(cin >> control && control != 0)
	{
		switch (control)
		{
			case 1:
				insert(itens,n_itens);
				break;
			case 2:
				cout << "Quantas relações(Arestas) gostaria de inserir?" << endl;
				cin >> arestas;
				define_related(listas_adj, arestas);
				break;
			case 3:
				cout << "Insira qual jogador nao deve estar incluido, qual item gostaria de comparar e a similaridade minima respectivamente\n";
				cin >> jogador_j >>codigo >> simmin;
				search_related(listas_adj, itens, n_itens, codigo, simmin,jogador_j);
				break;
			case 4:
				cout << "Item que está procurando: ";
				cin.ignore();
				getline(cin, search_name);
				search(itens, n_itens, search_name);
				break;
			case 5:
				list_alpha(itens, n_itens);
				break;
			case 6:
				list_rarity();
				break;
			case 7:
				count_property();
				break;
			case 8:
				remove_common();
				break;
			default:
				cout << "Instrução inválida.\n";
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








