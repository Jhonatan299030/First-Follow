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
	if(x == "")
	{
		return 0;
	}
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

string RemoveEspacos(string x, char c)
{
	char atual;
	int tam = StringLength(x);
	for(int i = 0; i < tam; i++)
	{
		atual = x[i];
		if(atual == c)
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
	string producao;
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
string StringConcat(string x, string y)
{
	int Intx, Inty, Intx1, j;
	Inty = StringLength(y);
	Intx = StringLength(x);
	x[Intx] = y[0];
	Intx1 = StringLength(x);
	if(Intx < Intx1)
	{
		j = 1;
	}
	else
	{
		j = 0;
	}
	for(int i = j; i < Inty; i++)
	{
		x += y[i];
	}
	return x;
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
		EstadosNT = RemoveEspacos(EstadosNT, ' ');
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
			for(j = 1; j < NSequencias + 1; j++)
			{
				AuxString = gramatica[i][j];
				AuxChar = AuxString[0];
				if(!EstadoNaoTerminal(EstadosNT, AuxChar, NEstados))
				{
					first[i][j] = AuxChar;
				}
			}
		}

		//Contagem do total de producoes
		for(i = 0; i < NEstados; i++)
		{
			NProducoesTotais += NProducoes[i];
		}

		//First indireto
		while(1)
		{
			string AuxStringInterna, StringFirst, StringRetorno, x;
			int indice, AuxInt, AuxInt1, CharAtual, Count = 0;
			char AuxCharInterno, NextChar;

			for(i = 0; i < NEstados; i++)
			{
				for(j = 1; j < NSequencias + 1; j++)
				{
					////////Aqui verificar se por um looping while utilizando o CharAtual
					////////resolveria a continuidade da sequencia
					AuxStringInterna = gramatica[i][j];
					AuxString = first[i][j];
					AuxChar = AuxString[0];
					CharAtual = 0;
					StringRetorno = "";

					while(1)
					{
						AuxCharInterno = AuxStringInterna[CharAtual];
						if(EstadoNaoTerminal(EstadosNT, AuxCharInterno, NEstados) && AuxChar == '\0')
						{
							AuxInt = 0;
							indice = Indice(EstadosNT, AuxCharInterno, NEstados);
							string s;
							char c;
							for(int k = 1; k < NSequencias + 1; k++)
							{
								s = first[indice][k];
								c = s[0];
								if(c != '\0')
									AuxInt++;
							}
							if(AuxInt == NProducoes[indice])
							{
								for(int k = 1; k < NSequencias + 1; k++)
								{
									x = first[indice][k];
									if(k == 1)
									{
										StringFirst = x;
									}
									else if(x != "")
									{
										StringFirst += x;
									}
								}
								AuxInt1 = StringLength(StringFirst);
								c = StringFirst[AuxInt1 - 1];
								if(c == '/')
								{
									NextChar = AuxStringInterna[CharAtual + 1];
									if(EstadoNaoTerminal(EstadosNT, NextChar, NEstados))
									{
										StringFirst[AuxInt1 - 1] = '\0';
										StringRetorno = StringConcat(StringRetorno, StringFirst);
										CharAtual++;

									}
									else if(NextChar != '\0')
									{
										StringFirst[AuxInt1 - 1] = NextChar;
										StringRetorno = StringConcat(StringRetorno, StringFirst);
										first[i][j] = StringRetorno;
										break;
									}
									else
									{
										StringRetorno = StringConcat(StringRetorno, StringFirst);
										first[i][j] = StringRetorno;
										break;
									}

								}
								else
								{
									StringRetorno = StringConcat(StringRetorno, StringFirst);
									first[i][j] = StringRetorno;
									break;
								}
							}
							else
							{
								break;
							}
						}
						else if(AuxChar != '\0')
						{
							Count++;
							break;
						}
						else
						{
							break;
						}
					}
				}
			}

			if(Count == NProducoesTotais)
				break;
		}

		for(i = 0; i < NEstados; i++)
		{
			for(j = 0; j < NSequencias + 1; j++)
			{
				cout << first[i][j] << " ";
			}
			cout << "\n";
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
