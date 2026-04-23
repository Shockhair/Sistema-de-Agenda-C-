#ifndef GERENCIADORCSV_H
#define GERENCIADORCSV_H

#include <QList>
#include <QString>
#include "contato.h"

class GerenciadorCSV {
public:
    GerenciadorCSV(const QString &caminhoArquivo);

    // CRUD Operations
    void adicionarContato(const Contato &contato);
    QList<Contato> obterTodosContatos();
    Contato obterContatoPorIndice(int indice);
    void atualizarContato(int indice, const Contato &contato);
    void deletarContato(int indice);

    // Busca
    QList<Contato> buscarPorNome(const QString &nome);
    QList<Contato> buscarPorTelefone(const QString &telefone);
    QList<Contato> buscarPorEmail(const QString &email);

    // Arquivo
    bool salvarArquivo();
    bool carregarArquivo();

private:
    QString caminhoArquivo;
    QList<Contato> contatos;
};

#endif // GERENCIADORCSV_H
