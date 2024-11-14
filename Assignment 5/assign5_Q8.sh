#8. Write a program to print the table of a given number.

echo -n -e "Enter a number : "
read n

i=1

while [ $i -le 10 ]
do
	res=`expr $i \* $n`
	echo "$res"
	i=`expr $i + 1`
done


