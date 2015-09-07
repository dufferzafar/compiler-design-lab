SOURCE := nfa.cpp

TARGET := $(SOURCE:%.cpp=%.out)

default: clean compile run

clean:
	@rm -f $(TARGET)

compile:
	@g++ $(SOURCE) -o $(TARGET)

run:
	@./$(TARGET)
