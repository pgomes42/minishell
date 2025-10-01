# Minishell - Quick Start Guide

## 🚀 Instalação Rápida

```bash
# Clone o repositório
git clone https://github.com/pgomes42/minishell.git
cd minishell

# Compile
make

# Execute
./minishell
```

## 📝 Comandos Básicos

### Built-ins Disponíveis
- `echo` - Exibe texto
- `cd` - Muda diretório
- `pwd` - Mostra diretório atual
- `export` - Define variáveis
- `unset` - Remove variáveis
- `env` - Lista variáveis de ambiente
- `exit` - Sai do shell

### Exemplos de Uso

```bash
minishell> echo "Olá da 42 Luanda!"
Olá da 42 Luanda!

minishell> export NOME="Pacheco"
minishell> echo "Oi, $NOME!"
Oi, Pacheco!

minishell> ls | grep .c | head -3
main.c
ast.c
execute.c
```

## 🔧 Funcionalidades Avançadas

### Redirecionamentos
```bash
# Saída para arquivo
minishell> echo "teste" > arquivo.txt

# Entrada de arquivo
minishell> cat < arquivo.txt

# Append
minishell> echo "mais texto" >> arquivo.txt
```

### Heredoc
```bash
minishell> cat << FIM
> Esta é uma linha
> Esta é outra linha
> FIM
Esta é uma linha
Esta é outra linha
```

### Pipes
```bash
# Pipe simples
minishell> ls | wc -l

# Pipes múltiplos
minishell> ps aux | grep minishell | head -1
```

## 🏆 Características Especiais

- ✅ **Gestão de Sinais**: Ctrl+C funciona corretamente
- ✅ **Expansão de Variáveis**: $VAR, $HOME, $USER, $?
- ✅ **Aspas**: Simples (') e duplas (") implementadas
- ✅ **Tratamento de Erros**: Códigos de saída corretos
- ✅ **Memory Safe**: Zero leaks com Valgrind

## 📞 Suporte

Para dúvidas ou problemas:
- 📧 Email: pgomes42@hotmail.com
- 🐱 GitHub: [@pgomes42](https://github.com/pgomes42)

---

**Desenvolvido com ❤️ na 42 Luanda por Pacheco Gomes**