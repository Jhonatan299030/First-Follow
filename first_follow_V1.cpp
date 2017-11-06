#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stack>
#define limpa system("cls");

using namespace std;

int StringLength(string x)
{
	int count = 1;
	for(int i = 0; x[i + 1] != '\0'; i++)
		count++;
	return count;
}

int NumeroProducoes(string x)
{
	int TamanhhoSequencia = 1, NSimbolos = StringLength(x);

	for(int i = 0; i < NSimbolos; i++)
	{
		if(x[i] == ' ')
		{
			TamanhhoSequencia++;
		}
	}
	return TamanhhoSequencia;
}

int MaiorNumeroProducoes(int NEstados, string V[])
{
	int SequenciaAtual, MSequencia = 0;
	string aux;

	for(int i = 0; i < NEstados; i++)
	{
		aux = V[i];
		SequenciaAtual = NumeroProducoes(aux);
		if(MSequencia < SequenciaAtual)
			MSequencia = SequenciaAtual;
	}

	return MSequencia;
}

string RemoveEspacos(string x)
{
	char atual;
	int tam = StringLength(x);
	for(int i = 0; i < tam; i++)
	{
		atual = x[i];
		if(atual == ' ')
		{
			for(int j = i; j < tam; j++)
			{
				x[j] = x[j + 1];
			}
		}
	}
	return x;
}

