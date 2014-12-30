
gcc -Wall -Werror -Wextra -O2 -c get_next_line.c

gcc -O2 test.c get_next_line.o -o gnl_test

echo "cat... > cat.txt"
time cat $@ > cat.txt

echo ""
echo "get_next_line... > gnl.txt"
time ./gnl_test $@ > gnl.txt

rm gnl_test
rm get_next_line.o
