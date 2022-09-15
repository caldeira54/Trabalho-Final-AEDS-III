#include <iostream>
#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include "ParteI.h"
#include "ParteII.h"

using namespace std;

int main(){

    setlocale(LC_ALL,"Portuguese");

    TipoGrafo grafo;
    int opcao,resultado;
    int u,v,vertice,atual,peso;
    int origem,destino;
    char nomeDoArquivo[255];

    do{
        cout << "********************************** MENU **********************************" << endl;
        cout << "*\t 1 - Importar um grafo de um arquivo de texto                    *" << endl;
        cout << "*\t 2 - Criar um grafo vazio                                        *" << endl;
        cout << "*\t 3 - Exibir as adjac�ncias                                       *" << endl;
        cout << "*\t 4 - Consultar a existencia de adjacencia entre v�rtices         *" << endl;
        cout << "*\t 5 - Inserir aresta                                              *" << endl;
        cout << "*\t 6 - Remover aresta                                              *" << endl;
        cout << "*\t 7 - Editar coordenada de um v�rtice                             *" << endl;
        cout << "*\t 8 - Consultar o primeiro adjacente um v�rtice                   *" << endl;
        cout << "*\t 9 - Consultar o pr�ximo adjacente de um v�rtice                 *" << endl;
        cout << "*\t 10 - Consultar a lista completa de ajacentes                    *" << endl;
        cout << "*\t 11 - Exportar o grafo para um arquivo de texto                  *" << endl;
        cout << "*\t 12 - Calcular �rvore geradora m�nima                            *" << endl;
        cout << "*\t 13 - Calcular menor caminho                                     *" << endl;
        cout << "*\t 14 - Encerrar programa                                          *" << endl;
        cout << "**************************************************************************" << endl << endl;
        cout << "Escolha uma op��o e tecle ENTER" << endl;
        cin >> opcao;
        limpaTela();

        switch(opcao){
            case 1:
                cout << "Digite o nome do arquivo juntamente com sua extens�o : ";
                cin >> nomeDoArquivo;
                limpaTela();

                importar(&grafo,nomeDoArquivo);
                break;

            case 2:
                cout << "Digite a quantidade de v�rtices do grafo : ";
                cin >> grafo.qtoVertices;
                limpaTela();

                criarGrafoVazio(&grafo);
                break;

            case 3:
                imprimeGrafo(&grafo);
                break;

            case 4:
                cout << "V�rtice X : ";
                cin >> u;
                cout << "V�rtice Y : ";
                cin >> v;
                limpaTela();

                if(verificarAdjacencias(&grafo,u,v)){
                    cout << "Existe adjac�ncia entre os vertices " << u << " e " << v << "!" << endl;
                } else {
                    cout << "N�o existe adjac�ncia entre os vertices " << u << " e " << v << "!" << endl;
                }
                break;

            case 5:
                cout << "V�rtice X : ";
                cin >> u;
                cout << "V�rtice Y : ";
                cin >> v;
                cout << "Peso : ";
                cin >> peso;
                limpaTela();

                inserirArestas(&grafo,u,v,peso);
                break;

            case 6:
                cout << "V�rtice X : ";
                cin >> u;
                cout << "V�rtice Y : ";
                cin >> v;
                limpaTela();

                removerAresta(&grafo,u,v);
                break;

            case 7:
                cout << "Digite o v�rtice : ";
                cin >> vertice;
                limpaTela();

                editarCoordenada(&grafo,vertice);
                break;

            case 8:
                cout << "V�rtice a ser consultado : ";
                cin >> vertice;
                limpaTela();

                resultado = consultarPrimeiroAdjacente(&grafo,vertice);

                if(resultado == -1){
                    cout << "O v�rtice " << vertice << " n�o tem adjacente!" << endl;
                } else {
                    cout << "O primeiro adjacente do v�rtice " << vertice << " � " << resultado << endl;
                }

            case 9:
                cout << "V�rtice a ser consultado : ";
                cin >> vertice;
                cout << "Insira o v�rtice inicial para consulta : ";
                cin >> atual;
                limpaTela();

                resultado = consultarProximoAdjacente(&grafo,vertice,atual);

                if(resultado != -1){
                    cout << "O pr�ximo adjacente do v�rtice " << vertice << " partindo do v�rtice " << atual << " � ";
                    cout << resultado << endl;
                } else {
                    cout << "O v�rtice " << vertice << " n�o tem adjacente partindo de " << atual << "!" << endl;
                }

            case 10:
                cout << "V�rtice a ser consultado : ";
                cin >> vertice;
                limpaTela();

                consultarListaDeAdjacentes(&grafo,vertice);
                break;

            case 11:
                cout << "Digite o nome do arquivo juntamente com sua extens�o : ";
                cin >> nomeDoArquivo;
                limpaTela();

                exportar(&grafo,nomeDoArquivo);
                break;

            case 12:
                //cout << verificaCiclo(&grafo) << endl;
                calcularArvoreGeradoraMinima(&grafo);
                break;

            case 13:
                cout << "V�rtice de origem : ";
                cin >> origem;
                cout << "V�rtice de destino : ";
                cin >> destino;
                limpaTela();

                calcularMenorCaminho(&grafo,origem,destino);
                break;

            case 14:
                break;

            default:
                cout << "Op��o Inv�lida, tente novamente." << endl;
                Sleep(2000);
                limpaTela();
                break;
        }

    }while(opcao != 14);

    return 0;
}
