#include "lab.h"
#include <stdbool.h>
#define PISTA_TAMANHO 14
#define N_PERSONAGENS 5
#define N_PODIO 3
typedef struct Baralho
{
	char cartas[81];
	char d[81]; //deck descarte
	char a[5]; //deck de aposta
	int size;
	int maxsize;
}baralho;
typedef struct BaralhoAposta
{
	int maxsize;
	int size;
	char cartas[8];
	char apostaI; //aposta incial dos jogadores
	char apostaF; //aposta feita pelos jogadores 
}Baposta;
typedef struct BaralhoDescarte
{
	int maxsize;
	int size;
	baralho descarte;
}descarte;
typedef struct pistaepodio {
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

void EI()//ecra inicial
{
	setColor(MY_COLOR_DARK_RED, MY_COLOR_BLACK);
	setFullScreen(true);
	gotoxy(35, 8); printf("Bem vindo ao jogo da Lebre e da Tartaruga\n");
	gotoxy(43, 9); printf("feito por: Dinis Almeida\n");
	system("pause");
}

void IniB(baralho* myB)
{
	/* l- lebre
	   w- lobo
	   W- lobo especial
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
			myB->a[0] = 'l';
		}
	}
	for (i = 18; i < 35; i++)
	{
		myB->cartas[i] = 't';
		myB->size++;
		if (i == 33)
		{
			myB->a[1] = 't';
		}
	}
	for (i = 35; i < 48; i++)
	{
		myB->cartas[i] = 'w';
		myB->size++;
		if (i == 46)
		{
			myB->a[2] = 'w';
		}
	}
	for (i = 48; i < 51; i++)
	{
		myB->cartas[i] = 'W';
		myB->size++;
	}
	for (i = 51; i < 66; i++)
	{
		myB->cartas[i] = 'r';
		myB->size++;
		if (i == 64)
		{
			myB->a[3] = 'r';
		}
	}
	for (i = 66; i < 81; i++)
	{
		myB->cartas[i] = 'c';
		myB->size++;
		if (i == 79)
		{
			myB->a[4] = 'c';
		}
	}
}
void BaralharBaralho(baralho* myB)
{
	int i;
	if (myB->size == 0) { return; }
	for (i = 0; i < myB->size; i++)
	{
		trocaChars(&(myB->cartas[i]), &(myB->cartas[rand() % myB->size]));
	}
}
void BaralharApostaI(baralho* myB)
{
	int i;
	myB->size = 5;
	if (myB->size == 0) { return; }
	for (i = 0; i < myB->size; i++)
	{
		trocaChars(&(myB->a[i]), &(myB->a[rand() % myB->size]));
	}
}
void PrintB(baralho myB)
{
	int i = 0;
	for (i = 0; i < 81; i++)//81---> myB.size
	{
		printf("%c,", myB.cartas[i]);
	}
	printf("\n");
}
void PrintBA(baralho myB)
{
	int i = 0;
	for (i = 0; i < 5; i++)//81---> myB.size
	{
		printf(" %c", myB.a[i]);
	}
}
void IniJ1(jogadorH* j1, baralho* myB)
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
void IniJ2(jogadorH* j1, jogadorNH* j2, baralho* myB)
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
void RemoverC(char vetor[], int tamanho, char carta)
{
	int i, j;
	for (i = 0; i < tamanho; i++)
	{
		if (vetor[i] == carta)
		{
			for (j = i; j < tamanho - 1; j++)
			{
				vetor[j] = vetor[j + 1];
			}
			tamanho--;
			i--;
		}
	}
}
bool CartaM(char mao[], int tamanhoMao, char cartaProcurada) {
	for (int i = 0; i < tamanhoMao; i++) {
		if (mao[i] == cartaProcurada) {
			return true;
		}
	}
	return false;
}
void apostaFJ(jogadorH* myJ) {
	int i;
	int escolha;
	do {
		printf("vamos escolher a sua aposta(numero)\n");
		for (i = 0; i < myJ->mao.maxsize; i++) {
			printf("%d:%c\n", i, myJ->mao.cartas[i]);
		}
		(void)scanf("%d", &escolha);
		printf("escolheu:%c\n", myJ->mao.cartas[escolha]);
	} while (escolha != 0 && escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4 && escolha != 5 && escolha && 6);
	myJ->mao.cartas[escolha] = 'x';
	//printf("%c", myJ->apostas.cartas[2]);
}
void ApostaFBot(jogadorNH* j2, baralho* myB)
{

	int indicedecartas = rand() % 7;
	j2->apostas.apostaF = j2->mao.cartas[indicedecartas];
	j2->mao.cartas[indicedecartas] = 'x';

}
Baposta ColocarCB(char carta, Baposta aposta)
{
	aposta.maxsize = 8;
	if (aposta.size < aposta.maxsize)
	{
		for (int i = 0; i < aposta.size; i++)
		{
			aposta.cartas[i] = carta;
		}

	}
	else
	{
		printf("O baralho de aposta está cheio. Não é possível adicionar mais cartas.\n");
	}

	return aposta;
}
jogadorH RemoverCM(char carta, int quantidade, jogadorH* j1)
{

	int removidas = 0;
	for (int j = 0; j < j1->mao.size; j++)
	{
		if (carta == j1->mao.cartas[j])
		{
			j1->mao.cartas[j] = 'x';
			removidas++;

			if (removidas == quantidade)
			{
				break;  // Sai do loop se o número desejado de cartas iguais foi removido
			}
		}
	}

	return *j1;
}
int ContarCM(char carta, jogadorH* j1)
{
	int contador = 0;
	for (int i = 0; i < j1->mao.maxsize; i++)
	{
		if (j1->mao.cartas[i] == carta)
		{
			contador++;
		}
	}
	return contador;
}
void EscolherCJ(jogadorH* j1, baralho* myB, Baposta aposta)
{


	int verdadeiro = 0;
	int quantidade;

	do
	{
		// Solicita uma carta para fazer de aposta Inicial
		printf("\nEscolhe agora a tua carta da aposta inicial: ");
		(void)scanf(" %c", &j1->jogar);
		if (j1->jogar == 'l')
		{
			j1->jogar = 'l';
		}
		else
		{
			if (j1->jogar == 'r')
			{
				j1->jogar = 'r';
			}
			else
			{
				if (j1->jogar == 'c')
				{
					j1->jogar = 'c';
				}
				else
				{
					if (j1->jogar == 't')
					{
						j1->jogar = 't';
					}
				}
			}
		}

		if (CartaM(j1->mao.cartas, 7, j1->jogar))
		{
			printf("Carta encontrada na mao!\n");
			verdadeiro = 1;
			printf("Quantas cartas iguais queres jogar: ");
			(void)scanf(" %d", &quantidade);

			int quantidade_na_mao = ContarCM(j1->jogar, j1);

			if (quantidade_na_mao < quantidade)
			{
				printf("Você não tem cartas suficientes na mão.\n");
				verdadeiro = 0;
				continue;  // Reinicia o loop para nova escolha
			}

			RemoverCM(j1->jogar, quantidade, j1);
			aposta.size = quantidade;
			aposta = ColocarCB(j1->jogar, aposta);


			for (int i = 0; i < quantidade; i++) {
				if (quantidade == 1) {
					printf(" Jogaste: %c\n", j1->jogar);
				}
				else
				{
					if (i == quantidade - 1) {
						printf(" %c\n", j1->jogar);
					}
					else
					{
						printf("Jogaste: %c,", j1->jogar);
					}

				}
			}

			printf("\nFicaste com estas cartas no teu deck :");
			for (int i = 0; i < 6; i++) {
				if (i == 5) {
					printf("%c", j1->mao.cartas[i]);
				}
				else
					printf("%c,", j1->mao.cartas[i]);
			}
			printf("\nBaralho de aposta atual: ");
			for (int i = 0; i < aposta.size; i++) {
				if (i == aposta.size - 1) {
					printf("%c", aposta.cartas[i]);
				}
				else {
					printf("%c, ", aposta.cartas[i]);
				}
			}
			printf("\n");
		}
		else {
			printf("Carta nao encontrada na mao.\n");

		}
	} while (verdadeiro != 1);
}
void PrintCApostaI(jogadorH j1)
{
	printf("\n%s cartas na mão: ", j1.name);
	for (int i = 0; i < 7; i++)
	{
		if (i == 6)
		{
			printf("%c ", j1.mao.cartas[i]);
		}
		else
		{
			printf("%c, ", j1.mao.cartas[i]);
		}
	}
	printf("\n");
}
void PrintCMparaJogar(jogadorH j1)
{
	printf("\n%s cartas na mão: ", j1.name);
	for (int i = 0; i < 6; i++)
	{
		if (i == 5)
		{
			printf("%c ", j1.mao.cartas[i]);
		}
		else
		{
			printf("%c, ", j1.mao.cartas[i]);
		}
	}
	printf("\n");
	printf("Cartas de aposta: %c, %c", j1.apostas.apostaF, j1.apostas.apostaI);
}
void PrintCMparaJogarBot(jogadorNH j2) {
	printf("\n%s cartas na mão: ", j2.name);
	for (int i = 0; i < 6; i++)
	{
		if (i == 5)
		{
			printf("%c ", j2.mao.cartas[i]);
		}
		else
		{
			printf("%c, ", j2.mao.cartas[i]);
		}
	}
	printf("\n");
	printf("Cartas de aposta: %c, %c", j2.apostas.apostaF, j2.apostas.apostaI);
}
Personagem pista[PISTA_TAMANHO];
void IniP()
{
	for (int i = 0; i < PISTA_TAMANHO; i++)
	{
		pista[i].tipo = ' ';
		pista[i].posicao = i + 1;
		pista[i].podio = 0;
	}
	pista[0].tipo = 'S';
	pista[PISTA_TAMANHO - 1].tipo = 'F';
}
void PrintP()
{

	for (int i = 0; i < PISTA_TAMANHO; i++)
	{
		if (pista[i].podio)
		{
			printf("%c ", pista[i].tipo);
		}
		else if (pista[i].tipo == ' ')
		{
			printf("|----| ");
		}
		else
		{
			if (i < PISTA_TAMANHO - 1 && pista[i].tipo == pista[i + 1].tipo)
			{
				printf("%c%c ", pista[i].tipo, pista[i + 1].tipo);
				i++;  // Pula para a próxima posição para evitar impressão duplicada
			}
			else
			{
				printf("%c ", pista[i].tipo);
			}
		}
	}
	printf("\n");
}
void MoverPersagem(jogadorH* j1, Baposta* aposta)
{

	char carta = j1->jogar;
	int countL = 0, avanco = 0;

	if (carta == 'L')
	{

		for (int i = 0; i < aposta->size; i++)
		{
			if (pista[i].tipo == 'L' && !pista[i].podio)
			{
				countL++;
			}
		}

		if (countL < 2)
		{
			avanco = 1;
		}
		else
		{
			avanco = 2;
		}
	}
	else if (carta == 'W')
	{

		for (int i = 0; i < aposta->size; i++)
		{
			if (pista[i].tipo == 'W' && !pista[i].podio)
			{
				countL++;
			}
		}

		if (countL < 2)
		{
			avanco = 1;
		}
		else
		{
			avanco = 2;
		}
	}
	else if (carta == 'T')
	{
		for (int i = 0; i < aposta->size; i++)
		{
			if (pista[i].tipo == 'T' && !pista[i].podio)
			{
				countL++;
			}
		}

		if (countL < 2)
		{
			avanco = 1;
		}
		else
		{
			avanco = 2;
		}
	}
	else if (carta == 'C')
	{
		for (int i = 0; i < aposta->size; i++) {
			if (pista[i].tipo == 'C' && !pista[i].podio)
			{
				countL++;
			}
		}

		if (countL < 2)
		{
			avanco = 1;
		}
		else
		{
			avanco = 2;
		}
	}
	else if (carta == 'R') {
		for (int i = 0; i < aposta->size; i++) {
			if (pista[i].tipo == 'R' && !pista[i].podio)
			{
				countL++;
			}
		}

		if (countL < 2)
		{
			avanco = 1;
		}
		else
		{
			avanco = 2;
		}
	}

	for (int i = 0; i < N_PERSONAGENS; i++)
	{
		if (pista[i].tipo == carta && !pista[i].podio)
		{
			int novaPosicao = pista[i].posicao + avanco;

			if (novaPosicao >= PISTA_TAMANHO - 1)
			{
				if (pista[i].tipo == 'E') {
					pista[i].posicao = PISTA_TAMANHO - 1;
					pista[i].podio = true;
				}
				else {
					pista[i].posicao = PISTA_TAMANHO - 2;
				}
			}
			else if (novaPosicao < 0)
			{
				pista[i].posicao = 0;
			}
			else
			{
				pista[i].posicao = novaPosicao;
			}
		}
	}

	for (int j = 0; j < PISTA_TAMANHO; j++)
	{
		int count = 0;
		for (int h = 0; h < N_PERSONAGENS; h++)
		{
			if (pista[h].posicao == j && !pista[h].podio)
			{
				count++;
			}
		}
		if (count > 1)
		{
			printf("Posição %d: ", j);
			for (int h = 0; h < N_PERSONAGENS; h++)
			{
				if (pista[h].posicao == j && !pista[h].podio)
				{
					printf("%c ", pista[h].tipo);
				}
			}
			printf("\n");
		}
	}
}
void AtualizarPosicoes(Personagem pista[], int tamanhoPista)
{
	for (int i = 0; i < tamanhoPista; i++)
	{
		if (!pista[i].podio)
		{
			int novaPosicao = pista[i].posicao - 1;
			if (novaPosicao >= tamanhoPista - 1)
			{
				if (pista[i].tipo == 'E') {
					pista[i].posicao = tamanhoPista - 1;
					pista[i].podio = true;
				}
				else
				{
					pista[i].posicao = tamanhoPista - 2;
				}
			}
			else if (novaPosicao < 0)
			{
				pista[i].posicao = 0;
			}
			else
			{
				pista[i].posicao = novaPosicao;
			}
		}
	}
}
void VerificarCPodio() {
	for (int i = 0; i < PISTA_TAMANHO; i++) {
		if (pista[i].posicao <= N_PODIO) {
			pista[i].podio = 1;
		}
	}
}
void contarcartas(baralho myBplay, int contagem[])
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		contagem[i] = 0;
	}

	while (i < myBplay.size)
	{
		switch (myBplay.cartas[i])
		{
		case 'l':
		{
			contagem[0]++;
			break;
		}
		case 't':
		{
			contagem[1]++;
			break;
		}
		case 'w':
		{
			contagem[2]++;
			break;
		}
		case 'r':
		{
			contagem[3]++;
			break;
		}
		case 'c':
		{
			contagem[4]++;
			break;
		}
		i++;
		}
	}
}
void NJ()
{
	baralho myB;
	jogadorH j1;
	jogadorNH j2;
	Baposta aposta = { .size = 0,.maxsize = 8 };
	IniB(&myB);
	BaralharBaralho(&myB);
	BaralharApostaI(&myB);
	IniJ1(&j1, &myB);
	system("cls");
	IniJ2(&j1, &j2, &myB);
	system("cls");

	PrintCApostaI(j1);
	apostaFJ(&j1);
	ApostaFBot(&j2, &myB);
	RemoverC(&j1.mao.cartas, 7, 'x');
	RemoverC(&j2.mao.cartas, 7, 'x');
	PrintCMparaJogar(j1);
	PrintCMparaJogarBot(j2);
	system("cls");

	IniP();
	PrintP();
	system("pause");

	PrintCMparaJogar(j1);
	EscolherCJ(&j1, &myB, aposta);
	MoverPersagem(&j1, &aposta);
	system("pause");
	system("cls");
	printf("Posições após mover Personagem:\n");

	AtualizarPosicoes(pista, PISTA_TAMANHO);
	PrintP();
}

void menu()
{
	char opc;
	do
	{
		system("cls");
		gotoxy(10, 8); printf("Menu");
		gotoxy(10, 10); printf("a- Novo Jogo");
		gotoxy(10, 11); printf("b- Continuar jogo");
		gotoxy(10, 12); printf("c- Regras de jogo");
		gotoxy(10, 13); printf("d- Sair");
		gotoxy(10, 15); printf("Escolha uma opção:"); (void)scanf(" %c", &opc);
	} while (opc != 'a' && opc != 'b' && opc != 'c' && opc != 'd');
	system("cls");
	switch (opc)
	{
	case 'a':
	{
		system("cls");
		NJ();
		break;
	}
	case 'b':
	{

		break;
	}
	case 'c':
	{

		break;
	}
	case 'd':
	{
		gotoxy(50, 8); printf("A sair do jogo\n");
		break;
	}
	}

}
int main() {
	setlocale(LC_ALL, "Portuguese");

	EI();
	menu();

	return 0;
}