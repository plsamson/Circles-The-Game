#Définitions
CC = gcc
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS = -Wall -Wextra `sdl2-config --cflags`
LDFLAGS = -lSDL2_image -lSDL2_mixer `sdl2-config --libs` -lm
EXEC = circles

# Génération de l'exécutable
$(EXEC): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(EXEC)

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

# Cible pour nettoyer les fichiers générés
.PHONY: clean
clean:
	rm -f $(OBJS) $(EXEC)
