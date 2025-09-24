# Minishell

![Made with C](https://img.shields.io/badge/Made%20with-C-blue)
![42 School](https://img.shields.io/badge/42-School-black)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)

Um shell simples implementado em C como parte do currículo da 42 School.

## ✨ Features

- 🔧 Builtins: `cd`, `echo`, `env`, `export`, `pwd`, `unset`, `exit`
- 🚰 Pipes e redirecionamentos (`|`, `>`, `>>`, `<`, `<<`)
- 🔀 Expansão de variáveis de ambiente (`$VAR`, `$?`)
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

## 🛠️ Compilação

```bash
make
```

## 🚀 Uso

```bash
./minishell
```

## 📋 Testado com

- ✅ Comandos básicos (ls, cat, grep, etc.)
- ✅ Pipes complexos
- ✅ Redirecionamentos múltiplos
- ✅ Tratamento de erros
- ✅ Expansão de variáveis

## 👨‍💻 Autor

Feito com ❤️ por [pgomes42](https://github.com/pgomes42)