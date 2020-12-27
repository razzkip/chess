
TESTS=test/*.c
LIB_SRC=chess.c chess.h

test: $(TESTS) $(LIB_SRC)
	gcc $(TESTS) $(LIB_SRC) -I. -Itest -o test/run_tests -g
	./test/run_tests

clean:
	rm -f *.o *.a *.gch test/*.o test/*.gch test/run_tests

.PHONY: test
.PHONY: clean
