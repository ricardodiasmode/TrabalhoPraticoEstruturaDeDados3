
#include "Arvore.h"
#include<stdlib.h>
#include<cstdlib>

No::No()
{
	Item = -1;
	esq = nullptr;
	dir = nullptr;
}

No::No(int ItemInit)
{
	Item = ItemInit;
	esq = nullptr;
	dir = nullptr;
}

Arvore::Arvore()
{
	Raiz = nullptr;
}

void Arvore::Limpa()
{
	ApagaRecursivo(Raiz);
	Raiz = nullptr;
}

Arvore::~Arvore()
{
	Limpa();
}

void Arvore::CarregarArvore(std::ifstream* Arquivo)
{
	using namespace std;

	// Criando string que ira receber os caracteres da arvore
	char* StringArvore = new char[1000];
	*Arquivo >> StringArvore;

	// Preenchendo arvore
	Raiz = InsereRecursivo(Raiz, StringArvore[0]);
	int i = 1;
	while (StringArvore[i] != '\0')
	{
		Insere(StringArvore[i]);
		i++;
	}

	// Inserindo o espaco tendo como codigo o numero -999. Note que o operador ">>" ignora espacos.
	Insere(-999);

	// Preenchendo restante
	*Arquivo >> StringArvore;
	i = 0;
	while (StringArvore[i] != '\0')
	{
		Insere(StringArvore[i]);
		i++;
	}
}

void Arvore::Decodificar(std::ifstream* Arquivo)
{
	using namespace std;

	// String que ira segurar o codigo para ser decodificado
	char* StringCodigo = new char[2000];
	*Arquivo >> StringCodigo;

	// Variaveis auxiliares
	int j = 0;
	int i;
	bool par;

	// String que vai segurar a linha decodificada e que vamos printar
	char* StringToPrint = new char[1000];

	// Node auxiliar
	No* CurrentNode = Raiz;
	// Loop para checar para qual lado ira andar na arvore
	// Indo de 1 a n para pular o x inicial
	for (i = 1; StringCodigo[i] != '\0'; i++)
	{
		// Checa se chegou no x, e se chegou reinicia as variaveis para procurar outro caracter
		if (StringCodigo[i] == 'x')
		{
			if(CurrentNode->Item == -999)
				StringToPrint[j] = ' ';
			else
				StringToPrint[j] = static_cast<char>(CurrentNode->Item);
			j++;
			CurrentNode = Raiz;
			continue;
		}
		// Checa se o numero em questao eh par
		par = (StringCodigo[i] - '0') % 2 == 0 ? true : false;
		// Se for par, anda para a direita
		if (par)
		{
			// Verificacao se o node aa direita existe
			if (CurrentNode->dir != nullptr)
				CurrentNode = CurrentNode->dir;
		}
		// Se for impar, anda para a direita
		else
		{
			// Verificacao se o node aa esquerda existe
			if (CurrentNode->esq != nullptr)
				CurrentNode = CurrentNode->esq;
		}
	}
	// Atribuindo uma ultima vez apos o loop, pois no final da linha nao ha x, entao nao faz a atribuicao no loop
	StringToPrint[j] = static_cast<char>(CurrentNode->Item);
	StringToPrint[j+1] = '\0';

	// Ate aqui temos o vetor com as letras preenchido. Agora printamos esse vetor
	for (i = 0; StringToPrint[i] != '\0'; i++)
		cout << StringToPrint[i];
	cout << endl;

	// Deletando variaveis alocadas apos usar
	delete StringToPrint;
	delete StringCodigo;
}

