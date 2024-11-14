#7. Write a Program to find whether a given number is positive or negative

echo -n -e "Enter a number : "
read n

if [ $n -gt 0 ]
then 
	echo "Positive"
elif [ $n -eq 0 ]
then
	echo "Zero"
else
	echo "Negative"
fi

