#include "Tipo.hpp"

bool Tipo::compativel_com(Tipo* outro) {
    if (this->tipo == outro->tipo) return true;
    
    // Integer é compatível com Float para operações aritméticas
    if ((this->tipo == TipoSmallTalk::INTEGER && outro->tipo == TipoSmallTalk::FLOAT) ||
        (this->tipo == TipoSmallTalk::FLOAT && outro->tipo == TipoSmallTalk::INTEGER)) {
        return true;
    }
    
    return false;
}

bool Tipo::pode_fazer_operacao_aritmetica() {
    return (tipo == TipoSmallTalk::INTEGER || tipo == TipoSmallTalk::FLOAT);
}

bool Tipo::pode_fazer_operacao_logica() {
    return (tipo == TipoSmallTalk::BOOLEAN);
}

string Tipo::to_string() {
    return nome;
}
