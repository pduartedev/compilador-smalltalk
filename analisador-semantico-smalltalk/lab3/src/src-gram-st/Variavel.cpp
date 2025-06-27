#include "Variavel.hpp"
#include "ID.hpp"
#include "Tipo.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

vector<Variavel*> Variavel::extrai_lista_nao_vazia_parametros(No_arv_parse* no) {
  // LPx. 4) LPx -> P, 5) LPx -> P , LPx
  vector<Variavel*> res;
  res.push_back(extrai_variavel_P(no->filhos[0]));
  if (no->regra == 4) return res;
  // Tem que ser regra 5. LPx-> P , LPx
  vector<Variavel*> restante = extrai_lista_nao_vazia_parametros(no->filhos[2]);
  res.insert(res.end(), restante.begin(), restante.end());
  return res;
}

vector<Variavel *> Variavel::extrai_lista_parametros(No_arv_parse* no) {
  // LP
  if (no->regra == 2) return vector<Variavel*>();
  // Tem que ser regra 3, com unico filho.
  return extrai_lista_nao_vazia_parametros(no->filhos[0]);
}

vector<Variavel *> Variavel::extrai_lista_variaveis(No_arv_parse* no) {
  if (no->regra == 6) return vector<Variavel*>();
  // Tem que ser regra 7.
  vector<Variavel*> res;
  // 7) LV -> V LV    ,   10)V -> P ;   extrai(P) ,   
  res.push_back(extrai_variavel_P(no->filhos[0]->filhos[0]));
  // 7) LV -> V LV. Focando em LV da direita.
  vector<Variavel*> restante = extrai_lista_variaveis(no->filhos[1]);
  res.insert(res.end(), restante.begin(), restante.end());
  return res;
}

Variavel* Variavel::extrai_variavel_P(No_arv_parse* no) {
  Variavel* res = new Variavel();
  // 11) P -> ID ID
  res->tipo = ID::extrai_ID(no->filhos[0]);
  res->nome = ID::extrai_ID(no->filhos[1]);
  res->tipo_semantico = res->inferir_tipo_semantico();
  return res;
}

Tipo* Variavel::inferir_tipo_semantico() {
  if (tipo == nullptr) return Tipo::OBJECT_TYPE();
  
  string tipo_str = tipo->nome;
  if (tipo_str == "Integer" || tipo_str == "int") {
    return Tipo::INTEGER_TYPE();
  } else if (tipo_str == "Float" || tipo_str == "float") {
    return Tipo::FLOAT_TYPE();
  } else if (tipo_str == "Boolean" || tipo_str == "bool") {
    return Tipo::BOOLEAN_TYPE();
  } else {
    return Tipo::OBJECT_TYPE();
  }
}

void Variavel::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "[" << nome->nome << ":" <<  tipo->nome << "] Variavel Declarada" << endl;
}
