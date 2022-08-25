CC=gcc
CWWW=-c

my_cat: main.o my_cat.o
	$(CC) $^ -o my_cat 

main.o: main.c
	$(CC) $(CWWW) $^

my_cat.o: my_cat.c
	$(CC) $(CWWW) $^

check_python: my_cat.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c $^

test:
	cat -n Makefile > cat_n.txt && ./my_cat -n Makefile > my_cat_n.txt && diff cat_n.txt my_cat_n.txt
	cat -b Makefile > cat_b.txt && ./my_cat -b Makefile > my_cat_b.txt && diff cat_b.txt my_cat_b.txt
	cat -s Makefile > cat_s.txt && ./my_cat -s Makefile > my_cat_s.txt && diff cat_s.txt my_cat_s.txt
	cat -t bytes.txt > cat_t.txt && ./my_cat -t bytes.txt > my_cat_t.txt && diff cat_t.txt my_cat_t.txt
	cat -e bytes.txt > cat_t.txt && ./my_cat -e bytes.txt > my_cat_t.txt && diff cat_t.txt my_cat_t.txt

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem my_cat.c main.c

check_leaks:
	leaks -atExit -- ./my_cat -n

clean:
	rm -rf *.o *.txt
