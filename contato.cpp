#include "contato.h"

Contato::Contato()
    : nome(""), telefone(""), email(""), idade(0), endereco(""),
      conta(""), agencia(""), pix("") {}

Contato::Contato(const QString &nome, const QString &telefone, const QString &email,
                 int idade, const QString &endereco, const QString &conta,
                 const QString &agencia, const QString &pix)
    : nome(nome), telefone(telefone), email(email), idade(idade),
      endereco(endereco), conta(conta), agencia(agencia), pix(pix) {}

QString Contato::getNome() const { return nome; }
QString Contato::getTelefone() const { return telefone; }
QString Contato::getEmail() const { return email; }
int Contato::getIdade() const { return idade; }
QString Contato::getEndereco() const { return endereco; }
QString Contato::getConta() const { return conta; }
QString Contato::getAgencia() const { return agencia; }
QString Contato::getPix() const { return pix; }

void Contato::setNome(const QString &nome) { this->nome = nome; }
void Contato::setTelefone(const QString &telefone) { this->telefone = telefone; }
void Contato::setEmail(const QString &email) { this->email = email; }
void Contato::setIdade(int idade) { this->idade = idade; }
void Contato::setEndereco(const QString &endereco) { this->endereco = endereco; }
void Contato::setConta(const QString &conta) { this->conta = conta; }
void Contato::setAgencia(const QString &agencia) { this->agencia = agencia; }
void Contato::setPix(const QString &pix) { this->pix = pix; }

QString Contato::toCSV() const {
    return QString("%1,%2,%3,%4,%5,%6,%7,%8")
        .arg(nome)
        .arg(telefone)
        .arg(email)
        .arg(idade)
        .arg(endereco)
        .arg(conta)
        .arg(agencia)
        .arg(pix);
}

Contato Contato::fromCSV(const QString &linha) {
    QStringList campos = linha.split(",");
    if (campos.size() >= 8) {
        return Contato(campos[0], campos[1], campos[2], campos[3].toInt(),
                      campos[4], campos[5], campos[6], campos[7]);
    }
    return Contato();
}
