OBJ = main.o tui.o gui.o game.o
PROG = snake
LIBS =
CXXFLAGS +=-Wall -Wextra -g

$(PROG): $(OBJ)
	$(CXX) -o $(PROG) $(OBJ) $(LIBS)

depend:
	$(CXX) -MM $(OBJ:.o=.cc) > .depend
-include .depend
