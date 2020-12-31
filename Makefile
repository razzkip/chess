
CFLAGS=-I$(JSON_C_DIR)/include/json-c
LDFLAGS=-L$(JSON_C_DIR)/lib -ljson-c
TESTS=test/*.c
LIB_SRC=chess.c chess.h

test: $(TESTS) $(LIB_SRC)
	gcc $(TESTS) $(LIB_SRC) -I. -Itest -o test/run_tests -g $(CFLAGS) \
		$(LTFLAGS)
	./test/run_tests

clean:
	rm -f *.o *.a *.gch test/*.o test/*.gch test/run_tests

.PHONY: test
.PHONY: clean
