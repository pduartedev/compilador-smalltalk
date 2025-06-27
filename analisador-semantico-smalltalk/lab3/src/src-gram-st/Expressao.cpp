#include "Expressao.hpp"
#include "ExpressaoDivisao.hpp"
#include "ExpressaoMod.hpp"
#include "ExpressaoMultiplicacao.hpp"
#include "ExpressaoNumero.hpp"
#include "ExpressaoInt.hpp"
#include "ExpressaoSoma.hpp"
#include "ExpressaoSubtracao.hpp"
#include "ExpressaoVariavel.hpp"
#include "ExpressaoBoolean.hpp"
#include "ExpressaoFloat.hpp"
#include "ExpressaoLogica.hpp"
#include "ExpressaoRelacional.hpp"
#include "Variavel.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

// Extração de expressões usando gramática completa do Smalltalk
Expressao* Expressao::extrai_expressao(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Expression -> Assignment | Basic_Expression (gramática completa)
  if (no->simb == "Expression") {
    for (auto filho : no->filhos) {
      if (filho->simb == "Assignment") {
        // Ignora Assignment aqui, será tratado em Comando
        return nullptr;
      }
      if (filho->simb == "Basic_Expression") {
        return extrai_expressao(filho);
      }
    }
  }
  
  // Basic_Expression -> Primary Message_Sequence (gramática completa)
  if (no->simb == "Basic_Expression") {
    if (no->filhos.size() >= 1) {
      // Processa Primary - ignora Message_Sequence por simplicidade na análise semântica
      return extrai_expressao(no->filhos[0]);
    }
  }
  
  // Primary -> TOKEN_identifier | Literal | TOKEN_left_paren Expression TOKEN_right_paren |
  //           Block_Constructor | TOKEN_self | TOKEN_super | TOKEN_true | TOKEN_false | TOKEN_nil (gramática completa)
  if (no->simb == "Primary") {
    return extrai_primary(no);
  }
  
  // Tentar extrair diretamente se for um terminal conhecido
  return extrai_primary(no);
}

Expressao* Expressao::extrai_primary(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Primary da gramática completa:
  // Primary -> TOKEN_identifier | Literal | TOKEN_left_paren Expression TOKEN_right_paren |
  //           Block_Constructor | TOKEN_self | TOKEN_super | TOKEN_true | TOKEN_false | TOKEN_nil
  
  if (no->simb == "Primary") {
    // Processar o primeiro filho que contém o conteúdo real
    if (no->filhos.size() > 0) {
      return Expressao::extrai_primary(no->filhos[0]);
    }
    return nullptr;
  }
  
  // TOKEN_identifier (gramática completa)
  if (no->simb == "TOKEN_identifier") {
    ExpressaoVariavel* var = new ExpressaoVariavel();
    var->nome = ID::extrai_ID(no);
    return var;
  }
  
  // Literal (gramática completa)
  if (no->simb == "Literal") {
    return Expressao::extrai_literal(no);
  }
  
  // TOKEN_left_paren Expression TOKEN_right_paren (gramática completa)
  if (no->simb == "TOKEN_left_paren") {
    // Buscar a expressão entre parênteses (ignorado por simplicidade)
    return nullptr;
  }
  
  // TOKEN_true, TOKEN_false (gramática completa)
  if (no->simb == "TOKEN_true" || no->simb == "TOKEN_false") {
    return ExpressaoBoolean::extrai_boolean(no);
  }
  
  // TOKEN_nil (gramática completa)
  if (no->simb == "TOKEN_nil") {
    // Retornar uma expressão que representa nil (tratado como 0 para análise semântica)
    return new ExpressaoInt(0);
  }
  
  // TOKEN_self, TOKEN_super (gramática completa - ignorados por simplicidade)
  if (no->simb == "TOKEN_self" || no->simb == "TOKEN_super") {
    // Por simplicidade, retorna nil
    return new ExpressaoInt(0);
  }
  
  // Block_Constructor (gramática completa - ignorado por simplicidade)
  if (no->simb == "Block_Constructor") {
    // Por simplicidade, retorna nil
    return new ExpressaoInt(0);
  }
  
  // Expressão entre parênteses: TOKEN_left_paren Expression TOKEN_right_paren
  if (no->simb == "TOKEN_left_paren" && no->filhos.size() >= 2) {
    return Expressao::extrai_expressao(no->filhos[1]);
  }
  
  // Se for Primary com filhos, processar o primeiro filho
  if (no->simb == "Primary" && no->filhos.size() > 0) {
    return Expressao::extrai_primary(no->filhos[0]);
  }
  
  return nullptr;
}

Expressao* Expressao::extrai_literal(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Literal da gramática completa:
  // Literal -> Number_Literal | String_Literal | Character_Literal | Symbol_Literal | Selector_Literal | Array_Literal
  
  if (no->simb == "Literal" && no->filhos.size() > 0) {
    No_arv_parse* filho = no->filhos[0];
    
    // Number_Literal (gramática completa)
    if (filho->simb == "Number_Literal") {
      return Expressao::extrai_number_literal(filho);
    }
    
    // String_Literal (gramática completa - ignorado por simplicidade)
    if (filho->simb == "String_Literal") {
      // Por simplicidade, tratar strings como texto (não implementado para análise semântica)
      return nullptr;
    }
    
    // Character_Literal (gramática completa - tratado como inteiro)
    if (filho->simb == "Character_Literal") {
      // Tratar caracteres como inteiros (código ASCII) para análise semântica
      return new ExpressaoInt(65); // Valor padrão 'A'
    }
    
    // Symbol_Literal, Selector_Literal, Array_Literal (gramática completa - ignorados por simplicidade)
    if (filho->simb == "Symbol_Literal" || filho->simb == "Selector_Literal" || filho->simb == "Array_Literal") {
      // Por simplicidade, ignorados na análise semântica
      return nullptr;
    }
  }
  
  return nullptr;
}

Expressao* Expressao::extrai_number_literal(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Number_Literal da gramática completa:
  // Number_Literal -> TOKEN_decimal_integer | TOKEN_radix_integer | TOKEN_float | TOKEN_scaled_decimal
  
  if (no->simb == "Number_Literal" && no->filhos.size() > 0) {
    No_arv_parse* filho = no->filhos[0];
    
    // TOKEN_decimal_integer (gramática completa)
    if (filho->simb == "TOKEN_decimal_integer") {
      return ExpressaoInt::extrai_int(filho);
    }
    
    // TOKEN_float (gramática completa)
    if (filho->simb == "TOKEN_float") {
      return ExpressaoFloat::extrai_float(filho);
    }
    
    // TOKEN_radix_integer, TOKEN_scaled_decimal (gramática completa - tratados como inteiros por simplicidade)
    if (filho->simb == "TOKEN_radix_integer" || filho->simb == "TOKEN_scaled_decimal") {
      // Por simplicidade na análise semântica, tratados como inteiros
      return ExpressaoInt::extrai_int(filho);
    }
  }
  
  return nullptr;
}

void Expressao::debug_com_tab(int tab) {
    tab3(tab);
    cerr << "Expressao base" << endl;
}

Tipo* Expressao::verificar_tipos(const vector<Variavel*>& variaveis, const vector<Variavel*>& parametros) {
    return tipo_resultado;
}
