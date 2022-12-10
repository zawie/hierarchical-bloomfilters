TIMESTAMP=`date +%F-%T`

ID="aol_$TIMESTAMP"
DAT_FILE="experiments/dats/$ID.dat"

AOL_DATA="./data/aol"
KEYS="./data/keys"
SHUFFLED_KEYS="./data/shuffled_keys"

INSERT_KEYS="./data/aol_insert_keys"
QUERY_KEYS="./data/aol_query_keys"

# Download data
echo "Downloading data"
curl --output $AOL_DATA http://www.cim.mcgill.ca/~dudek/206/Logs/AOL-user-ct-collection/user-ct-test-collection-01.txt

echo "Parsing unique queries"
cat $AOL_DATA | awk -F'\t' '{print $2}' | sort | uniq -u >> $KEYS #Getting second column, which contains queries

#Shuffle keys
echo "Shuffling keys"
shuf $KEYS >> $SHUFFLED_KEYS

#Split keys into insertions and queries
echo "Counting keys"
N=`wc -l < $KEYS` #736967
echo "Key Count = $N"


echo "Splitting keys"
cat $SHUFFLED_KEYS | awk 'FNR < 730000' >> $INSERT_KEYS
cat $SHUFFLED_KEYS | awk 'FNR >= 730000' >> $QUERY_KEYS #6967

echo "Counting insertions"
N=`wc -l < $INSERT_KEYS`
echo "Insertion Count = $N"


echo "# AOL Data (N=$N)" >> $DAT_FILE
echo "# timestamp=$TIMESTAMP" >> $DAT_FILE
echo "#n/m  standard_thru  hierarchal_thru  standard_fp hierarchal_fp" >> $DAT_FILE

echo "Beginning experiment..."


for BPE in $@
do 
    #Compute bit count from pages
    M=$(($N*$BPE))
    
    #Output progress to stdout
    echo "BPE=$BPE (M=$M)"
    
    #Run experiments
    S_RESULT=`./standard $INSERT_KEYS $QUERY_KEYS $M`
    H_RESULT=`./hierarchical $INSERT_KEYS $QUERY_KEYS $M`

    #Parse results
    PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$S_RESULT"`
    BITS_PER_ELEMENTS=`grep -oP 'bits per elements:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`

    S_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    H_SECONDS=`grep -oP 'seconds:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`
    S_THRU=`grep -oP 'throughput:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    H_THRU=`grep -oP 'throughput:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`
    S_FP=`grep -oP 'positive rate:\s*\K\d+(\.\d+)?' <<< "$S_RESULT"`
    H_FP=`grep -oP 'positive rate:\s*\K\d+(\.\d+)?' <<< "$H_RESULT"`

    #Output results to stdout
    echo "pages count:  $PAGE_COUNT"
    echo "bits per element:   $BITS_PER_ELEMENTS"
    echo "standard:   $S_SECONDS (s)"
    echo "standard:   $S_THRU (ops/s)"
    echo "standard false-positive rate: $S_FP"
    echo "hierarchial:   $H_SECONDS (s)"
    echo "hierarchial:   $H_THRU (ops/s)"
    echo "hierarchial false-positive rate:  $H_FP"

    #Write results to row
    echo "$BPE   $S_THRU $H_THRU    $S_FP    $H_FP" >> $DAT_FILE


    #Update plot
    # ./plots/aol_plotter.bash $DAT_FILE
done

sleep 1

./plots/aol_plotter.bash $DAT_FILE

# #Clean up data
rm $AOL_DATA
rm $KEYS
rm $SHUFFLED_KEYS
rm $INSERT_KEYS
rm $QUERY_KEYS