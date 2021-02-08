FS=-fsanitize=address
LIBFT=./src/libft/*.c
LIBFTINC = ./src/libft/
PARSER=./src/parser/srcs/*.c
PARSERINC=./src/parser/includes/
GNL=./src/getnextline/*.c
LINEINC=./src/line/includes/
AL=./src/arraylist/srcs/*.c
ALINC=./src/arraylist/includes/
PLAYER=./src/player/srcs/*.c
PLAYERINC=./src/player/includes/
UTILS=./src/utils/srcs/*.c
UTILSINC=./src/utils/includes/
INC= ./src/headers/
SRC = ./src/*.c
KEYS= ./src/keys/
RAY= ./src/ray/srcs/*.c
RAYINC= ./src/ray/includes/
GAME= ./src/game/srcs/*.c
GAMEINC=./src/game/includes/

FLAGS = -Wall -Wextra -Werror

# all : 
# 	gcc  ./Tools/*.c ./Tools/GetNextLine/*.c ./Tools/libft/*.c -L/usr/X11/lib /usr/X11/lib/libmlx.a /lib/x86_64-linux-gnu/libbsd.so.0 -lXext -lX11  -lm  -I   ./Tools/Headers -I ./keys -g 
# fs:
# 	gcc $(FS) ./Tools/*.c ./Tools/GetNextLine/*.c ./Tools/libft/*.c -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11  -lm -I ./Tools/Headers -I ./keys -g 
me:
	gcc   -lmlx -framework OpenGL -framework AppKit $(SRC) $(GAME) $(RAY) $(LIBFT) $(PARSER) $(GNL) $(AL) $(PLAYER) $(UTILS)  -I $(GAMEINC) -I $(LIBFTINC) -I $(ALINC)  -I $(UTILSINC) -I $(PARSERINC)   -I $(INC)  -I $(LINEINC) -I $(PLAYERINC)  -I $(KEYS) -I $(RAYINC) -g -O3
bonus:
	gcc    -D BONUS=1  -lmlx -framework OpenGL -framework AppKit $(SRC) $(GAME) $(RAY) $(LIBFT) $(PARSER) $(GNL) $(AL) $(PLAYER) $(UTILS) -I $(GAMEINC)  -I $(LIBFTINC) -I $(ALINC)  -I $(UTILSINC) -I $(PARSERINC)   -I $(INC)  -I $(LINEINC) -I $(PLAYERINC)  -I $(KEYS) -I $(RAYINC)   -g -O3
