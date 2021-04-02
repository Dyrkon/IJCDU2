PATH_TO_TEXT="/home/dyrkon/code/C/IJC/IJCDU2/tests/test.txt"

PARAMS1="-n 3 $PATH_TO_TEXT"
PARAMS2="-n -5 $PATH_TO_TEXT"
PARAMS3="$PATH_TO_TEXT"
PARAMS4=""
PARAMS5="3 $PATH_TO_TEXT"

TEST1=$(valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes /home/dyrkon/code/C/IJC/IJCDU2/tail "$PARAMS1")
TEST2=$(valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes /home/dyrkon/code/C/IJC/IJCDU2/tail "$PARAMS2")
TEST3=$(valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes /home/dyrkon/code/C/IJC/IJCDU2/tail "$PARAMS3")
TEST4=$(valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes /home/dyrkon/code/C/IJC/IJCDU2/tail "$PARAMS4")
TEST5=$(valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes /home/dyrkon/code/C/IJC/IJCDU2/tail "$PARAMS5")

OUT=0

if [[ $TEST1 == *"All heap blocks were freed -- no leaks are possible"* ]]; then
  OUT=$("$OUT"+1)
fi

if [[ $TEST2 == *"All heap blocks were freed -- no leaks are possible"* ]]; then
  OUT=$("$OUT"+1)
  fi

if [[ $TEST3 == *"All heap blocks were freed -- no leaks are possible"* ]]; then
  OUT=$("$OUT"+1)
  fi

if [[ $TEST4 == *"All heap blocks were freed -- no leaks are possible"* ]]; then
  OUT=$("$OUT"+1)
  fi

if [[ $TEST5 == *"All heap blocks were freed -- no leaks are possible"* ]]; then
  OUT=$("$OUT"+1)
  fi

if [[ $OUT == 5 ]]; then
  echo "0"
  exit
  fi

echo "1"
