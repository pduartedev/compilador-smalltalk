#include "Comando.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoLista.hpp"
#include "ComandoIf.hpp"
#include "ComandoWhile.hpp"
#include "Funcao.hpp"
#include "ID.hpp"
#include "Variavel.hpp"
#include <iostream>
#include "../debug-util.hpp"

vector<Comando*> Comando::extrai_lista_comandos(No_arv_parse* no) {
  // LC. 8) LC ->  9) LC -> C LC
  if (no->regra == 8) return vector<Comando*>();
  vector<Comando*> res;
  res.push_back(extrai_comando(no->filhos[0]));
  vector<Comando*> restante = extrai_lista_comandos(no->filhos[1]);
  res.insert(res.end(), restante.begin(), restante.end());
  return res;
}

Comando* Comando::extrai_comando(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Statement da gramática completa:
  // Statement -> Return_Statement | Expression
  if (no->simb == "Statement") {
    No_arv_parse* conteudo = no->filhos[0];
    
    // Return_Statement -> TOKEN_return_operator Expression (gramática completa)
    if (conteudo->simb == "Return_Statement") {
      // Por simplicidade, tratamos return como uma atribuição especial
      ComandoAtribuicao* cmd = new ComandoAtribuicao();
      cmd->esquerda = new ID();
      cmd->esquerda->nome = "$return"; // Nome especial para return
      cmd->direita = Expressao::extrai_expressao(conteudo->filhos[1]);
      return cmd;
    }
    // Expression (gramática completa)
    else if (conteudo->simb == "Expression") {
      return extrai_comando_de_expression(conteudo);
    }
  }
  
  // Expression -> Assignment | Basic_Expression (gramática completa)
  if (no->simb == "Expression") {
    return extrai_comando_de_expression(no);
  }
  
  // Assignment -> Assignment_Target TOKEN_assignment_operator Expression (gramática completa)
  if (no->simb == "Assignment") {
    ComandoAtribuicao* cmd = new ComandoAtribuicao();
    // Assignment_Target -> TOKEN_identifier (gramática completa)
    cmd->esquerda = ID::extrai_ID(no->filhos[0]->filhos[0]);
    cmd->direita = Expressao::extrai_expressao(no->filhos[2]);
    return cmd;
  }
  
  // Se não conseguir extrair, retorna nullptr
  return nullptr;
}

Comando* Comando::extrai_comando_de_expression(No_arv_parse* no) {
  if (no == nullptr) return nullptr;
  
  // Expression -> Assignment | Basic_Expression (gramática completa)
  for (auto filho : no->filhos) {
    if (filho->simb == "Assignment") {
      // Assignment -> Assignment_Target TOKEN_assignment_operator Expression (gramática completa)
      ComandoAtribuicao* cmd = new ComandoAtribuicao();
      if (filho->filhos.size() >= 3) {
        cmd->esquerda = ID::extrai_ID(filho->filhos[0]); // Assignment_Target
        cmd->direita = Expressao::extrai_expressao(filho->filhos[2]); // Expression
      }
      return cmd;
    }
    // Basic_Expression - por simplicidade, não gera comando
  }
  
  // Se for Basic_Expression, pode conter mensagens que são comandos
  // Por simplicidade, ignoramos por enquanto
  return nullptr;
}

void Comando::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "Comando generico"<< endl;
}

bool Comando::verificar_tipos_semanticos(vector<Variavel*>& variaveis, const vector<Variavel*>& parametros) {
    // Implementação padrão - retorna true
    return true;
}

void Comando::extrai_block_content(No_arv_parse* no, ComandoLista* cmd) {
  if (no == nullptr || cmd == nullptr) return;
  
  if (no->simb == "Block_Body_Content") {
    // Block_Body_Content -> Temporaries_Opt Block_Statements_Opt
    if (no->filhos.size() >= 2) {
      // Extrair variáveis temporárias
      if (no->filhos[0]->simb == "Temporaries_Opt") {
        cmd->lista_variaveis = Funcao::extrai_temporaries(no->filhos[0]);
      }
      
      // Extrair comandos
      if (no->filhos[1]->simb == "Block_Statements_Opt") {
        cmd->lista_comandos = Comando::extrai_block_statements(no->filhos[1]);
      }
    }
  }
}

vector<Comando*> Comando::extrai_block_statements(No_arv_parse* no) {
  vector<Comando*> comandos;
  
  if (no == nullptr) return comandos;
  
  if (no->simb == "Block_Statements") {
    // Block_Statements -> Statement Block_Statement_List
    if (no->filhos.size() >= 1) {
      Comando* cmd = Funcao::extrai_statement(no->filhos[0]);
      if (cmd != nullptr) {
        comandos.push_back(cmd);
      }
      
      if (no->filhos.size() >= 2) {
        vector<Comando*> resto = Comando::extrai_block_statement_list(no->filhos[1]);
        comandos.insert(comandos.end(), resto.begin(), resto.end());
      }
    }
  }
  
  return comandos;
}

vector<Comando*> Comando::extrai_block_statement_list(No_arv_parse* no) {
  vector<Comando*> comandos;
  
  if (no == nullptr) return comandos;
  
  if (no->simb == "Block_Statement_List") {
    for (auto filho : no->filhos) {
      if (filho->simb == "Statement") {
        Comando* cmd = Funcao::extrai_statement(filho);
        if (cmd != nullptr) {
          comandos.push_back(cmd);
        }
      } else if (filho->simb == "Block_Statement_List") {
        vector<Comando*> resto = Comando::extrai_block_statement_list(filho);
        comandos.insert(comandos.end(), resto.begin(), resto.end());
      }
    }
  }
  
  return comandos;
}
