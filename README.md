# Sistema de Agenda em C++ com Qt

Um sistema completo de gerenciamento de contatos com interface gráfica desenvolvido em C++ usando Qt5. O sistema permite adicionar, editar, deletar e buscar contatos com armazenamento em arquivo CSV.

## Funcionalidades

### CRUD Completo
- **Adicionar**: Criar novos contatos com todos os dados
- **Listar**: Visualizar todos os contatos em uma tabela
- **Editar**: Modificar dados de contatos existentes
- **Deletar**: Remover contatos com confirmação
- **Buscar**: Filtrar contatos por nome, telefone ou email

## Campos de Dados

Cada contato armazena as seguintes informações:

| Campo | Descrição |
|-------|-----------|
| Nome Completo | Nome do contato (obrigatório) |
| Telefone | Número de telefone |
| Email | Endereço de email |
| Idade | Idade do contato |
| Endereço | Endereço completo |
| Conta Bancária | Número da conta bancária |
| Agência | Número da agência bancária |
| PIX | Chave PIX para transferências |

## Requisitos

- Qt5 (libqt5gui5, libqt5core5a, qtbase5-dev)
- Compilador g++ com suporte a C++11
- Make

## Instalação

### 1. Instalar Dependências (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install -y qt5-qmake qtbase5-dev build-essential
```

### 2. Compilar o Projeto

```bash
cd SistemaAgenda
qmake SistemaAgenda.pro
make
```

### 3. Executar a Aplicação

```bash
./SistemaAgenda
```

## Estrutura do Projeto

```
SistemaAgenda/
├── main.cpp              # Ponto de entrada da aplicação
├── mainwindow.h          # Cabeçalho da janela principal
├── mainwindow.cpp        # Implementação da janela principal
├── contato.h             # Cabeçalho da classe Contato
├── contato.cpp           # Implementação da classe Contato
├── gerenciadorcsv.h      # Cabeçalho do gerenciador CSV
├── gerenciadorcsv.cpp    # Implementação do gerenciador CSV
├── SistemaAgenda.pro     # Arquivo de configuração Qt
└── README.md             # Este arquivo
```

## Descrição dos Arquivos

### contato.h / contato.cpp
Define a classe `Contato` que representa um contato individual com todos os seus dados. Inclui métodos para conversão para/de formato CSV.

### gerenciadorcsv.h / gerenciadorcsv.cpp
Implementa a classe `GerenciadorCSV` responsável por:
- Carregar contatos do arquivo CSV
- Salvar contatos no arquivo CSV
- Operações de CRUD (Create, Read, Update, Delete)
- Funções de busca por nome, telefone e email

### mainwindow.h / mainwindow.cpp
Implementa a interface gráfica com:
- Formulário para entrada de dados
- Tabela para visualização de contatos
- Botões para operações CRUD
- Campo de busca com filtros

### main.cpp
Ponto de entrada da aplicação que inicializa a aplicação Qt e exibe a janela principal.

## Uso da Aplicação

### Adicionar um Contato

1. Preencha os campos do formulário na parte superior
2. Clique no botão "Adicionar"
3. O contato será salvo automaticamente no arquivo CSV

### Editar um Contato

1. Clique em uma linha da tabela para selecionar o contato
2. Os dados serão carregados no formulário
3. Modifique os campos desejados
4. Clique no botão "Editar"

### Deletar um Contato

1. Clique em uma linha da tabela para selecionar o contato
2. Clique no botão "Deletar"
3. Confirme a exclusão na janela de diálogo

### Buscar um Contato

1. Selecione o tipo de busca no combo box (Nome, Telefone ou Email)
2. Digite o termo de busca
3. Clique no botão "Buscar"
4. A tabela exibirá apenas os resultados encontrados
5. Clique em "Limpar" para voltar a exibir todos os contatos

## Armazenamento de Dados

Os contatos são armazenados em um arquivo CSV localizado em:
- **Linux/Mac**: `~/Documents/contatos.csv`
- **Windows**: `Documents\contatos.csv`

O arquivo CSV possui o seguinte formato:

```
Nome,Telefone,Email,Idade,Endereco,Conta,Agencia,PIX
João Silva,(11) 98765-4321,joao@email.com,30,Rua A 123,12345-6,1234,joao@pix.com
Maria Santos,(21) 99876-5432,maria@email.com,28,Rua B 456,98765-4,5678,maria@pix.com
```

## Compilação Manual

Se preferir compilar manualmente sem usar o arquivo .pro:

```bash
# Gerar arquivos de meta-objetos
moc mainwindow.h -o moc_mainwindow.cpp

# Compilar cada arquivo
g++ -c main.cpp -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore
g++ -c mainwindow.cpp -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore
g++ -c contato.cpp -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore
g++ -c gerenciadorcsv.cpp -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore
g++ -c moc_mainwindow.cpp -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore

# Linkar
g++ -o SistemaAgenda main.o mainwindow.o contato.o gerenciadorcsv.o moc_mainwindow.o -L/usr/lib/x86_64-linux-gnu -lQt5Widgets -lQt5Gui -lQt5Core -lGL -lpthread
```

## Recursos Utilizados

- **Qt5**: Framework para desenvolvimento de interfaces gráficas
- **C++11**: Linguagem de programação
- **CSV**: Formato de armazenamento de dados

## Melhorias Futuras

- Validação de dados (email, telefone, PIX)
- Exportar contatos em diferentes formatos (PDF, Excel)
- Importar contatos de outros formatos
- Criptografia de dados sensíveis
- Sincronização com nuvem
- Backup automático
- Interface em múltiplos idiomas

## Licença

Este projeto é fornecido como está, sem garantias.

## Autor

Desenvolvido como um sistema de agenda completo em C++ com Qt5.

## Suporte

Para dúvidas ou problemas, verifique:
1. Se todas as dependências estão instaladas
2. Se o arquivo CSV está no local correto
3. Se possui permissões de leitura/escrita no diretório de documentos
