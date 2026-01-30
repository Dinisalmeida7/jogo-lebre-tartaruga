#include "lab.h"
#include <stdbool.h>

typedef struct Baralho
{
	char cartas[81];
	char des[81]; //deck descarte
	char apos[5]; //deck de aposta
	int size;
	int maxsize;
}baralho;
typedef struct BaralhoAposta
{
	int maxsize;
	int size;
	char cartas[8];
	char apostaIni; //aposta incial dos jogadores
	char apostaFin; //aposta feita pelos jogadores 
}Baposta;
typedef struct BaralhoDescarte
{
	int maxsize;
	int size;
	baralho descarte;
}descarte;
typedef struct pistaEpodio {
	char tipo;
	int posicao;
	bool podio;
} Personagem;
typedef struct JOGADOR
{
	char name[30];
	int type;
	baralho mao;
	Baposta apostas;
	int pontos;
	char jogar;

}jogadorH;
typedef struct BOT
{
	char name[30];
	int type;
	baralho mao;
	Baposta apostas;
	int pontos;
	char jogar;
}jogadorNH;


//FUNÇÕES DE SUPORTE
PrintB(baralho myB)
{
	int i = 0;
	for (i = 0; i < 81; i++)//81---> myB.size
	{
		printf("%c,", myB.cartas[i]);
	}
	printf("\n");
}
PrintBA(baralho myB)
{
	int i = 0;
	for (i = 0; i < 5; i++)//81---> myB.size
	{
		printf(" %c", myB.apos[i]);
	}
}


//FUNÇÕES DE INICIAÇÃO
IniB(baralho* myB)
{
	//INICIAR BARALHO

	/* l- lebre
	   w- lobo 
	   L- lobo especial
	   t- tartaruga
	   r- raposa
	   c- cordeiro
	*/
	int i = 0;
	myB->size = 0;
	for (i = 0; i < 18; i++)
	{
		myB->cartas[i] = 'l';
		myB->size++;
		if (i == 16)
		{
			myB->apos[0] = 'l';
		}
	}
	for (i = 18; i < 35; i++)
	{
		myB->cartas[i] = 't';
		myB->size++;
		if (i == 33)
		{
			myB->apos[1] = 't';
		}
	}
	for (i = 35; i < 48; i++)
	{
		myB->cartas[i] = 'w';
		myB->size++;
		if (i == 46)
		{
			myB->apos[2] = 'w';
		}
	}
	for (i = 48; i < 51; i++)
	{
		myB->cartas[i] = 'L';
		myB->size++;
	}
	for (i = 51; i < 66; i++)
	{
		myB->cartas[i] = 'r';
		myB->size++;
		if (i == 64)
		{
			myB->apos[3] = 'r';
		}
	}
	for (i = 66; i < 81; i++)
	{
		myB->cartas[i] = 'c';
		myB->size++;
		if (i == 79)
		{
			myB->apos[4] = 'c';
		}
	}
}
IniJ1(jogadorH* j1, baralho* myB)
{
	gotoxy(0, 7); printf("Introduza o nome do jogador1: ");
	(void)scanf("%s´", j1->name);
	int i;
	j1->mao.maxsize = 7;
	j1->mao.size = 0;
	for (i = 0; i < j1->mao.maxsize; i++)
	{
		j1->mao.size++;
		j1->mao.cartas[i] = myB->cartas[i];
		myB->cartas[i] = 'x';
		if (i == j1->mao.maxsize)
		{
			printf("%c", j1->mao.cartas[i]);

		}
		else
			printf("%c,", j1->mao.cartas[i]);
	}

}
IniJ2(jogadorH* j1, jogadorNH* j2, baralho* myB)
{
	gotoxy(0, 7); printf("Introduza o nome do Playe Two: ");
	(void)scanf("%s", j2->name);
	int i;
	int posicao_maoB = 0;;
	j2->mao.maxsize = 7;
	j2->mao.size = 0;
	for (i = 0; i < j1->mao.maxsize + j2->mao.maxsize; i++)
	{
		if (myB->cartas[i] != 'x')
		{
			j2->mao.cartas[posicao_maoB] = myB->cartas[i];
			myB->cartas[i] = 'x';
			posicao_maoB++;
			j2->mao.size++;
			if (posicao_maoB == j2->mao.maxsize)
			{
				break;
			}
		}
	}
	for (int i = 0; i < j2->mao.maxsize; i++)
	{
		if (i == j2->mao.maxsize)
		{
			printf("%c", j2->mao.cartas[i]);

		}
		else
			printf("%c,", j2->mao.cartas[i]);
	}


}

//FUNÇÕES DE CARTAS
BaralharBaralho(baralho* myb)
{
	int i;
	if (myb->size == 0) { return; }
	for (i = 0; i < myb->size; i++)
	{
		trocaChars(&(myb->cartas[i]), &(myb->cartas[rand() % myb->size]));
	}
}





NovoJogo()
{

	baralho myb;

	IniB(&myb);
	BaralharBaralho(&myb);


}

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
			NovoJogo();
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
			Menu();
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

	setlocale(LC_ALL, "Portuguese");
	Ecra_Ini();
	Menu();
	
	return 0;
}