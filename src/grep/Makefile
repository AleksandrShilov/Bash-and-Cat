CC=gcc
CWWW=-c

s21_grep: main.o s21_grep.o
	$(CC) $^ -o s21_grep

main.o: main.c
	$(CC) $(CWWW) $^

s21_grep.o: s21_grep.c
	$(CC) $(CWWW) $^

check_python: s21_grep.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c $^

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem s21_grep.c main.c

check_valgrind:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out

test:
	grep -e rs text.txt > grep_e.txt && ./s21_grep -e rs text.txt > s21_grep_e.txt && diff grep_e.txt s21_grep_e.txt
	grep -i [s] text.txt > grep_i.txt && ./s21_grep -i [s] text.txt > s21_grep_i.txt && diff grep_i.txt s21_grep_i.txt
	grep -v [s] text.txt > grep_v.txt && ./s21_grep -v [s] text.txt > s21_grep_v.txt && diff grep_v.txt s21_grep_v.txt
	grep -c [s] text.txt > grep_c.txt && ./s21_grep -c [s] text.txt > s21_grep_c.txt && diff grep_c.txt s21_grep_c.txt
	grep -l [s] text.txt > grep_l.txt && ./s21_grep -l [s] text.txt > s21_grep_l.txt && diff grep_l.txt s21_grep_l.txt
	grep -n [s] text.txt > grep_n.txt && ./s21_grep -n [s] text.txt > s21_grep_n.txt && diff grep_n.txt s21_grep_n.txt
	grep -h [s] text.txt > grep_h.txt && ./s21_grep -h [s] text.txt > s21_grep_h.txt && diff grep_h.txt s21_grep_h.txt
	grep -o rs text.txt > grep_o.txt && ./s21_grep -o rs text.txt > s21_grep_o.txt && diff grep_o.txt s21_grep_o.txt

check_leaks:
	leaks -atExit -- ./s21_grep -e

clean:
	rm -rf *.o
