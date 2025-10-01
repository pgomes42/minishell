# Minishell

![Made with C](https://img.shields.io/badge/Made%20with-C-blue)
![42 School](https://img.shields.io/badge/42-School-black)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![License](https://img.shields.io/badge/license-MIT-green)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
![Memory Safe](https://img.shields.io/badge/memory-safe-orange)

> 🐚 Um shell simples e robusto implementado em C como parte do currículo da 42 School.

## 📋 Índice

- [Features](#-features)
- [Arquitetura](#️-arquitetura-e-parsing)
- [Compilação](#️-compilação)
- [Uso](#-uso)
- [Testes](#-testado-com)
- [Autor](#-autor)

## 🚀 Features

### ✅ Implementações Core
- **Linha de comando interativa** com histórico usando readline
- **Built-ins completos**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Expansão de variáveis** ($USER, $HOME, $?, etc.)
- **Redirecionamentos**: `>`, `>>`, `<`
- **Heredoc**: `<<` com handling de sinais
- **Pipes**: Suporte completo a `|`
- **Aspas**: Single (') e double (") quotes
- **Gestão de sinais**: SIGINT (Ctrl+C) e SIGQUIT (Ctrl+\)

### 🧠 Arquitetura Avançada
- **AST (Abstract Syntax Tree)** para parsing de comandos
- **Tokenização inteligente** com suporte a diferentes tipos de tokens
- **Sistema de ambiente** com variáveis personalizadas
- **Gestão de memória** sem leaks (validado com Valgrind)
- **Handling de processos** com fork/exec/wait

## 🛠️ Compilação

### Pré-requisitos
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential libreadline-dev

# macOS
brew install readline
xcode-select --install
```

### Build do Projeto
```bash
# Clone o repositório
git clone <repository-url>
cd minishell

# Compile
make

# Compile para debug (com flags -g)
make debug

# Limpar objetos
make clean

# Limpar tudo
make fclean

# Recompilar
make re
```

## 🎮 Uso

### Execução Básica
```bash
./minishell

# Shell interativo inicia
minishell> echo "Hello, World!"
Hello, World!

minishell> ls | grep .c | head -5
main.c
ast.c
execute.c
tokenizing.c
expander.c

minishell> export MY_VAR="42 School"
minishell> echo $MY_VAR
42 School

minishell> exit
```

### Exemplos de Comandos Suportados
```bash
# Redirecionamentos
minishell> echo "test" > output.txt
minishell> cat < output.txt
test

# Heredoc
minishell> cat << EOF
> linha 1
> linha 2  
> EOF
linha 1
linha 2

# Pipes complexos
minishell> ls -la | grep "\.c$" | wc -l

# Built-ins
minishell> cd /tmp && pwd
/tmp

minishell> export PATH="/usr/bin:$PATH"
minishell> unset MY_VAR
```

- 🎯 Tratamento de sinais (Ctrl+C, Ctrl+D)
- 📝 Heredoc com controle de sinais
- 🎨 Aspas simples e duplas

## 🏗️ Arquitetura e Parsing

### **Tokenização**
O minishell utiliza um sistema de tokenização que identifica:
- **Comandos** e argumentos
- **Operadores** (`|`, `>`, `>>`, `<`, `<<`)
- **Delimitadores** (espaços, aspas)
- **Variáveis de ambiente** (`$VAR`)

### **AST (Abstract Syntax Tree)**
O coração do parsing é implementado através de uma **Árvore Sintática Abstrata**:

```c
typedef struct s_ast {
    char *value;          // Comando ou arquivo
    char **args;          // Argumentos do comando
    char **argv;          // Array completo para execv
    int nb_args;          // Número de argumentos
    struct s_ast *right;  // Nó filho direito
    struct s_ast *left;   // Nó filho esquerdo
    t_type type;          // Tipo do nó (COMANDO, PIPE, REDIR, etc.)
} t_ast;
```

### **Tipos de Nós AST**
- `T_COMMAND`: Comandos executáveis
- `T_PIPE`: Operador pipe (`|`)
- `T_IN_REDIR`: Redirecionamento de entrada (`<`)
- `T_OUT_SUB_REDIR`: Redirecionamento de saída (`>`)
- `T_OUT_APP_REDIR`: Redirecionamento append (`>>`)
- `T_HERODUC`: Here-document (`<<`)

### **Processo de Parsing**
1. **Lexical Analysis**: Entrada → Tokens
2. **Syntax Analysis**: Tokens → AST
3. **Expansion**: Expansão de variáveis na AST
4. **Execution**: Traversal da AST para execução

### **Exemplo de AST para `ls | grep .c > output.txt`**
```
         PIPE
        /    \
   COMMAND    OUT_REDIR
   (ls)       /        \
         COMMAND    FILE
         (grep)   (output.txt)
```

## 🔧 Implementação Técnica

### **Estruturas de Dados Principais**
```c
typedef struct s_data {
    t_list *list_token;    // Lista de tokens
    t_list *list_env;      // Variáveis de ambiente
    t_ast *ast;            // Árvore sintática
    int exit_status;       // Status de saída
    // ... outros campos
} t_data;
```

### **Tratamento de Sinais**
- **SIGINT (Ctrl+C)**: Interrompe comando atual, nova linha
- **SIGQUIT (Ctrl+\\)**: Ignorado (como bash)
- **EOF (Ctrl+D)**: Sai do shell
- **Heredoc**: Sinais específicos para não mostrar `^C`

### **Expansão de Variáveis**
- `$VAR` → Valor da variável de ambiente
- `$?` → Status de saída do último comando
- Aspas duplas: expansão ativa
- Aspas simples: expansão desabilitada

## 🧪 Testado com

### ✅ Funcionalidades Validadas
```bash
# Comandos básicos
✅ echo, cd, pwd, env, export, unset, exit
✅ ls, cat, grep, head, tail, wc
✅ comandos com argumentos e flags

# Redirecionamentos  
✅ echo "test" > file.txt
✅ cat < input.txt
✅ ls >> log.txt
✅ cat << EOF

# Pipes
✅ ls | grep .c
✅ ps aux | grep minishell | head -3
✅ echo "test" | cat | wc -l

# Variáveis
✅ export VAR="value" && echo $VAR  
✅ echo $USER $HOME $PWD
✅ echo $?

# Aspas e Escape
✅ echo 'single quotes'
✅ echo "double quotes with $USER"
✅ echo "mixed 'quotes' test"

# Casos Edge
✅ comando_inexistente (error handling)
✅ Ctrl+C durante execução
✅ Ctrl+D para sair
✅ Comandos vazios
```

### 🔍 Testes de Memória
```bash
# Sem memory leaks
valgrind --leak-check=full ./minishell

# Sem invalid reads/writes  
valgrind --tool=memcheck ./minishell

# Performance profiling
valgrind --tool=callgrind ./minishell
```

### 🏆 Compliance
- **Norminette**: ✅ Código conforme 42 Norm
- **Memory Safe**: ✅ Zero leaks detectados
- **Signal Handling**: ✅ Comportamento igual ao bash
- **Error Handling**: ✅ Códigos de saída corretos

## 📚 Recursos Técnicos

### 🔗 Links Úteis
- [42 Cursus](https://42.fr/)
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in Unix Environment](http://www.apue.com/)

### 📖 Conceitos Implementados
- **Lexical Analysis & Parsing**
- **Abstract Syntax Trees (AST)**  
- **Process Management (fork/exec/wait)**
- **Signal Handling & Terminal Control**
- **Memory Management & Leak Prevention**

---

## 👨‍💻 Autor

**pgomes** | 42 Lisboa
- 📧 Email: [pinto-go@student.42lisboa.com]
- 🐱 GitHub: [@pgomes42](https://github.com/pgomes42)
- 💼 LinkedIn: [Paulo Gomes](https://linkedin.com/in/paulo-gomes-dev)

---

<div align="center">

**⭐ Se este projeto te ajudou, deixe uma estrela! ⭐**

Feito com ❤️ e muito ☕ na **42 Lisboa**

</div>