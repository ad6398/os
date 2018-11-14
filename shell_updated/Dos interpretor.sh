#!/bin/sh
# DOS interpreter. Impersonates DOS as follows:
# DOS command   UNIX equivalent   Action
# cd            cd                Change directory
# dir           ls                List directory contents
# type          cat               List file contents
# del           rm                Delete a file
# ren           mv                Rename a file
# copy          cp                Copy a file

echo "Welcome to the DOS interpreter"
echo "Type Ctrl-C to exit"

# Infinite loop
while [ "forever" ]
do
# Show DOS prompt; \c stops a new line from being issued
  echo "DOS> \c"  
# Read in user's command
  read command arg1 arg2
# Do a UNIX command corresponding to the DOS command
  case $command in
    cd)
      cd $arg1
      ;;
    dir)
      ls
      ;;
    type)
      cat $arg1
      ;;
    del)
      rm $arg1
      ;;
    ren)
      mv $arg1 $arg2
      ;;
    copy)
      cp $arg1 $arg2
      ;;
    *)
      echo "DOS does not recognise the command $command"
      ;;
  esac   
done