todo: cocineros mozos reposteros
cocineros: cocineros.cpp
	g++ cocineros.cpp -o cocineros
mozos: mozos.cpp
	g++ mozos.cpp -o mozos
reposteros: reposteros.cpp
	g++ reposteros.cpp -o reposteros
clean:
	rm cocineros mozos reposteros