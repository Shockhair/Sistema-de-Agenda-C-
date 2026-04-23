#ifndef CONTATO_H
#define CONTATO_H

#include <QString>
#include <QStringList>

class Contato {
public:
    Contato();
    Contato(const QString &nome, const QString &telefone, const QString &email,
            int idade, const QString &endereco, const QString &conta,
            const QString &agencia, const QString &pix);

    // Getters
    QString getNome() const;
    QString getTelefone() const;
    QString getEmail() const;
    int getIdade() const;
    QString getEndereco() const;
    QString getConta() const;
    QString getAgencia() const;
    QString getPix() const;

    // Setters
    void setNome(const QString &nome);
    void setTelefone(const QString &telefone);
    void setEmail(const QString &email);
    void setIdade(int idade);
    void setEndereco(const QString &endereco);
    void setConta(const QString &conta);
    void setAgencia(const QString &agencia);
    void setPix(const QString &pix);

    // Converter para CSV
    QString toCSV() const;
    static Contato fromCSV(const QString &linha);

private:
    QString nome;
    QString telefone;
    QString email;
    int idade;
    QString endereco;
    QString conta;
    QString agencia;
    QString pix;
};

#endif // CONTATO_H
