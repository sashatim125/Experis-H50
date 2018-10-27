
TEST_FILE=stack_test.out

INCLUDES=../stack.h ../../mu_test.h

CC=gcc

CFLAGS= -Wall -Wconversion -pedantic -ansi -Werror -I../ -I../../ 

.PHONEY:run clean

$(TEST_FILE):$(INCLUDES) $(patsubst %.out,%.c,$@)
	$(CC) $(patsubst %.out,%.c,$@) $(CFLAGS) -ldl -o $@ 


run:$(TEST_FILE)
	./$(TEST_FILE)

clean:
	rm $(TEST_FILE)


