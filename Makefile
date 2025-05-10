# Default target to build the executable
weatherData: main.c weather.c
	gcc -o weatherData main.c weather.c

# Clean up compiled files
clean:
	rm -f weatherData
	rm -f *.o

# Run the program
run: weatherData
	./weatherData
