CPP = g++
CFLAGS = -Wall -Wextra -Werror


ttest: tree_test.cpp BST.o Node.o
	$(CPP) $(CFLAGS) -o $@ $^

BST.o: BST.cpp BST.h
	$(CPP) $(CFLAGS) -c $<

ntest: node_test.cpp Node.o
	$(CPP) $(CFLAGS) -o $@ $^

Node.o: Node.cpp Node.h
	$(CPP) $(CFLAGS) -c $<

clean:
	rm -f *.o;
	rm -f ntest; rm -f ttest;
	rm -f *~;
