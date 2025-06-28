#include <algorithm>
#include<vector>
#include<string>
#include<iostream>
#include <fstream>   
#include<sstream>
#include<map>
#include<stack>
using namespace std;

#include "Gramatica.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"
#include "src-gram-st/Funcao.hpp"
#include "src-gram-st/ComandoAtribuicao.hpp"
#include "src-gram-st/Analisador.hpp"


int main(int argc, char * argv[]) {
  if (argc != 3 && argc != 1) {
    cerr << "Parametros nomes dos arquivos: 1) csv com gramática e 2) csv com tabela LR1" << endl;
    return 1;
  }
  string nome_gramatica, nome_tab_lr1;
  if (argc == 1) {
    //cerr << "Valores padrao utilizados: gramatica.conf e tabela_lr1.conf" << endl;
    nome_gramatica = string("gramatica.conf");
    nome_tab_lr1 = string("tabela_lr1.conf");
  } else {
    nome_gramatica = string(argv[1]);
    nome_tab_lr1 = string(argv[2]);
  }

  ifstream arq_gramatica(nome_gramatica);
  ifstream arq_tabela_lr1(nome_tab_lr1);
  if (arq_tabela_lr1.fail() || arq_gramatica.fail()) {
    cerr << "Falha ao abrir arquivos: " << 
      ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " << 
      ((arq_tabela_lr1.fail()) ? nome_tab_lr1 : "") << endl;
    return 1;    
  }
  Parser parser(arq_gramatica, arq_tabela_lr1);
  parser.tabela.debug();
  parser.gram.debug();

  
  Arvore_parse arv = parser.executa_parse(cin);
  cerr << "Parse executado" << endl;
  arv.debug();
  Funcao* func = Funcao::extrai_funcao(arv.raiz);
  
  if (func == nullptr) {
    cerr << "Erro: Não foi possível extrair a função da árvore de parse" << endl;
    return 1;
  }
  
  func->debug();
  
  // Executar análise semântica
  Analisador ana;
  if (!ana.verificar_semantica(func)) {
    cerr << "Erro na análise semântica. Programa não pode ser executado." << endl;
    return 1;
  }
  
  cerr << "Análise semântica concluída com sucesso!" << endl;
  
  // Exemplo de chamada do analisador semantico com parâmetros de exemplo
  vector<double> parametros_passados;
  
  // Solicitar parâmetros ao usuário ou usar valores padrão
  if (func->parametros.size() > 0) {
    cout << "Digite os valores dos parâmetros (ou pressione Enter para usar valores padrão):" << endl;
    for (size_t i = 0; i < func->parametros.size(); i++) {
      cout << "Parâmetro " << func->parametros[i]->nome->nome << " (" 
           << func->parametros[i]->tipo->nome << "): ";
      string input;
      getline(cin, input);
      if (input.empty()) {
        parametros_passados.push_back(i + 1); // Valor padrão
      } else {
        parametros_passados.push_back(stod(input));
      }
    }
  }
  
  cout << "Ultimo valor calculado: ";
  double resultado = ana.calcula_ultimo_valor(func, parametros_passados);
  
  // Determinar o tipo do resultado baseado no último comando
  Tipo* tipo_resultado = Tipo::INTEGER_TYPE(); // Padrão
  if (!func->comandos.empty()) {
    // Tentar obter o tipo do último comando
    Comando* ultimo_cmd = func->comandos.back();
    
    // Se for uma atribuição, obter o tipo da expressão à direita
    ComandoAtribuicao* atribuicao = dynamic_cast<ComandoAtribuicao*>(ultimo_cmd);
    if (atribuicao != nullptr && atribuicao->direita != nullptr && atribuicao->direita->tipo_resultado != nullptr) {
      tipo_resultado = atribuicao->direita->tipo_resultado;
    }
  }
  
  ana.imprimir_resultado(resultado, tipo_resultado);
  return 0;
}
