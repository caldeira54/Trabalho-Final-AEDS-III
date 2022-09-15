#include <iostream>
#include <locale.h>
#include <windows.h>
#include <stdio.h>

using namespace std;

typedef struct TipoGrafo{
    int qtoVertices;
    int qtoArestas;
    int ** matrizGrafo;
    int ** coordenada;
} TipoGrafo;

void limpaTela(){
    system("cls");
}

void imprimeGrafo(TipoGrafo *grafo){
    for(int j = 0;j < grafo->qtoVertices;j++){
        if(j == 0){
            cout << "    ";
        }
        cout << j << "\t";
    }
    cout << endl;
    for(int j = 0;j < grafo->qtoVertices;j++){
        if(j == 0){
            cout << "    ";
        }
        cout << "|\t";
    }
    cout << endl;
    for(int i = 0;i < grafo->qtoVertices;i++){
        cout << i << " - ";
        for(int j = 0;j < grafo->qtoVertices;j++){
            cout << grafo->matrizGrafo[i][j] << "\t";
        }
        cout << endl;
    }
}

void importar(TipoGrafo *grafo,char nomeDoArquivo[]){
    FILE *arq;
    int aux,aux2,aux3;

    arq = fopen(nomeDoArquivo,"r");

    if(arq != NULL){
        fscanf(arq,"%d",&grafo->qtoVertices);

        grafo->matrizGrafo = (int **) malloc(grafo->qtoVertices * sizeof(int *));
        for(int i = 0;i < grafo->qtoVertices;i++){
            grafo->matrizGrafo[i] = (int *) calloc(grafo->qtoVertices, sizeof(int));
        }

        grafo->coordenada = (int **) malloc(grafo->qtoVertices * sizeof(int *));
        for(int i = 0;i < grafo->qtoVertices;i++){
            grafo->coordenada[i] = (int *) malloc(2 * sizeof(int));
        }

        for(int i = 0;i < grafo->qtoVertices;i++){
            fscanf(arq,"%d %d %d",&aux,&grafo->coordenada[i][0],&grafo->coordenada[i][1]);
        }

        fscanf(arq,"%d",&grafo->qtoArestas);
        grafo->qtoArestas = grafo->qtoArestas * 2;

        for(int i = 0;i < grafo->qtoArestas;i++){
            fscanf(arq,"%d %d %d",&aux,&aux2,&aux3);
            grafo->matrizGrafo[aux][aux2] = aux3;
            grafo->matrizGrafo[aux2][aux] = aux3;
        }

        cout << "Arquivo importado com sucesso!" << endl;
        Sleep(2000);
        limpaTela();
    }else{
        cout << "Não foi possível abrir o arquivo" << endl;
        Sleep(2000);
        limpaTela();
    }

    fclose(arq);
}

void criarGrafoVazio(TipoGrafo *grafo){
    grafo->matrizGrafo = (int **) malloc(grafo->qtoVertices * sizeof(int *));
    for(int i = 0;i < grafo->qtoVertices;i++){
        grafo->matrizGrafo[i] = (int *) calloc(grafo->qtoVertices, sizeof(int));
    }

    grafo->coordenada = (int **) malloc(grafo->qtoVertices * sizeof(int *));
    for(int i = 0;i < grafo->qtoVertices;i++){
        grafo->coordenada[i] = (int *) calloc(2,sizeof(int));
    }

    grafo->qtoArestas = 0;
}

bool verificarAdjacencias(TipoGrafo *grafo,int u,int v){
    if(grafo->matrizGrafo[u][v] != 0){
        return true;
    } else {
        return false;
    }
}

void inserirArestas(TipoGrafo *grafo,int u,int v,int peso){
    if(peso > 0){
        if(u >= grafo->qtoVertices || v >= grafo->qtoVertices){
            cout << "Coordenada inexistente!" << endl;
            Sleep(2000);
            limpaTela();
        } else {
            if(grafo->matrizGrafo[u][v] == 0){
                grafo->matrizGrafo[u][v] = peso;
                grafo->matrizGrafo[v][u] = peso;
                grafo->qtoArestas = grafo->qtoArestas + 2;
                cout << "Aresta adicionada!" << endl;
                Sleep(2000);
                limpaTela();
            } else {
                cout << "Posição ocupada!" << endl;
                Sleep(2000);
                limpaTela();
            }
        }
    } else {
        cout << "Impossível colocar peso menor ou igual que 0!" << endl;
        Sleep(2000);
        limpaTela();
    }
}

void removerAresta(TipoGrafo *grafo,int u,int v){
    if(grafo->matrizGrafo[u][v] != 0){
        grafo->matrizGrafo[u][v] = 0;
        grafo->qtoArestas = grafo->qtoArestas - 1;
        cout << "Aresta removida!" << endl;
        Sleep(2000);
        limpaTela();
    } else {
        cout << "Essa posição está vazia!" << endl;
        Sleep(2000);
        limpaTela();
    }
}

void editarCoordenada(TipoGrafo *grafo,int vertice){
    int coordenadaX,coordenadaY;

    if(vertice >= 0 && vertice < grafo->qtoVertices){
        cout << "Digite a nova coordenada do vértice" << endl;
        cout << "Coordenada X : ";
        cin >> coordenadaX;
        cout << "Coordenada Y : ";
        cin >> coordenadaY;
        limpaTela();

        grafo->coordenada[vertice][0] = coordenadaX;
        grafo->coordenada[vertice][1] = coordenadaY;
    } else {
        cout << "Vértice não encontrado!" << endl;
        Sleep(2000);
        limpaTela();
    }
}

int consultarPrimeiroAdjacente(TipoGrafo *grafo,int vertice){
    for(int i = 0;i < grafo->qtoVertices;i++){
        if(grafo->matrizGrafo[vertice][i] != 0){
            return i;
        }
    }
    return -1;
}

int consultarProximoAdjacente(TipoGrafo *grafo,int vertice,int atual){
    for(int i = atual;i < grafo->qtoVertices;i++){
        if(grafo->matrizGrafo[vertice][i] != 0){
            return i;
        }
    }
    return -1;
}

void consultarListaDeAdjacentes(TipoGrafo *grafo,int vertice){
    cout << "Lista de adjacentes : ";
    for(int i = 0;i < grafo->qtoVertices;i++){
        if(grafo->matrizGrafo[vertice][i] != 0){
            cout << i << " ";
        }
    }
    cout << endl;
}

void exportar(TipoGrafo *grafo,char nomeDoArquivo[]){
    FILE *arq;
    int auxPeso = 0;

    arq = fopen(nomeDoArquivo,"w");

    if(arq != NULL){
        fprintf(arq,"%d\n",grafo->qtoVertices);

        for(int i = 0;i < grafo->qtoVertices;i++){
            fprintf(arq,"%d %d %d\n",i,grafo->coordenada[i][0],grafo->coordenada[i][1]);
        }

        fprintf(arq,"%d\n",grafo->qtoArestas);

        for(int i = 0;i < grafo->qtoVertices;i++){
            for(int j = 0;j < grafo->qtoVertices;j++){
                if(grafo->matrizGrafo[i][j] != 0){
                    auxPeso = grafo->matrizGrafo[i][j];
                    fprintf(arq,"%d %d %d\n",i,j,auxPeso);
                }
            }
        }

        cout << "Arquivo exportado com sucesso!" << endl;
        Sleep(2000);
        limpaTela();
    } else {
        cout << "Não foi possível criar o arquivo" << endl;
        Sleep(2000);
        limpaTela();
    }

    fclose(arq);
}
