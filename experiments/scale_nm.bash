TIMESTAMP=`date +%F_%T`

ID="scale-nm_$TIMESTAMP"
DAT_FILE="experiments/dats/$ID.dat"
LOG_FILE="experiments/logs/$ID.log"
DATA_FILE="data/$ID.txt"

#Write header
echo "# Desc: Fix number of operations and scale bliim filter size" >> $DAT_FILE
echo "# timestamp=$TIMESTAMP" >> $DAT_FILE
echo "#n (1e6)   standard (s)    hierarchal (s)" >> $DAT_FILE

#Run experiments
for N in $@
do
    #Output progress to stdout
    echo "N=$N"

    #Generate data
    ./gen $DATA_FILE 8 $N > /dev/null

    #Run experiments
    S_RESULT=`./bloomfilt s $DATA_FILE /dev/null`
    H_RESULT=`./bloomfilt h $DATA_FILE /dev/null`

    echo "N=$N" >> $LOG_FILE
    echo "$S_RESULT" >> $LOG_FILE
    echo "$H_RESULT" >> $LOG_FILE

    #Parse results
    PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$S_RESULT"`
   
    S_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    H_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`
    S_THRU=`grep -oP 'throughput:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    H_THRU=`grep -oP 'throughput:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`
    N_IN_MIL=`grep -oP 'insert count in millions:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`

    #Output results to stdout
    echo "n (1e6) : $N_IN_MIL"
    echo "pages count:  $PAGE_COUNT"
    echo "standard:   $S_SECONDS (s)"
    echo "standard:   $S_THRU (ops/s)"
    echo "hierarchial:   $H_SECONDS (s)"
    echo "hierarchial:   $H_THRU (ops/s)"

    #Write results to row
    echo "$N_IN_MIL    $S_SECONDS    $H_SECONDS" >> $DAT_FILE

    #Update plot, ignoring errors or warnings
    ./plots/scale_nm_plotter.bash $DAT_FILE > /dev/null
done

#Clean up generated data file
rm $DATA_FILE

#Wait for DAT file to flush
sleep 1

#Final plot
./plots/scale_nm_plotter.bash $DAT_FILE

