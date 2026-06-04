colliding-blocks: colliding-blocks.c
	gcc -o colliding-blocks colliding-blocks.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm colliding-blocks
