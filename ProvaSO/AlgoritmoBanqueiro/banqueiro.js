import prompt from "prompt-sync"

let input = prompt();

function main(){
    let qtdProcessos = Number(input("Digite a quantidade de processos:"));
    let qtdRecursos = Number(input("Digite a quantidade de recursos:"));
    let recursosDisponiveis = [];
    let recursosExistentes = [];
    let matrizDeAlocacaoCorrente = [];
    let matrizDeRequisicoes = [];

    for(let i = 0; i < qtdRecursos; i++){
        let qtdRecursosExistentes = Number(input(`Digite a quantidade existente do recurso ${i}:`));
        recursosExistentes[i] = qtdRecursosExistentes;
    }

    for(let i = 0; i < qtdRecursos; i++){
        let qtdRecursosDisponiveis = Number(input(`Digite a disponibilidade do recurso ${i}:`));
        recursosDisponiveis[i] = qtdRecursosDisponiveis;
    }

    for(let i = 0; i < qtdProcessos; i++){
        let linhaProcesso = [];
        matrizDeAlocacaoCorrente[i] = linhaProcesso;

        for(let j = 0; j < qtdRecursos; j++){
            let qtdRecursosAlocados = Number(input(`Digite a quantidade alocada do recurso ${j} para o processo ${i}:`));
            linhaProcesso[j] = qtdRecursosAlocados;
        }
    }

    for(let i = 0; i < qtdProcessos; i++){
        let linhaProcesso = [];
        matrizDeRequisicoes[i] = linhaProcesso;
        
        for(let j = 0; j < qtdRecursos; j++){
            let qtdRecursosRequeridos = Number(input(`Digite a quantidade requerida do recurso ${j} para o processo ${i}:`));
            linhaProcesso[j] = qtdRecursosRequeridos;
        }
    }

    let resultado = banqueiro(recursosExistentes, recursosDisponiveis, matrizDeAlocacaoCorrente, matrizDeRequisicoes);
    console.log(resultado);
}

function banqueiro(recursosExistentes, recursosDisponiveis, matrizDeAlocacaoCorrente, matrizDeRequisicoes){
    let passou = false;
    let somatorioRecursosDiponiveis = 0;
    let somatorioRecursosExistentes = 0;

    for(let i = 0; i < recursosExistentes.length; i++){
        somatorioRecursosExistentes += recursosExistentes[i];
    }

    while (somatorioRecursosDiponiveis < somatorioRecursosExistentes) {
        for (let linhaR = 0; linhaR < matrizDeRequisicoes.length; linhaR++) {
            let podeAlocar = true;

            for (let requisicao = 0; requisicao < recursosExistentes.length; requisicao++) {
                if (matrizDeRequisicoes[linhaR][requisicao] <= recursosDisponiveis[requisicao]) {
                    continue;
                } else {
                    podeAlocar = false;
                    break;
                }
            }

            if (podeAlocar) {
                console.log(`Matriz de recursos disponíveis antes da soma: ${recursosDisponiveis}\n`);
                console.log(`Somando valores de matriz corrente do Processo ${linhaR} com Vetor de Recursos Disponíveis.\n`);

                for (let alocacao = 0; alocacao < recursosExistentes.length; alocacao++) {
                    recursosDisponiveis[alocacao] += matrizDeAlocacaoCorrente[linhaR][alocacao];
                }

                for (let i = 0; i < recursosDisponiveis.length; i++) {
                    somatorioRecursosDiponiveis += recursosDisponiveis[i];
                }

                console.log(`Matriz de recursos disponíveis após soma: ${recursosDisponiveis}\n`);

                console.log(`Removendo Processo ${linhaR}\n.`);
                matrizDeAlocacaoCorrente.splice(linhaR, 1);
                matrizDeRequisicoes.splice(linhaR, 1);

                passou = true;
                break;
            }

            if (!passou) {
                return "Ocorreu um impasse.";
            }
        }
    }
    return "Todos os processos rodaram, não ocorreram impasses.";
}

main();