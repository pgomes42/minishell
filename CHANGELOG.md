# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-10-01

### 🎉 Initial Release

#### Added
- **Core Shell Functionality**
  - Interactive command line with readline support
  - Command history navigation
  - Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
  
- **Advanced Features**
  - Abstract Syntax Tree (AST) for command parsing
  - Environment variable expansion (`$VAR`, `$HOME`, `$?`)
  - Pipe support (`|`) with multiple pipe chains
  - Redirections: input (`<`), output (`>`), append (`>>`)
  - Heredoc implementation (`<<`) with signal handling
  - Quote parsing: single (`'`) and double (`"`) quotes
  
- **Signal Handling**
  - SIGINT (Ctrl+C) - Interrupt current command
  - SIGQUIT (Ctrl+\\) - Ignored (bash-like behavior)
  - EOF (Ctrl+D) - Exit shell gracefully
  - Special heredoc signal handling to prevent `^C` display
  
- **Developer Tools**
  - Comprehensive test suite (`test_minishell.sh`)
  - Performance benchmark script (`benchmark.sh`)
  - Development configuration (`.devconfig`)
  - Valgrind integration for memory leak detection
  - Debug and release build targets in Makefile
  
- **Documentation**
  - Detailed README with features, installation, and usage
  - CONTRIBUTING.md with development guidelines
  - QUICKSTART.md for new users
  - MIT License for open source compliance
  - Project metadata in JSON format

#### Technical Details
- **Language**: C (C99 standard)
- **Dependencies**: libreadline-dev
- **Compliance**: 42 School Norm
- **Memory Safety**: Zero leaks verified with Valgrind
- **Architecture**: Modular design with separated concerns
  - AST parsing and execution
  - Tokenization and lexical analysis
  - Environment variable management
  - Built-in command implementation
  - Signal and error handling

#### Performance
- Optimized AST traversal for command execution
- Efficient memory management with proper cleanup
- Fast tokenization and parsing algorithms
- Minimal overhead for simple commands

#### Quality Assurance
- ✅ All basic shell operations functional
- ✅ Complex pipe chains working correctly
- ✅ Memory leak-free (Valgrind verified)
- ✅ Signal handling matches bash behavior
- ✅ Error codes and messages properly implemented
- ✅ Edge cases handled (empty commands, invalid syntax)

### Security
- No hardcoded credentials or sensitive data
- Safe handling of user input and file operations
- Proper validation of command arguments
- Secure environment variable handling

### Browser Support
- Compatible with all modern terminal emulators
- Works on Linux and macOS systems
- Requires readline library support

---

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to contribute to this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **42 School** for the educational framework and project specification
- **42 Luanda** community for support and collaboration
- **GNU Bash** for inspiration and reference implementation
- **readline library** developers for the excellent input handling

---

**Developed with ❤️ by Pacheco Gomes at 42 Luanda** 🇦🇴