string SepararProducoes(string x, int ProdAtual)
{
	char atual;
	int count = 0, tam = StringLength(x);
	string producao = "\0";
	for(int i = 0; i < tam; i++)
	{
		atual = x[i];
		if(atual == ' ')
		{
			count++;
		}
		if(count == ProdAtual && atual != ' ')
		{
			producao += atual;
		}
	}
	return producao;
}
bool EstadoNaoTerminal(string EstadosNT, char CharComparacao, int NEstados)
{
	char AuxCharComparacao;

	for(int k = 0; k < NEstados; k++)
	{
		AuxCharComparacao = EstadosNT[k];
		if(CharComparacao == AuxCharComparacao)
		{
			return true;
		}
	}
	return false;
}
int Indice(string EstadosNT, char Comparacao, int NEstados)
{
	char Aux;
	for(int i = 0; i < NEstados; i++)
	{
		Aux = EstadosNT[i];
		if(Aux == Comparacao)
			return i;
	}
	return -1;
}
int main()
{
//Declaracao variaveis
	int op, i, j, NEstados, NSequencias, NProducoesTotais = 0;
	char AuxChar;
	string EstadosNT, AuxString;

//Menu
	printf("				-------------PROGRAMA FIRST-FOLLOW-------------\n");
	printf("				-----------------1 - ENTRAR--------------------\n");
	printf("				---------------2 - INFORMACOES-----------------\n");
	printf("				------------------3 - SAIR---------------------\n");
	printf("\n\n\n\n Digite a opcao desejada: ");
	scanf("%d", &op);

	if(op == 1)
	{
		limpa;
		fflush(stdin);
		printf("Digite os Estados nao terminais: \n");
		getline(cin, EstadosNT);
		EstadosNT = RemoveEspacos(EstadosNT);
		NEstados = StringLength(EstadosNT);
		string ProducoesEstados[NEstados];

		//Inserindo as producoes dos estados
		for(i = 0; i < NEstados; i++)
		{
			fflush(stdin);
			AuxChar = EstadosNT[i];
			AuxChar = toupper(AuxChar);
			EstadosNT[i] = AuxChar;
			cout << AuxChar << " -> ";
			getline(cin, ProducoesEstados[i]);
		}
		//Encontra a maior sequencia de producoes para definir o numero de colunas
		NSequencias = MaiorNumeroProducoes(NEstados, ProducoesEstados);

		//Cria as matrizes de gramatica / first / follow
		string gramatica[NEstados][NSequencias + 1];
		string first[NEstados][NSequencias + 1];
		string follow[NEstados][NSequencias + 1];

		//Transferindo os estados para as Matrizes
		for(i = 0; i < NEstados; i++)
		{
			first[i][0] = EstadosNT[i];
			follow[i][0] = EstadosNT[i];
			gramatica[i][0] = EstadosNT[i];
		}

		//Zera as matrizes, para inserção de dados
		for(i = 0; i < NEstados; i++)
		{
			for(j = 1; j < NSequencias; j++)
			{
				first[i][j] = '\0';
				follow[i][j] = '\0';
				gramatica[i][j] = '\0';
			}
		}

		//Vetor com o numero de producoes de cada estado nao terminal
		int NProducoes[NEstados];
		for(i = 0; i < NEstados; i++)
		{
			NProducoes[i] = NumeroProducoes(ProducoesEstados[i]);
			cout << NProducoes[i];
		}

		cout << "\n\n";
		//Insere as producoes na matriz
		for(i = 0; i < NEstados; i++)
		{
			for(j = 1; j <= NSequencias; j++)
			{
				AuxString = ProducoesEstados[i];
				AuxString = SepararProducoes(AuxString, j - 1);
				gramatica[i][j] = AuxString;
				cout << gramatica[i][j] << " ";
			}
			cout << "\n";
		}

		cout << "\n\n";
		//First direto
		for(i = 0; i < NEstados; i++)
		{
			for(j = 1; j < NSequencias; j++)
			{
				AuxString = gramatica[i][j];
				AuxChar = AuxString[0];
				if(!EstadoNaoTerminal(EstadosNT, AuxChar, NEstados))
				{
					first[i][j] += AuxChar;
				}
				cout << first[i][j];
			}
			cout << "\n";
		}

		//Contagem do total de producoes
		for(i = 0; i < NEstados; i++)
		{
			NProducoesTotais += NProducoes[i];
		}

		//First indireto
		while(1)
		{
			string AuxStringInterna, StringFirst;
			int indice, AuxInt, AuxInt1, CharAtual, Count = 0;
			char AuxCharInterno, NextChar;

			for(i = 0; i < NEstados; i++)
			{
				for(j = 1; j < NSequencias; j++)
				{
					////////Aqui verificar se por um looping while utilizando o CharAtual 
					////////resolveria a continuidade da sequencia
					AuxStringInterna = first[i][j];
					AuxCharInterno = StringAuxInterna[0];
					CharAtual = 0;
					
					//////Ideia atual = If verifica se ultima caracter eh um estado nao terminal e faz
					//////Varedura de first novamente, se for nao terminal e vazio concatena com o prox
					///// se nao for segue o jogo
					if(EstadoNaoTerminal(EstadosNT, CharAuxInterno, NEstados))
					{
						indice = Indice(EstadosNT, AuxCharInterno, NEstados);
						string s;
						char c;
						for(int k = 0; k < NSequencias; k++)
						{
							s = first[indice][k];
							c = s[0];
							if(c != '\0')
								AuxInt++;
						}
						if(AuxInt == NProducoes[indice])
						{
							for(int k = 0; k < NSequencias; k++)
							{
								StringFirst += first[indice][k];
							}
							StringFirst = RemoveEspacos(StringFirst);
							AuxInt1 = StringLength(StringFirst);
							c = StringFirst[AuxInt1];
							if(c == '/')
							{
								CharAtual++;
								NextChar = AuxString[CharAtual];
								if(NextChar != '\0')
								{
									StringFirst[AuxInt1] = NextChar;
								}
							}
						}
					}
					elseif(CharAuxInterno == '\0')
					{
						AuxString = gramatica[i][j];
						AuxChar = AuxString[0];
						if(AuxChar != '\0')
						{
							indice = Indice(EstadosNT, AuxChar, NEstados);
							string s;
							char c;
							for(int k = 0; k < NSequencias; k++)
							{
								s = first[indice][k];
								c = s[0];
								if(c != '\0')
									AuxInt++;
							}
							if(AuxInt == NProducoes[indice])
							{
								for(int k = 0; k < NSequencias; k++)
								{
									StringFirst += first[indice][k];
								}
								StringFirst = RemoveEspacos(StringFirst);
								AuxInt1 = StringLength(StringFirst);
								c = StringFirst[AuxInt1];
								if(c == '/')
								{
									CharAtual++;
									NextChar = AuxString[CharAtual];
									if(NextChar != '\0')
									{
										StringFirst[AuxInt1] = NextChar;
									}
								}
							}
						}
					}
					else
					{
						Count++;
					}
				}
			}

			if(Count == NProducoesTotais)
				break;
		}
	}
	else if(op == 2)
	{
		limpa;
		printf("informacao");
	}

	else if(op == 3)
	{

	}

	else
	{
		limpa;
		printf("Opção Inválida!");
	}


	return 0;
}
