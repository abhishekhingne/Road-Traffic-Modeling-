CC=g++ 
TARGET=Car
DEP=Car.h Map.h transforms.h
OBJS= main.o Car.o Map.o transforms.o


%.o: %.cpp $(DEP)
	$(CC) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

clean:
	rm *.o

cleanAll:
	rm *.o $(TARGET)
