#include "lab.h"
#include <stdbool.h>




abrirFicheiroler(const char* filename)
{
	FILE* file = fopen(filename, "r");

	// Verificar se abriu com sucesso
	if (file == NULL) {
		printf("Erro ao abrir o ficheiro!\n");
		return;
	}

	// Ler do ficheiro
	
	char linha[256];
	while (fgets(linha, sizeof(linha), file) != NULL) {
		
		printf("%s", linha);
	}

	// Fechar o ficheiro
	fclose(file);
}


Ecra_Ini()
{
	setForeColor(MY_COLOR_LIGTH_GREEN);
	//gotoxy(45, 13); printf("jogo da Lebre e Tartaruga\n");
	

	showRectAt(40, 8, 36, 7);
	gotoxy(50, 10);
	printf("LEBRE vs TARTARUGA");
	gotoxy(45, 13);
	printf("Jogo de Apostas e Corridas\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Feito por: Dinis Almeida\n");
	
	system("pause");
}
Menu()
{
	setlocale(LC_ALL, "Portuguese");
	char opc;
	do
	{
		system("cls");
		gotoxy(10, 8); printf("Menu");
		gotoxy(10, 10); printf("1- Novo Jogo");
		gotoxy(10, 11); printf("2- Continuar jogo");
		gotoxy(10, 12); printf("3- Regras de jogo");
		gotoxy(10, 13); printf("4- Sair");
		gotoxy(10, 15); printf("Escolha uma opção:"); (void)scanf("%c", &opc);
	} while (opc != '1' && opc != '2' && opc != '3' && opc != '4');
	system("cls");
	switch (opc)
	{
		case '1':
		{
			break;
		}
		case '2':
		{
			break;
		}
		case '3':
		{
			abrirFicheiroler("regras.txt");
			system("pause");
			break;
		}
		case '4':
		{
			gotoxy(50, 8); printf("A SAIR DO JOGO\n");
			break;
		}
	}
}

int main()
{
	
	
	Ecra_Ini();
	Menu();
	
	return 0;
}