TIMESTAMP=`date +%F-%T`

ID="fp_$TIMESTAMP"
DAT_FILE="experiments/dats/$ID.dat"
LOG_FILE="experiments/logs/$ID.log"
INSERTS_KEYS="data/insert_$ID.txt"
QUERY_KEYS="data/query_$ID.txt"

N=1000000

#Make executables
make 

echo "# Desc: Find false positive rate as n/m varies (fix n)" >> $DAT_FILE
echo "# N=$N" >> $DAT_FILE
echo "# timestamp=$TIMESTAMP" >> $DAT_FILE
echo "#n/m  regular    hierarchal" >> $DAT_FILE

#Generate data
echo "Generating $N keys to inserts"
./gen $INSERTS_KEYS 16 $N > /dev/null

echo "Generating $N keys to query"
./gen $QUERY_KEYS 15 $N > /dev/null

echo "Beginning experiments..."
#Run experiments
for BPE in $@
do 
    #Compute bit count from pages
    M=$(($N*$BPE))
    
    #Output progress to stdout
    echo "BPE=$BPE (M=$M)"
    
    #Run experiments
    RESULT=`./bloomfilt $INSERTS_KEYS $QUERY_KEYS $M`
    echo "$RESULT" >> $LOG_FILE

    #Parse results
    PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$RESULT"`
    BITS_PER_ELEMENTS=`grep -oP 'bits per elements:\s*\K\d+(\.\d+)?' <<< "$RESULT"`
    R_FP=`grep -oP 'regular positive rate:\s*\K\d+(\.\d+)?' <<< "$RESULT"`
    H_FP=`grep -oP 'hierarchial positive rate:\s*\K\d+(\.\d+)?' <<< "$RESULT"`

    #Output results to stdout
    echo "bits per element:   $BITS_PER_ELEMENTS"
    echo "regular false-positive rate:   $R_FP"
    echo "hierarchial false-positive rate:   $H_FP"

    #Write results to row
    echo "$BITS_PER_ELEMENTS   $R_FP $H_FP" >> $DAT_FILE

    #Update plot
    ./plots/fp_plotter.bash $DAT_FILE
done

#Clean up generated data
rm $INSERTS_KEYS
rm $QUERY_KEYS