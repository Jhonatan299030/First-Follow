#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stack>
#define limpa system("cls");

using namespace std;

int stringlength(string x)
{
	int count = 1;
	for(int i = 0; x[i + 1] != '\0'; i++)
		count++;
	return count;
}

int maiorsequencia(int NEstados, string V[])
{
	int TamanhhoSequencia, NSimbolos, MSequencia = 0;
	string aux;

	for(int i = 0; i < NEstados; i++)
	{
		TamanhhoSequencia = 1;
		aux = V[i];
		NSimbolos = stringlength(aux);
		for(int j = 0; j < NSimbolos; j++)
		{
			if(aux[j] == ' ')
			{
				TamanhhoSequencia++;
			}
		}

		if(MSequencia < TamanhhoSequencia)
			MSequencia = TamanhhoSequencia;
	}

	return MSequencia;
}

string RemoveEspacos(string x)
{
	char atual;
	int tam = stringlength(x);
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
	int count = 0, tam = stringlength(x);
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
bool EstadoTerminal(string EstadosNT, char CharComparacao)
{
	int NEstados, Count=0;
	char AuxCharComparacao;
	
	NEstados = stringlength(EstadosNT);
	
	for(int k = 0; k < NEstados; k++)
	{
		AuxCharComparacao = EstadosNT[k];
		if(CharComparacao != AuxCharComparacao)
		{
			Count++;
		}		
	}
	if(Count == NEstados)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*
string FirstIndireto(char Estado, int colunas, string Mat[][])
{

}
*/
int main()
{
//Declaracao variaveis
	int op, i, j, NEstados, NSequencias;
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
		NEstados = stringlength(EstadosNT);
		string ProducoesEstados[NEstados];

		//Inserindo a derivacao dos estados
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
		NSequencias = maiorsequencia(NEstados, ProducoesEstados);

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
			cout<<"\n";
		}
		
		cout << "\n\n";
		//First direto
		for(i = 0; i < NEstados; i++)
		{
			for(j = 1; j < NSequencias; j++)
			{
				AuxString = gramatica[i][j];
				AuxChar = AuxString[0];
				if(EstadoTerminal(EstadosNT,AuxChar))
				{
					first[i][j] += AuxChar;
				}
				cout << first[i][j];
			}
			cout << "\n";
		}
/*
		//First indireto
		while(1)
		{
			string AuxStringInterna;
			char AuxCharInterno;

			for(i = 0; i < NEstados; i++)
			{
				for(j = 1; j < NSequencias; j++)
				{
					AuxStringInterna = first[i][j];
					AuxCharInterno = StringAuxInterna[0];
					if(CharAuxInterno == '\0')
					{
						AuxString = gramatica[i][j];
						AuxChar = AuxString[0];
						if(!EstadoTerminal(EstadosNT,AuxChar))
						{
							FirstIndireto(AuxChar);
						}
					}
				}
			}
		}

*/





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
