#include "ExpressaoSubtracao.hpp"
#include "Variavel.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;
ExpressaoSubtracao::ExpressaoSubtracao() { }

void ExpressaoSubtracao::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "- [ INI Subtracao"<< endl;
  esquerda->debug_com_tab(tab+1);
  tab3(tab);
  cerr << "-" << endl;
  direita->debug_com_tab(tab+1);
  tab3(tab);
  cerr << "- ] FIM Subtracao"<< endl;
}

Tipo* ExpressaoSubtracao::verificar_tipos(const vector<Variavel*>& variaveis, const vector<Variavel*>& parametros) {
    Tipo* tipo_esq = esquerda->verificar_tipos(variaveis, parametros);
    Tipo* tipo_dir = direita->verificar_tipos(variaveis, parametros);
    
    if (tipo_esq == nullptr || tipo_dir == nullptr) {
        return nullptr;
    }
    
    if (!tipo_esq->pode_fazer_operacao_aritmetica() || !tipo_dir->pode_fazer_operacao_aritmetica()) {
        cerr << "Erro semântico: Operação de subtração requer operandos numéricos" << endl;
        return nullptr;
    }
    
    if (tipo_esq->tipo == TipoSmallTalk::FLOAT || tipo_dir->tipo == TipoSmallTalk::FLOAT) {
        tipo_resultado = Tipo::FLOAT_TYPE();
        return Tipo::FLOAT_TYPE();
    }
    
    tipo_resultado = Tipo::INTEGER_TYPE();
    return Tipo::INTEGER_TYPE();
}

double ExpressaoSubtracao::calcular_valor(const map<string, double>& valores_variaveis) {
    return esquerda->calcular_valor(valores_variaveis) - direita->calcular_valor(valores_variaveis);
}
