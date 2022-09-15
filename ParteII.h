#include <iostream>
#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>

using namespace std;

typedef struct TipoAresta{
    int u;
    int v;
    int p;
} TipoAresta;

void BubbleSort(TipoAresta *lista,int tamanho){
    TipoAresta aux;

    for(int i = 0;i < tamanho - 1;i++){
        for(int j = 1;j < tamanho - i;j++){
            if(lista[j].p < lista[j - 1].p){
                aux = lista[j];
                lista[j] = lista[j - 1];
                lista[j - 1] = aux;
            }
        }
    }
}

bool visitaDfs (int u, TipoGrafo *grafo, int* cor, int* antecessor){
    int aux;
    cor[u] = 1;

    if(consultarPrimeiroAdjacente(grafo,u) != -1){
        aux = consultarPrimeiroAdjacente(grafo,u);
        while(aux != -1){
            if(cor[aux] == 0){
                antecessor[aux] = u;
                visitaDfs(aux,grafo,cor,antecessor);
            } else if(aux != antecessor[u]){
                return true;
            }
            aux = consultarProximoAdjacente(grafo,u,aux + 1);
        }
    }
    cor[u] = 2;
    return false;
}

bool verificaCiclo(TipoGrafo *grafo){
    int maxNumVertices = grafo->qtoVertices;
    int cor[maxNumVertices + 1];
    int antecessor[maxNumVertices + 1];
    bool temCiclo = false;

    for (int x = 0; x < grafo->qtoVertices; x++){
        cor[x] = 0;
        antecessor[x] = -1;
    }

    for (int x = 0;x < grafo->qtoVertices && !temCiclo;x++){
        if(cor[x] == 0){
            temCiclo = visitaDfs(x, grafo, cor, antecessor);
        }
    }
    return temCiclo;
}

void calcularArvoreGeradoraMinima(TipoGrafo *grafo){
    TipoAresta *vetorAresta = (TipoAresta *) calloc(grafo->qtoArestas, sizeof(vetorAresta));
    TipoGrafo grafoAux;
    int k = 0;
    int pesoTotal = 0;

    grafoAux.qtoVertices = grafo->qtoVertices;
    grafoAux.qtoArestas = 0;

    grafoAux.matrizGrafo = (int **) malloc(grafoAux.qtoVertices * sizeof(int *));
    for(int i = 0;i < grafoAux.qtoVertices;i++){
        grafoAux.matrizGrafo[i] = (int *) calloc(grafoAux.qtoVertices, sizeof(int));
    }

    for(int i = 0;i < grafo->qtoVertices;i++){
        for(int j = 0;j < grafo->qtoVertices;j++){
            if(grafo->matrizGrafo[i][j] != 0){
                vetorAresta[k].p = grafo->matrizGrafo[i][j];
                vetorAresta[k].u = i;
                vetorAresta[k].v = j;
                k++;
            }
        }
    }

    BubbleSort(vetorAresta,grafo->qtoArestas);

    for(int i = 0;i < grafo->qtoArestas;i++){
        grafoAux.matrizGrafo[vetorAresta[i].u][vetorAresta[i].v] = vetorAresta[i].p;
        pesoTotal = pesoTotal + vetorAresta[i].p;
        if(verificaCiclo(&grafoAux)){
            grafoAux.matrizGrafo[vetorAresta[i].u][vetorAresta[i].v] = 0;
            pesoTotal = pesoTotal - vetorAresta[i].p;
        }
    }

    imprimeGrafo(&grafoAux);
    cout << endl << "Peso Total : " << pesoTotal << endl;
}

void calcularMenorCaminho(TipoGrafo *grafo, int origem, int destino){
    int i,vert,k,novaDist,min;
    int *m,*l,*a,*caminho;

    m = (int *) malloc (grafo->qtoVertices * sizeof(int)); // determina se um vertice ja foi visitado
    l = (int *) malloc (grafo->qtoVertices * sizeof(int)); // determina o caminho mais curto entre origem e destino
    a = (int *) malloc (grafo->qtoVertices * sizeof(int)); //infinito determina o comprimento do caminho mais curto
    caminho = (int *) malloc (grafo->qtoVertices * 3 * sizeof(int));


    for(i = 0;i < grafo->qtoVertices;i++){
        m[i] = 0;
        a[i] = -1;
        l[i] = 300000;
    }

    vert = origem;
    l[vert] = 0;

    while(vert != destino && vert != -1){
        for(i = 0;i < grafo->qtoVertices;i++){
            if(grafo->matrizGrafo[vert][i] != 0 && m[i]==0){
                novaDist = l[vert] + grafo->matrizGrafo[vert][i];
                if(novaDist < l[i]){
                    l[i] = novaDist;
                    a[i] = vert;
                }
            }
        }

        m[vert] = 1;
        min = 300000;
        vert = -1;

        for(i = 0;i < grafo->qtoVertices;i++){
            if (m[i] == 0 && l[i] < min){
                min = l[i];
                vert = i;
            }
        }
    }

    if(vert == destino){
        cout << "O caminho mais curto entre " << origem << " e " << destino << " tem comprimento " << l[destino] << endl;
        caminho[0] = destino;
        k = 1;

        while(vert != origem){
            caminho[k] = a[vert];
            vert = a[vert];
            k++;
        }

        cout << "Caminho percorrido : ";
        for (i = k - 1;i >= 0;i--){
            cout << caminho[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Não existe caminho entre " << origem << " e " << destino << endl;
    }
}
