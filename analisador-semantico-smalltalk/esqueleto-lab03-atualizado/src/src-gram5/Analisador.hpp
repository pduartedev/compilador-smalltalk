#ifndef _ANALISADOR_HPP_
#define _ANALISADOR_HPP_
#include "Funcao.hpp"
#include <vector>
#include <map>
using namespace std;

class Analisador {
public:
  int calcula_ultimo_valor(Funcao *f, const vector<int> &params);
};
  
#endif
