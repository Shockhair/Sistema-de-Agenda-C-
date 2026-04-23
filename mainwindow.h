#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include "gerenciadorcsv.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void adicionarContato();
    void editarContato();
    void deletarContato();
    void buscar();
    void limparBusca();
    void carregarTabela();
    void selecionarLinha(int row, int column);

private:
    void criarInterface();
    void conectarSinais();
    void validarEPreencherFormulario();

    // Widgets
    QTableWidget *tabela;
    QLineEdit *inputNome;
    QLineEdit *inputTelefone;
    QLineEdit *inputEmail;
    QLineEdit *inputIdade;
    QLineEdit *inputEndereco;
    QLineEdit *inputConta;
    QLineEdit *inputAgencia;
    QLineEdit *inputPix;

    QLineEdit *campoBusca;
    QComboBox *comboBusca;

    QPushButton *btnAdicionar;
    QPushButton *btnEditar;
    QPushButton *btnDeletar;
    QPushButton *btnBuscar;
    QPushButton *btnLimpar;

    GerenciadorCSV *gerenciador;
    int contatoSelecionado;
};

#endif // MAINWINDOW_H
