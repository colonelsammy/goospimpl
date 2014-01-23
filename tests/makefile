CC=g++
CFLAGS=-c -Wall -I../../Catch/include -I../include
LDFLAGS=
SOURCES=main.cpp \
    end_to_end_test.cpp \
    any_value_of_any_type_matcher_tests.cpp \
    any_value_of_type_matcher_tests.cpp \
    between_matcher_tests.cpp \
    counted_object_tests.cpp \
    equals_matcher_tests.cpp \
    equals_with_epsilon_matcher_tests.cpp \
    matcher_tests.cpp \
    value_holder_tests.cpp \
    with_tests.cpp
    

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tests

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE) $(EXECUTABLE).exe

