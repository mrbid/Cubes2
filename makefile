all:
	gcc main.c glad_gl.c -Ofast -lglfw -lm -o cubes2

install:
	cp cubes2 $(DESTDIR)

uninstall:
	rm $(DESTDIR)/cubes2

clean:
	rm cubes2