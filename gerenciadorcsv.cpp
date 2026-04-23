#include "gerenciadorcsv.h"
#include <QFile>
#include <QTextStream>

GerenciadorCSV::GerenciadorCSV(const QString &caminhoArquivo)
    : caminhoArquivo(caminhoArquivo) {
    carregarArquivo();
}

void GerenciadorCSV::adicionarContato(const Contato &contato) {
    contatos.append(contato);
    salvarArquivo();
}

QList<Contato> GerenciadorCSV::obterTodosContatos() {
    return contatos;
}

Contato GerenciadorCSV::obterContatoPorIndice(int indice) {
    if (indice >= 0 && indice < contatos.size()) {
        return contatos[indice];
    }
    return Contato();
}

void GerenciadorCSV::atualizarContato(int indice, const Contato &contato) {
    if (indice >= 0 && indice < contatos.size()) {
        contatos[indice] = contato;
        salvarArquivo();
    }
}

void GerenciadorCSV::deletarContato(int indice) {
    if (indice >= 0 && indice < contatos.size()) {
        contatos.removeAt(indice);
        salvarArquivo();
    }
}

QList<Contato> GerenciadorCSV::buscarPorNome(const QString &nome) {
    QList<Contato> resultado;
    for (const Contato &c : contatos) {
        if (c.getNome().toLower().contains(nome.toLower())) {
            resultado.append(c);
        }
    }
    return resultado;
}

QList<Contato> GerenciadorCSV::buscarPorTelefone(const QString &telefone) {
    QList<Contato> resultado;
    for (const Contato &c : contatos) {
        if (c.getTelefone().contains(telefone)) {
            resultado.append(c);
        }
    }
    return resultado;
}

QList<Contato> GerenciadorCSV::buscarPorEmail(const QString &email) {
    QList<Contato> resultado;
    for (const Contato &c : contatos) {
        if (c.getEmail().toLower().contains(email.toLower())) {
            resultado.append(c);
        }
    }
    return resultado;
}

bool GerenciadorCSV::salvarArquivo() {
    QFile arquivo(caminhoArquivo);
    if (!arquivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&arquivo);
    out << "Nome,Telefone,Email,Idade,Endereco,Conta,Agencia,PIX\n";
    for (const Contato &c : contatos) {
        out << c.toCSV() << "\n";
    }

    arquivo.close();
    return true;
}

bool GerenciadorCSV::carregarArquivo() {
    QFile arquivo(caminhoArquivo);
    if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&arquivo);
    QString cabecalho = in.readLine(); // Pula o cabeçalho

    contatos.clear();
    while (!in.atEnd()) {
        QString linha = in.readLine();
        if (!linha.isEmpty()) {
            contatos.append(Contato::fromCSV(linha));
        }
    }

    arquivo.close();
    return true;
}
