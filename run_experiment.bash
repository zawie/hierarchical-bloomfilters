for N in 50000 500000 500000 5000000 50000000
do
    ./gen data/inserts 8 $N
    ./gen data/queries 8 $N

    ./bloomfilt data/inserts data/queries
done