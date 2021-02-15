FS=-fsanitize=address
NAME= cub3D
MLX= -lmlx -framework OpenGL -framework AppKit -g
# includes

LIBFTINC = ./src/libft/includes/
PARSERINC=./src/parser/includes/
LINEINC=./src/line/includes/
ALINC=./src/arraylist/includes/
PLAYERINC=./src/player/includes/
UTILSINC=./src/utils/includes/
INPUTINC= ./src/input/includes
RAYINC= ./src/ray/includes/
GAMEINC=./src/game/includes/
VECTORINC=./src/vector/includes/

FLAGS = -Wall -Wextra -Werror

# sources
ARRAYLIST=./src/arraylist/libarraylist.a
LIBFT=./src/libft/libft.a
GAME = 		./src/game/srcs/game_exit.c \
			./src/game/srcs/game_free.c \
			./src/game/srcs/game_init.c \
			./src/game/srcs/game_save.c 
PLAYER =  	./src/player/srcs/floor_cast_render.c \
			./src/player/srcs/line_distance.c \
			./src/player/srcs/player_check_collision.c \
			./src/player/srcs/player_free.c \
			./src/player/srcs/player_init.c \
			./src/player/srcs/player_render.c \
			./src/player/srcs/player_update.c \
			./src/player/srcs/render_sprite_texture.c \
			./src/player/srcs/secret_door_update.c \
			./src/player/srcs/sprite_render.c
GNL = 		./src/getnextline/get_next_line.c \
			./src/getnextline/get_next_line_utils.c
GRAPHICS = 	./src/graphics/graphics.c \
			./src/graphics/image.c    \
			./src/graphics/texture.c  
INPUT = 	./src/input/srcs/input.c \
			./src/input/srcs/mouse_events.c
LINE = 		./src/line/srcs/free_line.c

PARSER = 	./src/parser/srcs/map_checker.c \
			./src/parser/srcs/parse_ea_tex.c \
			./src/parser/srcs/parse_floor.c \
			./src/parser/srcs/parse_map.c \
			./src/parser/srcs/parse_no_tex.c \
			./src/parser/srcs/parse_so_tex.c \
			./src/parser/srcs/parse_sprite_bonus.c \
			./src/parser/srcs/parse_sprites.c \
			./src/parser/srcs/parse_sprites_tex.c \
			./src/parser/srcs/parse_we_tex.c \
			./src/parser/srcs/parser.c \
			./src/parser/srcs/parser_ceilling.c \
			./src/parser/srcs/parser_init.c \
			./src/parser/srcs/parser_parse_file.c \
			./src/parser/srcs/parser_parse_file_c.c \
			./src/parser/srcs/parser_read.c \
			./src/parser/srcs/parser_res.c \
			./src/parser/srcs/parser_verify.c \
			./src/parser/srcs/parser_verify_c.c \
			./src/parser/srcs/parser_verify_cc.c \
			./src/parser/srcs/parser_walls_e.c \
			./src/parser/srcs/parser_walls_n.c \
			./src/parser/srcs/parser_walls_s.c \
			./src/parser/srcs/parser_walls_w.c \
			./src/parser/srcs/sprite_tex_parser.c \
			./src/parser/srcs/token.c \
			./src/parser/srcs/token_free.c \
			./src/parser/srcs/token_put_token.c

RAY = 		./src/ray/srcs/ray_cast.c \
			./src/ray/srcs/ray_free.c \
			./src/ray/srcs/ray_init.c \
			./src/ray/srcs/ray_intersection.c \
			./src/ray/srcs/ray_intersection_calculation.c \
			./src/ray/srcs/ray_len.c \
			./src/ray/srcs/ray_render.c \
			./src/ray/srcs/ray_render_wall.c \
			./src/ray/srcs/ray_tex_col.c \
			./src/ray/srcs/ray_update.c \
			./src/ray/srcs/sprites.c \
			./src/ray/srcs/wall_init.c 
UTILS = 	./src/utils/srcs/ft_check_file.c \
			./src/utils/srcs/ft_put_error.c \
			./src/utils/srcs/ft_split_property.c \
			./src/utils/srcs/get_current_time.c
VECTOR =	./src/vector/srcs/vector_calculation.c \
			./src/vector/srcs/vector_init.c


INC= ./src/headers/  \
	-I $(LIBFTINC)		 \
	-I $(VECTORINC)		 \
	-I $(PARSERINC)	 \
	-I $(LINEINC)		 \
	-I $(ALINC)		 \
	-I $(PLAYERINC)	 \
	-I $(UTILSINC)		 \
	-I $(INPUTINC)		 \
	-I $(RAYINC)		 \
	-I $(GAMEINC)		

SRC= ./src/main.c  \
	$(ARRAYLIST)  \
	$(LIBFT)  	 \
	$(GAME)		 \
	$(PLAYER)		 \
	$(GNL)		 \
	$(GRAPHICS)		 \
	$(INPUT)		 \
	$(LINE)		 \
	$(PARSER)		 \
	$(RAY)		 \
	$(UTILS)		 \
	$(VECTOR)

RELINK = relink

all: arraylist libft $(NAME)

libft:
		$(MAKE) -C ./src/libft/
arraylist:
		$(MAKE) -C ./src/arraylist/

$(NAME): 
	gcc  $(FLAGS)  $(MLX) $(SRC) -I $(INC) -o $(NAME) -O3


clean: libftclean arraylistclean
	rm -f *.o

fclean: clean	libftfclean arraylistfclean
	rm -f $(NAME)	
	rm -f includes/*.*.gch	

re: fclean all

libftclean:
	$(MAKE) clean  -C ./src/libft/ 
libftfclean:
	$(MAKE) fclean  -C ./src/libft/ 
arraylistclean:
	$(MAKE) clean -C ./src/arraylist/
arraylistfclean:
	$(MAKE) fclean -C ./src/arraylist/

bonus: arraylist libft 	
	gcc -D BONUS=1  $(FLAGS) $(MLX) $(SRC) -I $(INC) -o $(NAME)
