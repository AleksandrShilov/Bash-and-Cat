CC=gcc
CWWW=-c

my_grep: main.o my_grep.o
	$(CC) $^ -o my_grep

main.o: main.c
	$(CC) $(CWWW) $^

my_grep.o: my_grep.c
	$(CC) $(CWWW) $^

check_python: my_grep.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c $^

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem my_grep.c main.c

check_valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out

test:
	grep -e rs text.txt > grep_e.txt && ./my_grep -e rs text.txt > my_grep_e.txt && diff grep_e.txt my_grep_e.txt
	grep -i [s] text.txt > grep_i.txt && ./my_grep -i [s] text.txt > my_grep_i.txt && diff grep_i.txt my_grep_i.txt
	grep -v [s] text.txt > grep_v.txt && ./my_grep -v [s] text.txt > my_grep_v.txt && diff grep_v.txt my_grep_v.txt
	grep -c [s] text.txt > grep_c.txt && ./my_grep -c [s] text.txt > my_grep_c.txt && diff grep_c.txt my_grep_c.txt
	grep -l [s] text.txt > grep_l.txt && ./my_grep -l [s] text.txt > my_grep_l.txt && diff grep_l.txt my_grep_l.txt
	grep -n [s] text.txt > grep_n.txt && ./my_grep -n [s] text.txt > my_grep_n.txt && diff grep_n.txt my_grep_n.txt
	grep -h [s] text.txt > grep_h.txt && ./my_grep -h [s] text.txt > my_grep_h.txt && diff grep_h.txt my_grep_h.txt
	grep -o rs text.txt > grep_o.txt && ./my_grep -o rs text.txt > my_grep_o.txt && diff grep_o.txt my_grep_o.txt

check_leaks:
	leaks -atExit -- ./my_grep -e

clean:
	rm -rf *.o
