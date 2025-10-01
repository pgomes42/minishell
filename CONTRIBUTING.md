# Contributing to Minishell

Thank you for your interest in contributing to this minishell implementation! 🚀

## 📋 Table of Contents

- [Getting Started](#getting-started)
- [Development Environment](#development-environment)
- [Coding Standards](#coding-standards)
- [Testing](#testing)
- [Pull Request Process](#pull-request-process)
- [Issue Reporting](#issue-reporting)

## 🚀 Getting Started

### Prerequisites

- **Compiler**: GCC or Clang with C99 support
- **Libraries**: readline development headers
- **Tools**: Make, Git, Valgrind (optional but recommended)

```bash
# Ubuntu/Debian
sudo apt-get install build-essential libreadline-dev valgrind

# macOS
brew install readline
xcode-select --install
```

### Development Setup

1. **Fork the repository**
2. **Clone your fork**
   ```bash
   git clone https://github.com/your-username/minishell.git
   cd minishell
   ```

3. **Load development environment**
   ```bash
   source .devconfig
   ```

4. **Test the build**
   ```bash
   make
   ./test_minishell.sh
   ```

## 🛠️ Development Environment

### Available Development Tools

- **`mshell`** - Run minishell directly
- **`mtest`** - Execute comprehensive test suite  
- **`mvalgrind`** - Memory leak detection
- **`mclean`** - Clean rebuild
- **`mgdb`** - Debug with GDB

### Project Structure

```
src/
├── main.c              # Entry point and main shell loop
├── ast/               # Abstract Syntax Tree implementation
├── builtins/          # Built-in commands (cd, echo, etc.)
├── env/               # Environment variable management  
├── execute/           # Command execution engine
├── expander/          # Variable expansion logic
├── tokenizing/        # Lexical analysis and tokenization
└── utils/             # Utility functions and signal handling
```

## 📏 Coding Standards

### 42 School Norm Compliance

This project follows the **42 School Norm** strictly:

- **Line length**: Maximum 80 characters
- **Function length**: Maximum 25 lines
- **Parameters**: Maximum 4 parameters per function
- **Variables**: Maximum 5 variables per function
- **Indentation**: Tabs only, no spaces
- **Naming**: Snake_case for functions, lowercase for variables

### Code Quality Guidelines

- **Memory management**: No leaks, proper error handling
- **Documentation**: Clear comments for complex logic
- **Error handling**: Graceful degradation and informative messages
- **Testing**: All new features must include tests

### Example Code Style

```c
/**
 * @brief Process command line tokens into AST
 * 
 * @param data Shell data structure containing tokens
 * @return int 1 on success, 0 on failure
 */
static int	ft_parse_token_ast(t_data *data)
{
	t_ast	*root;

	// Validate input parameters
	if (!data || !data->list_token)
		return (0);
	// Build AST from token list
	root = ft_creat_root(data);
	return (root != NULL);
}
```

## 🧪 Testing

### Running Tests

```bash
# Quick test suite
./test_minishell.sh

# Memory leak testing
mvalgrind

# Manual testing scenarios
echo "ls | grep .c" | ./minishell
echo "export TEST=42 && echo \$TEST" | ./minishell
```

### Test Categories

- **Basic Commands**: echo, pwd, env, cd
- **Pipes**: Single and multiple pipe chains
- **Redirections**: Input/output/append redirections  
- **Variable Expansion**: Environment variables and $?
- **Error Handling**: Invalid commands and syntax
- **Signal Handling**: Ctrl+C and Ctrl+D behavior

### Adding New Tests

When contributing new features, add corresponding tests to `test_minishell.sh`:

```bash
run_test "Your feature description" "command to test" expected_exit_code
```

## 🔄 Pull Request Process

### Before Submitting

1. **Ensure compliance with 42 Norm**
   ```bash
   norminette src/ include/
   ```

2. **Run full test suite**
   ```bash
   ./test_minishell.sh
   mvalgrind
   ```

3. **Check for memory leaks**
   ```bash
   valgrind --leak-check=full ./minishell
   ```

### Pull Request Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature  
- [ ] Code refactoring
- [ ] Documentation update

## Testing
- [ ] Tests pass locally
- [ ] No memory leaks detected
- [ ] 42 Norm compliant

## Checklist
- [ ] Code follows project style guidelines
- [ ] Self-review completed
- [ ] Comments added for complex logic
- [ ] Tests added for new functionality
```

## 🐛 Issue Reporting

### Bug Reports

Include the following information:

- **Environment**: OS, compiler version
- **Steps to reproduce**: Exact commands used
- **Expected behavior**: What should happen
- **Actual behavior**: What actually happens
- **Additional context**: Error messages, stack traces

### Feature Requests

- **Description**: Clear explanation of the proposed feature
- **Motivation**: Why this feature would be valuable
- **Implementation**: Any ideas for how it could be implemented

## 🤝 Code of Conduct

- Be respectful and inclusive
- Provide constructive feedback
- Focus on the code, not the person
- Help others learn and grow

## 📚 Resources

- [42 School Norm](https://github.com/42School/norminette)
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment](http://www.apue.com/)

---

Thank you for contributing to the minishell project! 🎉

For questions, feel free to open an issue or reach out to the maintainers.