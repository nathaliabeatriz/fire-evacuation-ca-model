EXEC = exec.exe
all:
	g++ -Ofast -Wall -o $(EXEC) *.cpp
	./$(EXEC)

build:
	g++ -Ofast -o $(EXEC) *.cpp

run:
	./$(EXEC)

val:
	g++ -g -O1 -Wall -o $(EXEC) *.cpp
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -q ./exec.exe

save:
	g++ -O2 -o $(EXEC) *.cpp
	.\\$(EXEC) > $(OUT_FILE)