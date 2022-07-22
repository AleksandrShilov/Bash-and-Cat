CC=gcc
CWWW=-c

s21_cat: main.o s21_cat.o
	$(CC) $^ -o s21_cat 

main.o: main.c
	$(CC) $(CWWW) $^

s21_cat.o: s21_cat.c
	$(CC) $(CWWW) $^

check_python: s21_cat.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c $^

test:
	cat -n Makefile > cat_n.txt && ./s21_cat -n Makefile > s21_cat_n.txt && diff cat_n.txt s21_cat_n.txt
	cat -b Makefile > cat_b.txt && ./s21_cat -b Makefile > s21_cat_b.txt && diff cat_b.txt s21_cat_b.txt
	cat -s Makefile > cat_s.txt && ./s21_cat -s Makefile > s21_cat_s.txt && diff cat_s.txt s21_cat_s.txt
	cat -t bytes.txt > cat_t.txt && ./s21_cat -t bytes.txt > s21_cat_t.txt && diff cat_t.txt s21_cat_t.txt
	cat -e bytes.txt > cat_t.txt && ./s21_cat -e bytes.txt > s21_cat_t.txt && diff cat_t.txt s21_cat_t.txt

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem s21_cat.c main.c

check_leaks:
	leaks -atExit -- ./s21_cat -n

clean:
	rm -rf *.o *.txt
