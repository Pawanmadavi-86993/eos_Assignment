# Write a shell script to determine whether a given number is prime or not



function msg ()
{
	echo "Hello desd"
}

msg
echo -n -e "Enter a number : "
read num

#function print_num ()
##{
#	echo "$1 $2"
#}

#print_num 10 20

function check_prime ()
{
	flag=0
	i=2
	while [ $i -lt $num ]
	do
		if [ `expr $num % $i` -eq 0 ]
		then 
			flag=1

		fi
		i=`expr $i + 1`
	done
	echo $flag
}

res=$( check_prime $num )
echo "res = $res"

if [ $res -eq 0 ]
then
	echo " prime "
else
	echo " not prime "
fi
