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