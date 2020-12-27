
TESTS=test/test_board_operations.c
LIB_SRC=chess.c chess.h
TEST_SRC=test/test.c test/test.h

test: $(TESTS) $(TEST_SRC) $(LIB_SRC)
	gcc $(TESTS) $(TEST_SRC) $(LIB_SRC) -I. -Itest -o test/tests
	./test/tests

clean:
	rm -f *.o *.a *.gch test/*.o test/*.gch test/tests

.PHONY: test
.PHONY: clean
