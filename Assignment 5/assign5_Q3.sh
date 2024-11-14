#3. Write a shell script to accept the name from the user and check whether user entered name is file or directory. If name is file display its size and if it is directory display its contents.

echo -n -e "Enter name : "
read name

if [ -f $name ]
then
	ls -s $name

elif [ -d $name ]
then
	ls $name
else
	echo "Invalid "
fi
