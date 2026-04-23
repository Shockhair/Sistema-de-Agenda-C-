#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), contatoSelecionado(-1) {
    
    // Inicializar gerenciador
    QString caminhoArquivo = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/contatos.csv";
    gerenciador = new GerenciadorCSV(caminhoArquivo);

    setWindowTitle("Sistema de Agenda");
    setGeometry(100, 100, 1200, 700);

    criarInterface();
    conectarSinais();
    carregarTabela();
}

MainWindow::~MainWindow() {
    delete gerenciador;
}

void MainWindow::criarInterface() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(centralWidget);

    // ===== SEÇÃO DE FORMULÁRIO =====
    QGroupBox *grupoFormulario = new QGroupBox("Dados do Contato", this);
    QVBoxLayout *layoutFormulario = new QVBoxLayout(grupoFormulario);

    // Primeira linha
    QHBoxLayout *linha1 = new QHBoxLayout();
    linha1->addWidget(new QLabel("Nome Completo:"));
    inputNome = new QLineEdit();
    linha1->addWidget(inputNome);
    linha1->addWidget(new QLabel("Telefone:"));
    inputTelefone = new QLineEdit();
    linha1->addWidget(inputTelefone);
    layoutFormulario->addLayout(linha1);

    // Segunda linha
    QHBoxLayout *linha2 = new QHBoxLayout();
    linha2->addWidget(new QLabel("Email:"));
    inputEmail = new QLineEdit();
    linha2->addWidget(inputEmail);
    linha2->addWidget(new QLabel("Idade:"));
    inputIdade = new QLineEdit();
    inputIdade->setMaximumWidth(80);
    linha2->addWidget(inputIdade);
    layoutFormulario->addLayout(linha2);

    // Terceira linha
    QHBoxLayout *linha3 = new QHBoxLayout();
    linha3->addWidget(new QLabel("Endereço:"));
    inputEndereco = new QLineEdit();
    linha3->addWidget(inputEndereco);
    layoutFormulario->addLayout(linha3);

    // Quarta linha
    QHBoxLayout *linha4 = new QHBoxLayout();
    linha4->addWidget(new QLabel("Conta Bancária:"));
    inputConta = new QLineEdit();
    linha4->addWidget(inputConta);
    linha4->addWidget(new QLabel("Agência:"));
    inputAgencia = new QLineEdit();
    inputAgencia->setMaximumWidth(100);
    linha4->addWidget(inputAgencia);
    layoutFormulario->addLayout(linha4);

    // Quinta linha
    QHBoxLayout *linha5 = new QHBoxLayout();
    linha5->addWidget(new QLabel("PIX:"));
    inputPix = new QLineEdit();
    linha5->addWidget(inputPix);
    layoutFormulario->addLayout(linha5);

    layoutPrincipal->addWidget(grupoFormulario);

    // ===== SEÇÃO DE BOTÕES =====
    QHBoxLayout *layoutBotoes = new QHBoxLayout();
    btnAdicionar = new QPushButton("Adicionar");
    btnEditar = new QPushButton("Editar");
    btnDeletar = new QPushButton("Deletar");
    layoutBotoes->addWidget(btnAdicionar);
    layoutBotoes->addWidget(btnEditar);
    layoutBotoes->addWidget(btnDeletar);
    layoutBotoes->addStretch();
    layoutPrincipal->addLayout(layoutBotoes);

    // ===== SEÇÃO DE BUSCA =====
    QGroupBox *grupoBusca = new QGroupBox("Buscar Contato", this);
    QHBoxLayout *layoutBusca = new QHBoxLayout(grupoBusca);
    layoutBusca->addWidget(new QLabel("Buscar por:"));
    comboBusca = new QComboBox();
    comboBusca->addItem("Nome");
    comboBusca->addItem("Telefone");
    comboBusca->addItem("Email");
    layoutBusca->addWidget(comboBusca);
    campoBusca = new QLineEdit();
    layoutBusca->addWidget(campoBusca);
    btnBuscar = new QPushButton("Buscar");
    btnLimpar = new QPushButton("Limpar");
    layoutBusca->addWidget(btnBuscar);
    layoutBusca->addWidget(btnLimpar);
    layoutPrincipal->addWidget(grupoBusca);

    // ===== SEÇÃO DE TABELA =====
    tabela = new QTableWidget();
    tabela->setColumnCount(8);
    tabela->setHorizontalHeaderLabels({"Nome", "Telefone", "Email", "Idade", 
                                       "Endereço", "Conta", "Agência", "PIX"});
    tabela->horizontalHeader()->setStretchLastSection(true);
    tabela->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabela->setSelectionMode(QAbstractItemView::SingleSelection);
    layoutPrincipal->addWidget(tabela);

    centralWidget->setLayout(layoutPrincipal);
}

void MainWindow::conectarSinais() {
    connect(btnAdicionar, &QPushButton::clicked, this, &MainWindow::adicionarContato);
    connect(btnEditar, &QPushButton::clicked, this, &MainWindow::editarContato);
    connect(btnDeletar, &QPushButton::clicked, this, &MainWindow::deletarContato);
    connect(btnBuscar, &QPushButton::clicked, this, &MainWindow::buscar);
    connect(btnLimpar, &QPushButton::clicked, this, &MainWindow::limparBusca);
    connect(tabela, &QTableWidget::cellClicked, this, &MainWindow::selecionarLinha);
}

