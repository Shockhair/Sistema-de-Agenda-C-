#!/bin/bash

# Script de compilação para o Sistema de Agenda

echo "========================================"
echo "Sistema de Agenda - Script de Compilação"
echo "========================================"
echo ""

# Verificar se qmake está instalado
if ! command -v qmake &> /dev/null; then
    echo "Erro: qmake não encontrado. Por favor, instale Qt5:"
    echo "  sudo apt-get install qt5-qmake qtbase5-dev"
    exit 1
fi

# Verificar se make está instalado
if ! command -v make &> /dev/null; then
    echo "Erro: make não encontrado. Por favor, instale build-essential:"
    echo "  sudo apt-get install build-essential"
    exit 1
fi

echo "Limpando arquivos anteriores..."
make clean 2>/dev/null

echo "Gerando arquivo Makefile com qmake..."
qmake SistemaAgenda.pro

echo "Compilando o projeto..."
make

if [ -f "SistemaAgenda" ]; then
    echo ""
    echo "========================================"
    echo "Compilação concluída com sucesso!"
    echo "========================================"
    echo ""
    echo "Para executar a aplicação, digite:"
    echo "  ./SistemaAgenda"
    echo ""
else
    echo ""
    echo "Erro: Compilação falhou!"
    exit 1
fi
