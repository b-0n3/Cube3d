FS=-fsanitize=address
all : 
	gcc  ./Tools/*.c ./Tools/GetNextLine/*.c ./Tools/libft/*.c -L/usr/X11/lib /usr/X11/lib/libmlx.a /lib/x86_64-linux-gnu/libbsd.so.0 -lXext -lX11  -lm  -I   ./Tools/Headers -I ./keys -g 
fs:
	gcc $(FS) ./Tools/*.c ./Tools/GetNextLine/*.c ./Tools/libft/*.c -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11  -lm -I ./Tools/Headers -I ./keys -g 
