CXX = g++
CXXFLAGS = -Wall -pedantic
CPPFLAGS = -std=c++11
LIB = -lncurses
SRC = ./src/

all: compile doc

#COMPILE - compiles each of the files one by one and then links them together

compile: Main.o CMenu.o CUtilities.o CWindow.o CBuffer.o CTextEditor.o CNote.o CNoteStd.o CNoteToDo.o CNoteShopping.o
	$(CXX) -o smejkp13 $(CXXFLAGS) $(CPPFLAGS) *.o $(LIB)

Main.o: $(SRC)Main.cpp $(SRC)CMenu.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)Main.cpp
	
CMenu.o: $(SRC)CMenu.cpp $(SRC)CMenu.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CMenu.cpp

CUtilities.o: $(SRC)CUtilities.cpp $(SRC)CUtilities.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CUtilities.cpp

CWindow.o: $(SRC)CWindow.cpp $(SRC)CWindow.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CWindow.cpp

CBuffer.o: $(SRC)CBuffer.cpp $(SRC)CBuffer.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CBuffer.cpp

CTextEditor.o: $(SRC)CTextEditor.cpp $(SRC)CTextEditor.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CTextEditor.cpp

CNote.o: $(SRC)CNote.cpp $(SRC)CNote.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CNote.cpp

CNoteStd.o: $(SRC)CNoteStd.cpp $(SRC)CNoteStd.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CNoteStd.cpp

CNoteToDo.o: $(SRC)CNoteToDo.cpp $(SRC)CNoteToDo.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CNoteToDo.cpp

CNoteShopping.o: $(SRC)CNoteShopping.cpp $(SRC)CNoteShopping.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $(SRC)CNoteShopping.cpp

#DOC - generates the documentation and saves it into /doc
doc:
	mkdir doc;
	doxygen ./Doxyfile;

#RUN - runs the compiled program
run:
	./smejkp13

#CLEAN - undoes all changes (deletes object files, program and documentation)
clean:
	rm -f smejkp13 *.o;
	rm -rf doc;

#LINES - counts number of lines that the program has
lines:
	cat $(SRC)* | wc -l
