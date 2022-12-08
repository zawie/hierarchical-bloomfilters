TIMESTAMP=`date +%F_%T`

ID="scale-nm_$TIMESTAMP"
DAT_FILE="experiments/dats/$ID.dat"
DATA_FILE="data/$ID.txt"

#Write header
echo "# WHACK ALERT!"
echo "# Desc: Fix number of operations and scale bliim filter size" >> $DAT_FILE
echo "# timestamp=$TIMESTAMP" >> $DAT_FILE
echo "#n (1e6)   standard (s)    hierarchal4096 (s) hierarchal1024(s)  hierarchal256 (s)  hierarchal64 (s)  hierarchal8 (s)" >> $DAT_FILE

BPE="10"

#Run experiments
for c in 1, 2, 3
do
for N in $@
do

    M=$(($N*$BPE))

    #Output progress to stdout
    echo "N=$N"

    #Generate data
    ./gen $DATA_FILE 8 $N > /dev/null

    #Run standard
    S_RESULT=`./hierarchical $DATA_FILE /dev/null $M 4096`

    #Parse results of standard
    # PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$S_RESULT"`
    S_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    N_IN_MIL=`grep -oP 'insert count in millions:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`

    # Run hierarchical with various sub sizes
    H_OUT=""
    for s in 4096, 1024, 256, 64, 8
    do
        H_RESULT=`./hierarchical $DATA_FILE /dev/null $M $s`
        H_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`
        H_OUT="$H_OUT $H_SECONDS"
    done

    #Write results to row
    echo "$N_IN_MIL    $S_SECONDS    $H_OUT" >> $DAT_FILE

    #Update plot, ignoring errors or warnings
    ./plots/scale_nm_plotter.bash $DAT_FILE > /dev/null
done

#Clean up generated data file
rm $DATA_FILE
done

#Wait for DAT file to flush
sleep 1

#Final plot
./plots/scale_nm_plotter.bash $DAT_FILE

