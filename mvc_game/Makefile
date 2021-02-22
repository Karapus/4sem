OBJ = main.o tui.o
PROG = snake
LIBS =
CXXFLAGS +=-Wall -Wextra

$(PROG): $(OBJ)
	$(CXX) -o $(PROG) $(OBJ) $(LIBS)

depend:
	$(CXX) -MM $(OBJ:.o=.cc) > .depend
-include .depend
