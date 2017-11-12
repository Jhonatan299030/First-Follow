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

string RemoverCaracter(string x, char c)
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
string RemoveCaracterRepetido(string x, int NEstados)
{
	string StringInterna;
	char Caracterx, CaracterInterno;
	int TamStringInterna, Count, TamStringx = StringLength(x);
	for(int i = 0; i < TamStringx; i++)
	{
		Caracterx = x[i];
		TamStringInterna = StringLength(StringInterna);
		Count = 0;
		if(StringInterna == "")
		{
			StringInterna = Caracterx;
		}
		else
		{
			for(int j = 0; j < TamStringInterna; j++)
			{
				CaracterInterno = StringInterna[j];
				if(CaracterInterno != Caracterx)
					Count++;
			}
			if(Count == TamStringInterna)
				StringInterna += Caracterx;
		}
	}
	return StringInterna;
}
string VazioNoFim(string x)
{
	int AuxInt = StringLength(x);
	char AuxChar;
	bool Flag = false;
	for(int i = 0; i < AuxInt; i++)
	{
		AuxChar = x[i];
		if(AuxChar == '/')
		{
			Flag = true;
			i = AuxInt;
		}
	}
	if(Flag)
	{
		x = RemoverCaracter(x, '/');
		x = StringConcat(x, "/");
	}
	return x;
}
int main()
{
//Declaracao variaveis
	int op, i, j, NEstados, NSequencias, NProducoesTotais;
	char AuxChar, NextChar;
	string EstadosNT, AuxString;
	setlocale(LC_ALL, "Portuguese");

//Menu
Menu:
	limpa;
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
		EstadosNT = RemoverCaracter(EstadosNT, ' ');
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
		string VFollow[NEstados];
		string VFirst[NEstados];

		//Transferindo os estados para as Matrizes
		for(i = 0; i < NEstados; i++)
		{
			first[i][0] = EstadosNT[i];
			gramatica[i][0] = EstadosNT[i];
		}

		//Zera as matrizes, para inserção de dados
		for(i = 0; i < NEstados; i++)
		{
			for(j = 1; j < NSequencias; j++)
			{
				first[i][j] = '\0';
				VFollow[i] = '\0';
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
			}
		}

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
		NProducoesTotais = 0;
		for(i = 0; i < NEstados; i++)
		{
			NProducoesTotais += NProducoes[i];
		}

		//First indireto
		while(1)
		{
			string AuxStringInterna, StringFirst, StringRetorno, x;
			int indice, AuxInt, AuxInt1, CharAtual, Count = 0;
			char AuxCharInterno;

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
		
		cout << "\n\nProduções First:\n";
		//Limpa as producoes da matriz first e joga no vetor
		for(i = 0; i < NEstados; i++)
		{
			for(j = 1; j < NSequencias + 1; j++)
			{
				VFirst[i] += first[i][j];
			}
			AuxString = VFirst[i];
			VFirst[i] = RemoveCaracterRepetido(AuxString, NEstados);
			AuxString = VFirst[i];
			AuxString = VazioNoFim(AuxString);
			VFirst[i] = AuxString;
			cout << gramatica[i][0] << " -> " << VFirst[i] << "\n";
		}

		//Aqui comeca o choro do follow
		for(int h = 0; h < NEstados; h++)
		{
			string ProducaoGramatica, AuxStringInterna, FirstNext;
			char EstadoAtual, EstadoGramatica, CharFimFirst;
			int indice, FirstLength, AuxInt, Count;
			EstadoAtual = EstadosNT[h];
			AuxString = "";
			if(h == 0)
			{
				AuxString = "$";
			}

			for(i = 0; i < NEstados; i++)
			{
				for(j = 1; j < NSequencias + 1; j++)
				{
					ProducaoGramatica = gramatica[i][j];
					AuxInt = StringLength(ProducaoGramatica);
					for(int k = 0; k < AuxInt; k++)
					{
						EstadoGramatica = ProducaoGramatica[k];
						if(EstadoAtual == EstadoGramatica)
						{
							Count = k + 1;
							while(1)
							{
								NextChar = ProducaoGramatica[Count];
								if(EstadoNaoTerminal(EstadosNT, NextChar, NEstados))
								{
									//Pega o ultimo caracter da producao
									indice = Indice(EstadosNT, NextChar, NEstados);
									FirstNext = VFirst[indice];
									FirstLength = StringLength(FirstNext);
									CharFimFirst = FirstNext[FirstLength - 1];

									if(CharFimFirst == '/')
									{
										FirstNext = RemoverCaracter(FirstNext, '/');
										AuxString = StringConcat(AuxString, FirstNext);
										Count++;
									}
									else
									{
										AuxString = StringConcat(AuxString, FirstNext);
										break;
									}
								}
								else if(NextChar != '\0')
								{
									AuxString += NextChar;
									break;
								}
								else
								{
									AuxString = StringConcat(AuxString, VFollow[i]);
									break;
								}
							}
						}
					}
				}
			}
			//Atribui todas as producoes ao vetor de follow
			VFollow[h] = AuxString;
		}
		cout << "\n\nProduções Follow:\n";
		//Limpa as producoes da matriz first e joga no vetor
		for(i = 0; i < NEstados; i++)
		{
			AuxString = VFollow[i];
			VFollow[i] = RemoveCaracterRepetido(AuxString, NEstados);
			AuxString = VFollow[i];
			cout << gramatica[i][0] << " -> " << VFollow[i] << "\n";
		}
		cout<<"\n";
		system("pause");
		goto Menu;
	}
	else if(op == 2)
	{
		limpa;
		printf("-------------------------------FIRST------------------------------------\n");
		printf("Se a é uma forma sentencial (sequência de símbolos da grámatica,\n");
		printf("então FIRST(a) é o conjunto de terminais que iniciam formas sentenciais\n");
		printf("derivadas a partir de a. Se a->*E, então a palavra vazia também faz parte do conjunto.\n");
		printf("Seja a é terminal, então FIRST(a) = {a};\n");
		printf("Se X->E é uma produção, então adicione E a FIRST(X);\n");
		printf("Se X-> Y1Y2...Yk é uma produção e, para algum i, todos\n");
		printf("Y1, Y2, …, Yi-1 derivam E, então FIRST(Y1), FIRST(Y2), …, FIRST(Yi-1).\n");
		printf("O símbolo E será adicionado a FIRST(X) apenas se todo Yj (j=1, 2, …, k) derivar E.");
		printf("\n\n");
		printf("-------------------------------FOLLOW-----------------------------------\n");
		printf("A função do FOLLOW é definida para símbolos não-terminais.\n");
		printf("Sendo A um não-terminal, FOLLOW(A) é o conjunto de terminais a que\n");
		printf("podem aparecer imediatamente à direita de A em alguma forma sentencial.\n");
		printf("Isto é, o conjunto de terminais a, tal que existe uma derivação da forma\n");
		printf("S->*aAaB para a e B quaisquer.\n");
		printf("Se S é um símbolo inicial da grámatica e $ é o marcador de fim da sentença,\n");
		printf("então $ está em FOLLOW(S).\n");
		printf("Se existe produção do tipo A->aXB, então todos os símbolos de FIRST(B),\n");
		printf("exceto o vazio, fazem parte de FOLLOW(X).\n");
		printf("Se existe produção do tipo A-:aX, ou A->aXB,\n");
		printf("sendo que B->*E, então todos os símbolos que\n");
		printf("estiverem em FOLLOW(A) fazem parte do FOLLOW(X).\n\n");

		system("pause");
		goto Menu;
	}
	else if(op == 3)
	{
		printf(" \nVocê saiu do programa!\n");
	}
	else
	{
		limpa;
		printf("Opção Inválida!");

		system("pause");
		goto Menu;
	}
	return 0;
}
