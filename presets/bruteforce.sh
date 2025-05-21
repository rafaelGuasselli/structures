# The idea of the script is to test the code for different scenarios
# We create a bruteforce algorithm that does what we are trying to achieve with the original code
# and run them several times with different random inputs to compare if there is a difference
g++ gen.cpp -O2 -o gen
g++ {$question} -O2 -o a
g++ brute.cpp -O2 -o brute
for((i = 1; i <= 100; ++i)); do
	echo $i
	./gen $i >in1
	./a < in1 >out1
	./brute <in1 >out1
	diff -w out1 out2 || break
done
