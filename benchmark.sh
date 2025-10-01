#!/bin/bash

# ================================================
# Minishell Performance Benchmark Script
# ================================================
# Tests various scenarios to measure performance
# and compare with bash behavior
# ================================================

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}   MINISHELL PERFORMANCE BENCHMARK     ${NC}"
echo -e "${BLUE}========================================${NC}"
echo

# Check if minishell exists
if [ ! -f "./minishell" ]; then
    echo -e "${RED}Error: minishell not found! Run 'make' first.${NC}"
    exit 1
fi

# Function to time command execution
time_command() {
    local description="$1"
    local command="$2"
    local shell="$3"
    
    echo -e "${YELLOW}Testing:${NC} $description"
    echo -e "${BLUE}Shell:${NC} $shell"
    
    if [ "$shell" = "minishell" ]; then
        time_result=$(time (echo "$command" | ./minishell > /dev/null 2>&1) 2>&1 | grep real | awk '{print $2}')
    else
        time_result=$(time (echo "$command" | bash > /dev/null 2>&1) 2>&1 | grep real | awk '{print $2}')
    fi
    
    echo -e "${GREEN}Time:${NC} $time_result"
    echo
}

# Memory usage test
memory_test() {
    echo -e "${YELLOW}Memory Usage Test${NC}"
    echo "===================="
    
    # Test with valgrind for memory leaks
    if command -v valgrind >/dev/null 2>&1; then
        echo -e "${BLUE}Running memory leak test...${NC}"
        valgrind_output=$(echo "echo 'memory test'; exit" | valgrind --leak-check=summary --log-fd=2 ./minishell 2>&1)
        
        # Extract memory info
        if echo "$valgrind_output" | grep -q "no leaks are possible"; then
            echo -e "${GREEN}✓ No memory leaks detected${NC}"
        else
            echo -e "${RED}⚠ Memory issues detected${NC}"
        fi
    else
        echo -e "${YELLOW}Valgrind not installed, skipping memory test${NC}"
    fi
    echo
}

# Performance tests
echo -e "${YELLOW}Command Execution Tests${NC}"
echo "======================="

# Simple commands
time_command "Simple echo" "echo 'Hello World'" "minishell"
time_command "Simple echo" "echo 'Hello World'" "bash"

# Environment variables
time_command "Environment variable" "echo \$HOME" "minishell"
time_command "Environment variable" "echo \$HOME" "bash"

# Pipes
time_command "Simple pipe" "echo 'test' | cat" "minishell"
time_command "Simple pipe" "echo 'test' | cat" "bash"

# Multiple pipes
time_command "Multiple pipes" "echo 'test' | cat | cat | wc -l" "minishell"
time_command "Multiple pipes" "echo 'test' | cat | cat | wc -l" "bash"

# Redirections
time_command "Output redirection" "echo 'test' > /tmp/bench_test.txt" "minishell"
time_command "Output redirection" "echo 'test' > /tmp/bench_test.txt" "bash"

echo -e "${YELLOW}Built-in Commands Performance${NC}"
echo "============================="

# Built-ins
time_command "pwd command" "pwd" "minishell"
time_command "pwd command" "pwd" "bash"

time_command "export command" "export TEST_VAR='benchmark'" "minishell"
time_command "export command" "export TEST_VAR='benchmark'" "bash"

# Stress tests
echo -e "${YELLOW}Stress Tests${NC}"
echo "============"

# Multiple commands
echo -e "${BLUE}Testing multiple sequential commands...${NC}"
stress_command="echo 'cmd1'; echo 'cmd2'; echo 'cmd3'; echo 'cmd4'; echo 'cmd5'"
time_command "5 sequential commands" "$stress_command" "minishell"
time_command "5 sequential commands" "$stress_command" "bash"

# Complex pipe chain
echo -e "${BLUE}Testing complex pipe chain...${NC}"
complex_pipe="echo 'line1\nline2\nline3\nline4\nline5' | grep 'line' | wc -l"
time_command "Complex pipe chain" "$complex_pipe" "minishell"
time_command "Complex pipe chain" "$complex_pipe" "bash"

# Memory usage test
memory_test

# Cleanup
rm -f /tmp/bench_test.txt

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}         BENCHMARK COMPLETE             ${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}Performance testing completed!${NC}"
echo -e "${YELLOW}Note: Times may vary based on system load${NC}"