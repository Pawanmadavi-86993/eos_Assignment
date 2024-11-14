# 5. Write a Program to find the greatest of three numbers

echo -n -e "Enter 1st number : "
read n1
echo -n -e "Enter 2nd number : "
read n2

echo -n -e "Enter 3rd number : "
read n3

if [ $n1 -gt $n2 ]
then
	if [ $n1 -gt $n3 ]
	then
		echo " $n1 is greatest "
	else
		echo " $n3 is greatest "
	fi
else
	if [ $n2 -gt $n3 ]
	then
		echo " $n2 is greatest "
	else
		echo " $n3 is greatest "
	fi
fi
