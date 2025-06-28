#include "ComandoAtribuicao.hpp"
#include "Variavel.hpp"
#include <iostream>
#include "../debug-util.hpp"
using namespace std;

ComandoAtribuicao::ComandoAtribuicao() {
  
}

void ComandoAtribuicao::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "INI ATRIB: " << esquerda->nome << " = " << endl;
  direita->debug_com_tab(tab+1);
  tab3(tab);
  cerr << "FIM ATRIB" << endl;
  cerr << endl;
}

bool ComandoAtribuicao::verificar_tipos_semanticos(vector<Variavel*>& variaveis, const vector<Variavel*>& parametros) {
    // Primeiro verificar o tipo da expressão do lado direito
    Tipo* tipo_expressao = direita->verificar_tipos(variaveis, parametros);
    if (tipo_expressao == nullptr) {
        return false;
    }
    
    // Procurar se a variável já existe
    Variavel* variavel_encontrada = nullptr;
    
    for (auto& var : variaveis) {
        if (var->nome->nome == esquerda->nome) {
            variavel_encontrada = var;
            break;
        }
    }
    
    if (variavel_encontrada == nullptr) {
        for (const auto& param : parametros) {
            if (param->nome->nome == esquerda->nome) {
                variavel_encontrada = const_cast<Variavel*>(param);
                break;
            }
        }
    }
    
    // Se a variável não existe, criar uma nova com o tipo da expressão (declaração implícita)
    if (variavel_encontrada == nullptr) {
        cerr << "Declaração implícita da variável '" << esquerda->nome << "' com tipo " << tipo_expressao->to_string() << endl;
        
        // Criar nova variável
        Variavel* nova_variavel = new Variavel();
        nova_variavel->nome = esquerda;
        nova_variavel->tipo_semantico = tipo_expressao;
        
        // Adicionar à lista de variáveis
        variaveis.push_back(nova_variavel);
        
        return true;
    }
    
    // Se a variável existe e tem tipo UNDEFINED, fazer inferência de tipos
    if (variavel_encontrada->tipo_semantico->tipo == TipoSmallTalk::UNDEFINED) {
        cerr << "Inferindo tipo da variável '" << esquerda->nome << "' como " << tipo_expressao->to_string() << endl;
        variavel_encontrada->tipo_semantico = tipo_expressao;
        // Atualizar também o campo tipo para consistência
        variavel_encontrada->tipo->nome = tipo_expressao->nome;
        return true;
    }
    
    // Se a variável já existe com tipo definido, verificar compatibilidade de tipos
    if (!variavel_encontrada->tipo_semantico->compativel_com(tipo_expressao)) {
        cerr << "Erro semântico: Tipos incompatíveis na atribuição (" 
             << variavel_encontrada->tipo_semantico->to_string() << " := " << tipo_expressao->to_string() << ")" << endl;
        return false;
    }
    
    return true;
}

double ComandoAtribuicao::executar(map<string, double>& valores_variaveis) {
    double valor = direita->calcular_valor(valores_variaveis);
    valores_variaveis[esquerda->nome] = valor;
    return valor;
}
