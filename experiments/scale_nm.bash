TIMESTAMP=`date +%F_%T`
DAT_FILE="experiments/dats/scale-nm_$TIMESTAMP.dat"
LOG_FILE="experiments/logs/scale-nm_$TIMESTAMP.log"

#Write header
echo "# Desc: Fix number of operations and scale bliim filter size" >> $DAT_FILE
echo "# N=$N" >> $DAT_FILE
echo "# timestamp=$TIMESTAMP" >> $DAT_FILE
echo "#n   regular (seconds)    hierarchal (seconds)" >> $DAT_FILE

#Run experiments
for N in $@
do
    #Output progress to stdout
    echo N=$N

    #Generate data
    ./gen data/inserts 8 $N > /dev/null
    ./gen data/queries 8 $N > /dev/null

    #Run experiments
    RESULT=`./bloomfilt data/inserts data/queries`
    echo "N=$N" >> $LOG_FILE
    echo "$RESULT" >> $LOG_FILE

    #Parse results
    NUM_INSERTS=`grep -oP 'insert count:\s*\K\d+' <<< "$RESULT"`
    NUM_QUERIES=`grep -oP 'query count:\s*\K\d+' <<< "$RESULT"`

    PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$RESULT"`

    R_SECONDS=`grep -oP 'regular seconds:\s*\K\d+(\.\d+)?' <<< "$RESULT"`
    H_SECONDS=`grep -oP 'hierarchial seconds:\s*\K\d+(\.\d+)?' <<< "$RESULT"`

    #Output results to stdout
    echo "regular:   $R_SECONDS (s)"
    echo "hierarchial:   $H_SECONDS (s)"

    #Write results to row
    echo "$NUM_INSERTS,$NUM_QUERIES,$PAGE_COUNT,$R_SECONDS,$H_SECONDS" >> $DAT_FILE

    #Update plot
    ./plots/scale_nm_plotter.bash $DAT_FILE
done

