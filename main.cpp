#include <iostream>
#include <string>
#include <locale>

using namespace std;

struct itens{
	string name;
	string owner;
	string property;
    int id;
	int rarity;
};

void insert(itens Itens[], int &n_itens) // & para usar a var "n_itens" como referencia
{
	cout << "Nome do item: ";
	cin.ignore();
	getline(cin, Itens[n_itens].name); // input nome do item

	cout << "Quem é o dono do item: ";
	getline(cin, Itens[n_itens].owner); // input dono do item

	cout << "Qual é a propriedade magica: ";
	getline(cin, Itens[n_itens].property); // input propriedade magica

	cout << "Qual é a raridade: ";
	cin >> Itens[n_itens].rarity; // input raridade (0 a 100)

	n_itens++; // incremento
}
void define_related()
{
	cout << "Funcionalidade em construção.\n";
}
void search_related()
{
	cout << "Funcionalidade em construção.\n";
}
void search(itens Itens[], int &n_itens, string search_name) // Faz a busca de um item pelo seu nome
{
	for(int i = 0; i < n_itens; i++)
	{
		if(Itens[i].name == search_name){
			cout << "Item " << i << endl;
			cout << "Nome: " << Itens[i].name << endl;
			cout << "Dono: " << Itens[i].owner << endl;
			cout << "Propriedade Magica: " << Itens[i].property << endl;
			cout << "Raridade: " << Itens[i].rarity << endl;
			cout << endl;
		}
	}

}
void list_alpha(itens Itens[], int &n_itens) // Fazer em ordem alfabetica (incompleto)
{
	// lista todos itens, na ordem cadastrada !
	for(int i = 0; i < n_itens; i++)
	{
		cout << "Item " << i << endl;
		cout << "Nome: " << Itens[i].name << endl;
		cout << "Dono: " << Itens[i].owner << endl;
		cout << "Propriedade Magica: " << Itens[i].property << endl;
		cout << "Raridade: " << Itens[i].rarity << endl;
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
	
	itens Itens[1000];

	int control;
	int n_itens = 0;
	string search_name;
	
	menu();
	while(cin >> control && control != 0)
	{
		switch (control)
		{		 
			case 1:
				insert(Itens,n_itens);
				break;
			case 2:
				define_related();
				break;	
			case 3:
				search_related();
				break;
			case 4:
				cout << "Item que está procurando: ";
				cin.ignore();
				getline(cin, search_name);
				search(Itens, n_itens, search_name);
				break;
			case 5:
				list_alpha(Itens, n_itens);
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



