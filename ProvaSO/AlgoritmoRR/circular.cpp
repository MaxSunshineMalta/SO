#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct process{
    string nome;
    int duracao;
    int ingresso;

}Process;

void circular(queue<Process> FilaDeProcessos, int quantum, int trocaDeContexto){
    int contador = 0;
    float somatorioTempoDeVida = 0;
    float somatorioTempoDeEspera = 0;
    //vector<Process> Proce;

    int qtdProcessos = FilaDeProcessos.size();
    int cont2 = 0;

    while(cont2 < qtdProcessos){
        Process primeiro = FilaDeProcessos.front();
        //Proce.push_back(primeiro);
        somatorioTempoDeEspera += primeiro.duracao;
        FilaDeProcessos.pop();
        FilaDeProcessos.push(primeiro);
        cont2++;
    }

    while(!FilaDeProcessos.empty()){
        Process primeiro = FilaDeProcessos.front();
        cout<<"Processo "<<primeiro.nome<<" está sendo executado."<<endl<<endl;
        int duracao = primeiro.duracao;
        primeiro.duracao -= quantum;

        if(primeiro.duracao <= 0){
            primeiro.duracao = 0;
            contador += duracao + trocaDeContexto;
            cout<<"Processo "<<primeiro.nome<<" terminou de ser executado."<<endl<<endl;
            //somatorioTempoDeEspera -= somatorioTempoDeVida;
            somatorioTempoDeVida += contador - trocaDeContexto - primeiro.ingresso;
            cout<<somatorioTempoDeVida<<endl;

            /*for(int i = 0; i < qtdProcessos; i++){
                if(Proce[i].nome == primeiro.nome){
                    cout<<somatorioTempoDeEspera<<endl;
                    cout<<Proce[i].duracao<<endl;
                    somatorioTempoDeEspera += somatorioTempoDeVida - Proce[i].duracao;
                    cout<<somatorioTempoDeEspera<<endl;
                }
            }*/

            FilaDeProcessos.pop();
        }else{
            contador += quantum + trocaDeContexto;
            FilaDeProcessos.pop();
            FilaDeProcessos.push(primeiro);
        }
    }

    somatorioTempoDeEspera = somatorioTempoDeVida - somatorioTempoDeEspera;

    float tempoDeVidaMedio = somatorioTempoDeVida / 4;
    cout<<"Tempo de Vida Médio: "<<tempoDeVidaMedio<<endl;

    float tempoDeEsperaMedio = somatorioTempoDeEspera / 4;
    cout<<"Tempo de Espera Médio: "<<tempoDeEsperaMedio<<endl;
}

int main(){
    queue<Process> FilaDeProcessos;
    vector<int> Entradas;
    vector<Process> Processos;

    Process processo1;
    processo1.nome = "T1";
    processo1.duracao = 10;
    processo1.ingresso = 5;
    Entradas.push_back(processo1.ingresso);
    Processos.push_back(processo1);

    Process processo2;
    processo2.nome = "T2";
    processo2.duracao = 30;
    processo2.ingresso = 15;
    Entradas.push_back(processo2.ingresso);
    Processos.push_back(processo2);

    
    Process processo3;
    processo3.nome = "T3";
    processo3.duracao = 20;
    processo3.ingresso = 10;
    Entradas.push_back(processo3.ingresso);
    Processos.push_back(processo3);

    
    Process processo4;
    processo4.nome = "T4";
    processo4.duracao = 40;
    processo4.ingresso = 0;
    Entradas.push_back(processo4.ingresso);
    Processos.push_back(processo4);

    sort(Entradas.begin(), Entradas.end());

    int tamanho = Entradas.size();

    for(int i = 0; i < tamanho; i++){
        for(int i2 = 0; i2 < tamanho;i2++){
            if(Entradas[i] == Processos[i2].ingresso){
                FilaDeProcessos.push(Processos[i2]);
            }
        }
    }

    int quantum = 15;
    int trocaDeContexto = 4;

    circular(FilaDeProcessos, quantum, trocaDeContexto);
}


