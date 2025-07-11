CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Targets
TARGETS = puzzle_game puzzle_room_test boss_ai_test

# Default target
all: $(TARGETS)

# Puzzle game (original)
puzzle_game: src/test_puzzle.c src/puzzle.c
	$(CC) $(CFLAGS) -o $@ $^

# Puzzle room test
puzzle_room_test: src/test_puzzle_room.c src/puzzle_room.c
	$(CC) $(CFLAGS) -o $@ $^

# Boss AI test
boss_ai_test: src/test_boss_ai.c src/boss_ai.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
