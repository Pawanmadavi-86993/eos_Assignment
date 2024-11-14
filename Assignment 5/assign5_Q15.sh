echo -e -n "Enter two file names : "
read f1
read f2 
#cat>$f1
#cat>$f2
echo "Enter something in file $f1 "
cat>>$f1
echo "Enter something in file $f2 "
cat>>$f2

 rev $f1 | cat>>$f2

cat $f2
