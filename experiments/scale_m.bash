TIMESTAMP=`date +%F-%T`

ID="scale-m_$TIMESTAMP"
DAT_FILE="experiments/dats/$ID.dat"
LOG_FILE="experiments/logs/$ID.log"
DATA_FILE="data/$ID.txt"

N=10000000

#Make executables
make 

echo "# Desc: Fix number of operations and scale bliim filter size" >> $DAT_FILE
echo "# N=$N" >> $DAT_FILE
echo "# timestamp=$TIMESTAMP" >> $DAT_FILE
echo "#pages   regular (seconds)    hierarchal (seconds)" >> $DAT_FILE

#Generate data
echo "Generating $N keys to inserts"
./gen $DATA_FILE 8 $N > /dev/null

echo "Beginning experiments..."
#Run experiments
for P in $@
do 
    #Compute bit count from pages
    M=$(($P*4096*8))
    
    #Output progress to stdout
    echo "P=$P (M=$M)"
    
    #Run experiments
    RESULT=`./bloomfilt $DATA_FILE /dev/null $M`
    echo "$RESULT" >> $LOG_FILE

    #Parse results
    PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$RESULT"`

    R_SECONDS=`grep -oP 'regular seconds:\s*\K\d+(\.\d+)?' <<< "$RESULT"`
    H_SECONDS=`grep -oP 'hierarchial seconds:\s*\K\d+(\.\d+)?' <<< "$RESULT"`

    #Output results to stdout
    echo "regular:   $R_SECONDS (s)"
    echo "hierarchial:   $H_SECONDS (s)"

    #Write results to row
    echo "$PAGE_COUNT   $R_SECONDS  $H_SECONDS" >> $DAT_FILE

    #Update plot
    ./plots/scale_m_plotter.bash $DAT_FILE
done

#Clean up generated data
rm $DATA_FILE