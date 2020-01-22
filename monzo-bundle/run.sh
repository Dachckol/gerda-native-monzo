echo $(pwd) > /data/tmp/monzo.txt
echo $(ls $(pwd)) >> /data/tmp/monzo.txt
./monzo $1 &
