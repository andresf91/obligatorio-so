todo: cocineros mozos reposteros
cocineros: cocineros.cpp
	g++ -pthread cocineros.cpp -o cocineros
mozos: mozos.cpp
	g++ -pthread mozos.cpp -o mozos
reposteros: reposteros.cpp
	g++ -pthread reposteros.cpp -o reposteros
clean:
	rm cocineros mozos reposteros