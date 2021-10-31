#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EmptyTOS -1
#define MinTamPila 5
#define MaxTamArr  50

typedef struct pilaRegistro* Pila;

struct pilaRegistro
{
	int capacidad;
	int tope;
	char* arreglo;
};

Pila CrearPila(int tam)
{
	Pila s;
	if (tam < MinTamPila)
	{
		printf("Tamannio no apropiado\n");
	}
	s = (Pila)malloc(sizeof(struct pilaRegistro));
	s->capacidad = tam;
	s->tope = EmptyTOS;
	s->arreglo = (char*)malloc(sizeof(char) * tam);

	return s;
}

int EstaVacia(Pila s)
{
	return s->tope == EmptyTOS;
}

int EstaLlena(Pila s)
{
	return s->tope == s->capacidad - 1;
}

void Push(Pila s, char c)
{
	if (EstaLlena(s))
	{
		printf("Error, la pila esta llena");
		return;
	}
	else
	{
		s->arreglo[++(s->tope)] = c;
	}
}

char Top(Pila s)
{
	if (EstaVacia(s))
	{
		printf("Error, la pila esta vacia");
	}
	else
		return s->arreglo[s->tope];
}

char Pop(Pila s)
{
	if (EstaVacia(s))
	{
		printf("Error, la pila esta vacia");
	}
	else
		return s->arreglo[s->tope--];
}

int esMasAltoQue(char x, char y)
{
	if ((x == '(') && ((y == '+') || (y == '-') || (y == '*') || (y == '/')))
		return 1;
	else if (((x == '*') || (x == '/')) && ((y == '+') || (y == '-')))
		return 1;
	else
		return 0;
}

void InfijoAPostfijo(char* a)
{
	Pila s = CrearPila(50);
	int i = 0;

	while (a[i]!='\0')
	{
		if ((a[i] >= '0' && a[i] <= '9') || (a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z'))
			printf("%c ", a[i]);
		else if (a[i] == ')')
		{
			while (Top(s) != '(')
				printf("%c ", Pop(s));
			Pop(s);
		}
		else
		{
			if (EstaVacia(s))
				Push(s, a[i]);
			else if (esMasAltoQue(a[i], Top(s)))
				Push(s, a[i]);
			else
			{
				while (!EstaVacia(s) && (!esMasAltoQue(a[i], Top(s))))
				{
					if (Top(s) != '(')
						printf("%c ", Pop(s));
					else
						break;
				}
				Push(s, a[i]);
			}
		}
		i++;
	}

	while (!EstaVacia(s))
	{
		printf("%c ", Pop(s));
	}
}

int main()
{
	char str[MaxTamArr];
	printf("Dame infijo:\n");
	gets(str);
	printf("El postfijo:\n");
	InfijoAPostfijo(str);

	return 0;
}
