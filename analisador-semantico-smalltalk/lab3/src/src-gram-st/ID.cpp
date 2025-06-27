#include "ID.hpp"
#include <iostream>
using namespace std;

ID* ID::extrai_ID(No_arv_parse* no) {
  ID* res = new ID();
  
  // Debug: imprimir informações sobre o nó
  cerr << "DEBUG ID::extrai_ID - simb: '" << no->simb 
       << "', dado_extra: '" << no->dado_extra
       << "', lexema: '" << no->lexema << "'" << endl;
  
  // Se o nó atual é um TOKEN_identifier, usar diretamente
  if (no->simb == "TOKEN_identifier") {
    res->nome = no->dado_extra;
    if (res->nome.empty() && !no->lexema.empty()) {
      res->nome = no->lexema;
    }
  } else {
    // Caso contrário, procurar por um filho TOKEN_identifier
    for (int i = 0; i < (int)no->filhos.size(); i++) {
      if (no->filhos[i]->simb == "TOKEN_identifier") {
        res->nome = no->filhos[i]->dado_extra;
        if (res->nome.empty() && !no->filhos[i]->lexema.empty()) {
          res->nome = no->filhos[i]->lexema;
        }
        cerr << "DEBUG: Encontrou TOKEN_identifier filho com nome: '" << res->nome << "'" << endl;
        break;
      }
    }
  }
  
  if (res->nome.empty()) {
    cerr << "DEBUG: Nome ainda vazio após extração!" << endl;
  }
  
  return res;
}
