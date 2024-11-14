#10. Write a program to find given number of terms in the Fibonacci series.

echo -e -n "Enter a number : "
read n

a=0
b=1

if [ $n -eq 1 ]
then
	echo "$a "
elif [ $n -eq 2 ]
then
	echo "$a $b "
else
	i=2
	echo -e -n "$a $b "
	while [ $i -lt `expr $n` ]
	do
		c=`expr $a + $b`
		a=$b
		b=$c
		echo -e -n "$c "
		i=`expr $i + 1`
	done
fi
