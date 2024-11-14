for i in 1 2 3 4 5
do
	x=$i
	while [ $x -gt 0 ]
	do
		echo -e -n "*"
		x=`expr $x - 1`
	done
	echo " "
done
