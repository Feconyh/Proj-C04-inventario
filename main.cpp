#include <iostream>
#include <locale>

using namespace std;



void insert()
{
	cout << "Funcionalidade em construção.\n";
}
void define_related()
{
	cout << "Funcionalidade em construção.\n";
}
void search_related()
{
	cout << "Funcionalidade em construção.\n";
}
void search()
{
	cout << "Funcionalidade em construção.\n";
}
void list_alpha()
{
	cout << "Funcionalidade em construção.\n";
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


int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int control;
	
	
	
	cin >> control;
	
	switch (control)
	{		
		case 1:
			insert();
			break;
		case 2:
			define_related();
			break;	
		case 3:
			search_related();
			break;
		case 4:
			search();
			break;
		case 5:
			list_alpha();
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
	return 0;
}