void MainWindow::adicionarContato() {
    if (inputNome->text().isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, preencha o nome do contato!");
        return;
    }

    Contato novoContato(
        inputNome->text(),
        inputTelefone->text(),
        inputEmail->text(),
        inputIdade->text().toInt(),
        inputEndereco->text(),
        inputConta->text(),
        inputAgencia->text(),
        inputPix->text()
    );

    gerenciador->adicionarContato(novoContato);
    carregarTabela();
    
    // Limpar formulário
    inputNome->clear();
    inputTelefone->clear();
    inputEmail->clear();
    inputIdade->clear();
    inputEndereco->clear();
    inputConta->clear();
    inputAgencia->clear();
    inputPix->clear();
    contatoSelecionado = -1;

    QMessageBox::information(this, "Sucesso", "Contato adicionado com sucesso!");
}

void MainWindow::editarContato() {
    if (contatoSelecionado < 0) {
        QMessageBox::warning(this, "Erro", "Por favor, selecione um contato para editar!");
        return;
    }

    if (inputNome->text().isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, preencha o nome do contato!");
        return;
    }

    Contato contatoAtualizado(
        inputNome->text(),
        inputTelefone->text(),
        inputEmail->text(),
        inputIdade->text().toInt(),
        inputEndereco->text(),
        inputConta->text(),
        inputAgencia->text(),
        inputPix->text()
    );

    gerenciador->atualizarContato(contatoSelecionado, contatoAtualizado);
    carregarTabela();
    
    // Limpar formulário
    inputNome->clear();
    inputTelefone->clear();
    inputEmail->clear();
    inputIdade->clear();
    inputEndereco->clear();
    inputConta->clear();
    inputAgencia->clear();
    inputPix->clear();
    contatoSelecionado = -1;

    QMessageBox::information(this, "Sucesso", "Contato atualizado com sucesso!");
}

void MainWindow::deletarContato() {
    if (contatoSelecionado < 0) {
        QMessageBox::warning(this, "Erro", "Por favor, selecione um contato para deletar!");
        return;
    }

    QMessageBox::StandardButton resposta = QMessageBox::question(this, "Confirmar",
        "Tem certeza que deseja deletar este contato?",
        QMessageBox::Yes | QMessageBox::No);

    if (resposta == QMessageBox::Yes) {
        gerenciador->deletarContato(contatoSelecionado);
        carregarTabela();
        
        inputNome->clear();
        inputTelefone->clear();
        inputEmail->clear();
        inputIdade->clear();
        inputEndereco->clear();
        inputConta->clear();
        inputAgencia->clear();
        inputPix->clear();
        contatoSelecionado = -1;

        QMessageBox::information(this, "Sucesso", "Contato deletado com sucesso!");
    }
}

void MainWindow::buscar() {
    QString termoBusca = campoBusca->text();
    if (termoBusca.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Por favor, digite um termo para buscar!");
        return;
    }

    QList<Contato> resultados;
    if (comboBusca->currentText() == "Nome") {
        resultados = gerenciador->buscarPorNome(termoBusca);
    } else if (comboBusca->currentText() == "Telefone") {
        resultados = gerenciador->buscarPorTelefone(termoBusca);
    } else if (comboBusca->currentText() == "Email") {
        resultados = gerenciador->buscarPorEmail(termoBusca);
    }

    tabela->setRowCount(resultados.size());
    for (int i = 0; i < resultados.size(); ++i) {
        tabela->setItem(i, 0, new QTableWidgetItem(resultados[i].getNome()));
        tabela->setItem(i, 1, new QTableWidgetItem(resultados[i].getTelefone()));
        tabela->setItem(i, 2, new QTableWidgetItem(resultados[i].getEmail()));
        tabela->setItem(i, 3, new QTableWidgetItem(QString::number(resultados[i].getIdade())));
        tabela->setItem(i, 4, new QTableWidgetItem(resultados[i].getEndereco()));
        tabela->setItem(i, 5, new QTableWidgetItem(resultados[i].getConta()));
        tabela->setItem(i, 6, new QTableWidgetItem(resultados[i].getAgencia()));
        tabela->setItem(i, 7, new QTableWidgetItem(resultados[i].getPix()));
    }
}

void MainWindow::limparBusca() {
    campoBusca->clear();
    carregarTabela();
}

void MainWindow::carregarTabela() {
    QList<Contato> contatos = gerenciador->obterTodosContatos();
    tabela->setRowCount(contatos.size());

    for (int i = 0; i < contatos.size(); ++i) {
        tabela->setItem(i, 0, new QTableWidgetItem(contatos[i].getNome()));
        tabela->setItem(i, 1, new QTableWidgetItem(contatos[i].getTelefone()));
        tabela->setItem(i, 2, new QTableWidgetItem(contatos[i].getEmail()));
        tabela->setItem(i, 3, new QTableWidgetItem(QString::number(contatos[i].getIdade())));
        tabela->setItem(i, 4, new QTableWidgetItem(contatos[i].getEndereco()));
        tabela->setItem(i, 5, new QTableWidgetItem(contatos[i].getConta()));
        tabela->setItem(i, 6, new QTableWidgetItem(contatos[i].getAgencia()));
        tabela->setItem(i, 7, new QTableWidgetItem(contatos[i].getPix()));
    }
}

void MainWindow::selecionarLinha(int row, int column) {
    Q_UNUSED(column);
    
    contatoSelecionado = row;
    Contato contato = gerenciador->obterContatoPorIndice(row);

    inputNome->setText(contato.getNome());
    inputTelefone->setText(contato.getTelefone());
    inputEmail->setText(contato.getEmail());
    inputIdade->setText(QString::number(contato.getIdade()));
    inputEndereco->setText(contato.getEndereco());
    inputConta->setText(contato.getConta());
    inputAgencia->setText(contato.getAgencia());
    inputPix->setText(contato.getPix());
}
