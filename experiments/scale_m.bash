TIMESTAMP=`date +%F-%T`

ID="scale-m_$TIMESTAMP"
DAT_FILE="experiments/dats/$ID.dat"
LOG_FILE="experiments/logs/$ID.log"
DATA_FILE="data/$ID.txt"

N=10000000

echo "# Desc: Fix number of operations and scale bliim filter size" >> $DAT_FILE
echo "# N=$N" >> $DAT_FILE
echo "# timestamp=$TIMESTAMP" >> $DAT_FILE
echo "#pages   standard (ops/s)    hierarchal (ops/s)" >> $DAT_FILE

#Generate data
echo "Generating $N keys to inserts"
./gen $DATA_FILE 32 $N > /dev/null

echo "Beginning experiments..."
#Run experiments
for P in $@
do 
    #Compute bit count from pages
    M=$(($P*4096*8))
    
    #Output progress to stdout
    echo "P=$P (M=$M)"
    
    #Run experiments
    S_RESULT=`./standard $DATA_FILE /dev/null $M`
    H_RESULT=`./hierarchical $DATA_FILE /dev/null $M`

    echo "$S_RESULT" >> $LOG_FILE
    echo "$H_RESULT" >> $LOG_FILE

    #Parse results
    PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$S_RESULT"`

    S_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    H_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`
    S_THRU=`grep -oP 'throughput:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    H_THRU=`grep -oP 'throughput:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`

    #Output results to stdout
    echo "standard:      $S_SECONDS (s)"
    echo "standard:      $S_THRU (ops/s)"
    echo "hierarchial:   $H_SECONDS (s)"
    echo "hierarchial:   $H_THRU (ops/s)"

    #Write results to row
    echo "$PAGE_COUNT   $S_THRU $H_THRU" >> $DAT_FILE

    #Update plot
    ./plots/scale_m_plotter.bash $DAT_FILE
done

#Clean up generated data
rm $DATA_FILE