#!/bin/bash

# Script para compilar o analisador léxico de Smalltalk

# Cria os diretórios necessários caso não existam
mkdir -p src/main/java/lexical
mkdir -p target/classes

# Executa o JavaCC para gerar os arquivos Java
javacc -OUTPUT_DIRECTORY=src/main/java/lexical src/main/jj/SmallTalk.jj

# Compila os arquivos Java gerados
javac -d target/classes src/main/java/lexical/*.java

echo "Compilação concluída!"
