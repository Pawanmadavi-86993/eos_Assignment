# 9. Write a program to find the factorial of given number.

echo -e -n "Enter a number : "
read n
i=1
fact=1
while [ $i -le $n ]
do
	fact=`expr $fact \* $i`
	i=`expr $i + 1`
done

echo "$fact"