void Arvore::Codificar(std::ifstream* Arquivo)
{
	using namespace std;

	// Criando string que ira segurar a linha a ser codificada
	char* StringLida = new char[1000];
	Arquivo->getline(StringLida, 1000);

	// Criando variaveis auxiliares
	No* CurrentNode = Raiz;
	int RandomNumberAux;
	int j = 1, i;

	// Criando string que ira segurar o codigo final
	char* StringCodigo = new char[1000];
	StringCodigo[0] = 'x';
	
	// Loop que vai de fato verificar o caminho e adicionar os numeros correspondentes ao caminho da letra em questao
	// Indo de 1 a n para pular o espaco
	for (i=1; StringLida[i] !='\0';i++)
	{
		// Verifica se procuramos o espaco
		if (StringLida[i] == ' ')
		{
			// Loop que verifica se o node atual(que inicia na raiz) ainda nao chegou no espaco
			while (CurrentNode->Item != -999)
			{
				// Atribuindo um numero aleatorio aa string que segura o codigo final
				RandomNumberAux = rand() % 10;
				// Enquanto o numero for par, randomiza novamente, pois queremos um numero impar
				while (RandomNumberAux % 2 == 0)
					RandomNumberAux = rand() % 10;
				// Atribuindo o numero aleatorio ao codigo
				StringCodigo[j] = '0' + (RandomNumberAux);
				// Andando para a esquerda no node atual
				CurrentNode = CurrentNode->esq;
				j++;
			}
			StringCodigo[j] = 'x';
			CurrentNode = Raiz;
			j++;
			continue;
		}
		// Loop que verifica se o node atual(que inicia na raiz) ainda nao chegou no node desejado
		while (CurrentNode->Item != (int)StringLida[i])
		{
			if (!CurrentNode)
			{
				// Check que verifica se o node atual esta nulo
				cout << "ERRO: NAO ENCONTROU A LETRA NA ARVORE";
				return;
			}
			// Verifica se o node que estamos lendo eh maior que o da nossa posicao atual
			if ((int)StringLida[i] > CurrentNode->Item)
			{
				// Atribuindo um numero aleatorio aa string que segura o codigo final
				RandomNumberAux = rand() % 10;
				// Enquanto o numero for impar, randomiza novamente, pois queremos um numero par
				while (RandomNumberAux % 2 != 0)
					RandomNumberAux = rand() % 10;
				StringCodigo[j] = '0' + (RandomNumberAux);
				// Andando para a direita no node atual
				CurrentNode = CurrentNode->dir;
				j++;
			}
			// Verifica se o node que estamos lendo eh menor que o da nossa posicao atual
			else if ((int)StringLida[i] < CurrentNode->Item)
			{
				// Atribuindo um numero aleatorio aa string que segura o codigo final
				RandomNumberAux = rand() % 10;
				// Enquanto o numero for par, randomiza novamente, pois queremos um numero impar
				while (RandomNumberAux % 2 == 0)
					RandomNumberAux = rand() % 10;
				StringCodigo[j] = '0' + (RandomNumberAux);
				// Andando para a esquerda no node atual
				CurrentNode = CurrentNode->esq;
				j++;
			}
		}
		// Se chegou aqui, encontrou o numero apos o loop. Portanto, coloca 'x' no codigo e volta para a raiz
		StringCodigo[j] = 'x';
		CurrentNode = Raiz;
		j++;
	}
	// Retirando o ultimo x da linha
	StringCodigo[j - 1] = '\0';
	// Printando o codigo
	for (i = 0; StringCodigo[i] != '\0'; i++)
		cout << StringCodigo[i];
	cout << endl;

	// Deletando variaveis alocadas apos usar
	delete StringLida;
	delete StringCodigo;
}

void Arvore::Insere(int Item)
{
	InsereRecursivo(Raiz, Item);
}

No* Arvore::InsereRecursivo(No* CurrentNode, int Item)
{
	if (CurrentNode == nullptr)
	{
		return new No(Item);
	}
	else
	{
		if(Item > CurrentNode->Item)
			CurrentNode->dir = InsereRecursivo(CurrentNode->dir, Item);
		else
			CurrentNode->esq = InsereRecursivo(CurrentNode->esq, Item);
	}
	return CurrentNode;
}

void Arvore::ApagaRecursivo(No* CurrentNode)
{
	if (CurrentNode != nullptr)
	{
		ApagaRecursivo(CurrentNode->esq);
		ApagaRecursivo(CurrentNode->dir);
		delete CurrentNode;
	}
}

void Arvore::InOrdem(No* CurrentNode)
{
	using namespace std;
	if (CurrentNode != nullptr)
	{
		InOrdem(CurrentNode->esq);
		cout << CurrentNode->Item << " ";
		InOrdem(CurrentNode->dir);
	}
}

void Arvore::PosOrdem(No* CurrentNode)
{
	using namespace std;
	if (CurrentNode != nullptr)
	{
		InOrdem(CurrentNode->esq);
		InOrdem(CurrentNode->dir);
		cout << CurrentNode->Item << " ";
	}
}
