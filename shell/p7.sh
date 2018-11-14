echo "Enter names of two files"
read first second

cat >$first
cat >$second

chmod 300 $first
chmod 300 $second

ls -l