# 42-pipex


// valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./pipex infile "invalidcmd" "wc -l" outfile
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes 