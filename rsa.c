#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

/*Acha o primo 1*/
long int findPrimo()
{
    long int number = 1, number2 = 0, seed = 0, i = 0, j = 0, *aux, returnNumber = 0;

    srand( (unsigned)time(NULL) );
    number2 = rand();
    number = number2*number2;


    aux = (long int*)malloc(number*sizeof(long int));

    for(i = 0; i < number; i++){
        aux[i] = i;
    }

    for (i = 2; i <= number2; i++) {
        if (aux[i] == i) {

            returnNumber = i;

            for (j = i+i; j <= number; j+=i) {
                aux[j]=0; // removendo da lista
            }
        }
    }
   return returnNumber;
}

/*Acha o primo 2*/
long int findPrimo2()
{
    long int number = 1, number2 = 0, seed = 0, i = 0, j = 0, *aux, returnNumber = 0;

    srand( (unsigned)time(NULL) );
    number2 = rand()/7;
    number = number2*number2;


    aux = (long int*)malloc(number*sizeof(long int));

    for(i = 0; i < number; i++){
        aux[i] = i;
    }

    for (i = 2; i <= number2; i++) {
        if (aux[i] == i) {

            returnNumber = i;

            for (j = i+i; j <= number; j+=i) {
                aux[j]=0; // removendo da lista
            }
        }
    }
   return returnNumber;
}

/*Dois números são primos entre si se, e somente se, o MDC
(Máximo divisor comum) entre os dois é 1.
Essa função calcula o MDC, se ele for igual a 1, retorna 0,
caso contrário, retorna o mdc*/
int primeBetween(long int x, long int y)
{
    long int resto = 0, biggest = 0,  smallest = 0, aux = 0;

    /*Tratamos o caso onde o e é maior que o z*/
    if(x > y){
        biggest = x;
        smallest = y;
    } else{
        biggest = y;
        smallest = x;
    }

    /*Encontramos o MDC, caso o resto seja 1, retornamos verdade
    caso contrário, retornamos o menor divisor comum*/
    resto = biggest%smallest;

    while(resto != 0 || resto != 1){
        if(resto == 0 || resto == 1){
          if(resto == 1)
            aux = 0;

          if(resto==0)
            aux = smallest;

          return aux;
        }else{
          biggest = smallest;
          smallest = resto;
        }
        resto = biggest%smallest;
    }

    return smallest;
}

/*Encontra o valor de e.
e precisa ser primo com z, e menor que n*/
long int findE(long int z, long int n)
{
    long int e = 1, aux = 1;

    while(aux != 0 && e < n){
        aux = primeBetween(z, e);
     //   printf("%d ", aux);
        e++;
    }
    //printf("%d ", e - 1);
 return (e - 1);
}

/*Algoritmo de Eucldies estendido, implementado com
o auxílio da função "primeBetween"*/
long int findD(long int z, long int e)
{
    long int mdc = 0, aux = 1, i = 0, j = 0, biggest = 0, smallest = 0;

    /*Tratamos o caso onde o e é maior que o z*/
    if(z > e){
        biggest = z;
        smallest = e;
    }else{
        biggest = e;
        smallest = z;
    }

    mdc = primeBetween(biggest, smallest);

    for(i = 0; i < e; i++){
        for(j = 0; j < z; j++){
            aux = (j*e) - (i*z);

            if(aux == 1){
              //  printf("%ld %ld\n", j, i);
                return j;
            }
        }
    }
    return -1;
}

/*Transforma a mensagem (que está em texto ASCI) em
números - no nosso caso, há a tradução do ASCI para
o seu respectivo inteiro*/
void transformInNumber(char *message, long int *m)
{
    int size = 0, i = 0;
    size = strlen(message);

        for(i = 0; i < size; i++){
            m[i] = (long int)message[i];
         //   printf("%ld ", m[i]);
        }
}

/*
Transforma a mensagem de números, para textos
*/
char* transformInAscii(long int *message, int size)
{
    int i = 0;
    char *m;

    m = (char*)malloc(size*sizeof(char));

    for(i = 0; i < size; i++){
        m[i] = (char)message[i];
    }

 return m;
}

/* Como os números podem ficar imensos, faço a exponenciação
por meio de uma operação bit a bit
 */
int myPow(long long a, long long b, int c) {
	int res = 1;
	while(b > 0) {
		/* Need long multiplication else this will overflow... */
		if(b & 1) {
			res = (res * a) % c;
		}
		b = b >> 1;
		a = (a * a) % c; /* Same deal here */
	}
	return res;
}

long int* rsaEncode(long int *m, long int e, long int n, long int size)
{
    long int i = 0, *c;

    c = (long int*)malloc(size*sizeof(long int));

    for(i = 0; i < size; i++){
        c[i] = myPow(m[i], e, n);
    }

    return c;
}

long int* rsaDecode(long int *c, long int d, long int n, long int size)
{
    long int i = 0, *m;

    m = (long int*)malloc(size*sizeof(long int));

    for(i = 0; i < size; i++){
        m[i] = myPow(c[i], d, n);
    }
 return m;
}

int main()
{
   long int p = findPrimo(), q = findPrimo2(), e = 0, d = 0, size = 0;
   long int n = p*q, z = (p-1)*(q-1);
   long int *v2, *v3 ;
   char *m;
    e = findE(z, n);
    d = findD(z, e);

    long int vet[10];
    size = (long int)strlen("azaa");

    transformInNumber("aaza", vet);
    v2 = rsaEncode(vet, e, n, size);
    v3 = rsaDecode(v2, d, n, size);
    m = transformInAscii(v3, size);

    int i = 0;
    for(i = 0; i < size; i++)
        printf("%c", m[i]);

return 0;
}
