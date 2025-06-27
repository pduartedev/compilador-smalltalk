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
#include "ExpressaoBinaria.hpp"
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
    if (no->filhos.size() >= 2) {
      // Processa Primary e Message_Sequence para operações binárias
      Expressao* primary = extrai_expressao(no->filhos[0]);
      if (primary != nullptr && no->filhos[1]->simb == "Message_Sequence") {
        return extrai_message_sequence(primary, no->filhos[1]);
      }
      return primary;
    } else if (no->filhos.size() >= 1) {
      // Processa apenas Primary se não houver Message_Sequence
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

Expressao* Expressao::extrai_message_sequence(Expressao* primary, No_arv_parse* no) {
  if (no == nullptr || primary == nullptr) return primary;
  
  // Message_Sequence -> Message_Chain Cascaded_Messages | ε
  if (no->simb == "Message_Sequence" && no->filhos.size() > 0) {
    // Processa o primeiro filho (Message_Chain)
    return extrai_message_chain(primary, no->filhos[0]);
  }
  
  return primary;
}

Expressao* Expressao::extrai_message_chain(Expressao* primary, No_arv_parse* no) {
  if (no == nullptr || primary == nullptr) return primary;
  
  // Message_Chain -> Unary_Message_Chain | Binary_Message_Chain | Keyword_Message
  if (no->simb == "Message_Chain" && no->filhos.size() > 0) {
    // Por simplicidade, só processamos Binary_Message_Chain
    if (no->filhos[0]->simb == "Binary_Message_Chain") {
      return extrai_binary_message_chain(primary, no->filhos[0]);
    }
  }
  
  return primary;
}

Expressao* Expressao::extrai_binary_message_chain(Expressao* primary, No_arv_parse* no) {
  if (no == nullptr || primary == nullptr) return primary;
  
  // Binary_Message_Chain -> Binary_Message_List | Binary_Message_List Keyword_Message
  if (no->simb == "Binary_Message_Chain" && no->filhos.size() > 0) {
    return extrai_binary_message_list(primary, no->filhos[0]);
  }
  
  return primary;
}

Expressao* Expressao::extrai_binary_message_list(Expressao* primary, No_arv_parse* no) {
  if (no == nullptr || primary == nullptr) return primary;
  
  // Binary_Message_List -> Binary_Message Binary_Message_List | Binary_Message
  if (no->simb == "Binary_Message_List" && no->filhos.size() > 0) {
    // Coleta todas as operações binárias em uma lista
    vector<pair<string, Expressao*>> operacoes;
    Expressao* atual = primary;
    No_arv_parse* lista_atual = no;
    
    // Percorre toda a lista de operações binárias
    while (lista_atual != nullptr && lista_atual->simb == "Binary_Message_List" && lista_atual->filhos.size() > 0) {
      // Extrai o operador e operando da operação atual
      string operador = extrai_binary_selector_from_message(lista_atual->filhos[0]);
      Expressao* operando = extrai_binary_argument_from_message(lista_atual->filhos[0]);
      
      if (!operador.empty() && operando != nullptr) {
        operacoes.push_back(make_pair(operador, operando));
      }
      
      // Avança para a próxima operação na lista
      if (lista_atual->filhos.size() > 1) {
        lista_atual = lista_atual->filhos[1];
      } else {
        break;
      }
    }
    
    // Aplica precedência: primeiro multiplicação/divisão, depois adição/subtração
    return aplica_precedencia_operadores(atual, operacoes);
  }
  
  return primary;
}

Expressao* Expressao::extrai_binary_message(Expressao* primary, No_arv_parse* no) {
  if (no == nullptr || primary == nullptr) return primary;
  
  // Binary_Message -> Binary_Selector Binary_Argument
  if (no->simb == "Binary_Message" && no->filhos.size() >= 2) {
    // Extrai o operador do Binary_Selector
    string operador = extrai_binary_selector(no->filhos[0]);
    
    // Extrai o argumento direito do Binary_Argument
    Expressao* direita = extrai_binary_argument(no->filhos[1]);
    
    if (!operador.empty() && direita != nullptr) {
      return new ExpressaoBinaria(primary, operador, direita);
    }
  }
  
  return primary;
}

string Expressao::extrai_binary_selector(No_arv_parse* no) {
  if (no == nullptr) return "";
  
  // Binary_Selector -> TOKEN_binary_selector
  if (no->simb == "Binary_Selector" && no->filhos.size() > 0) {
    if (no->filhos[0]->simb == "TOKEN_binary_selector") {
      return no->filhos[0]->dado_extra;
    }
  }
  
  return "";
}

Expressao* Expressao::extrai_binary_argument(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Binary_Argument -> Primary Unary_Message_List | Primary
  if (no->simb == "Binary_Argument" && no->filhos.size() > 0) {
    // Por simplicidade, só processa o Primary
    return extrai_expressao(no->filhos[0]);
  }
  
  return nullptr;
}

string Expressao::extrai_binary_selector_from_message(No_arv_parse* no) {
  if (no == nullptr) return "";
  
  // Binary_Message -> Binary_Selector Binary_Argument
  if (no->simb == "Binary_Message" && no->filhos.size() >= 1) {
    return extrai_binary_selector(no->filhos[0]);
  }
  
  return "";
}

Expressao* Expressao::extrai_binary_argument_from_message(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Binary_Message -> Binary_Selector Binary_Argument
  if (no->simb == "Binary_Message" && no->filhos.size() >= 2) {
    return extrai_binary_argument(no->filhos[1]);
  }
  
  return nullptr;
}

Expressao* Expressao::aplica_precedencia_operadores(Expressao* primary, const vector<pair<string, Expressao*>>& operacoes) {
  if (operacoes.empty()) {
    return primary;
  }
  
  // Para Smalltalk, não há precedência de operadores - avalia estritamente da esquerda para a direita
  Expressao* resultado = primary;
  
  for (const auto& operacao : operacoes) {
    resultado = new ExpressaoBinaria(resultado, operacao.first, operacao.second);
  }
  
  return resultado;
}
