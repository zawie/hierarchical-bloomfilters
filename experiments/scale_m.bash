TIMESTAMP=`date +%F-%T`
OUTPUT_FILE="experiments/results/scale-m_$TIMESTAMP.csv"

#Write header
echo "# Inserts,# Queries,Size (Pages),Regular Time (seconds),Hierarchial (seconds)" >> $OUTPUT_FILE

N=10000000

#Generate data
echo "Generating $N inserts and $N queries..."
./gen data/inserts 8 $N > /dev/null
./gen data/queries 8 $N > /dev/null

echo "Beginning experiments..."
#Run experiments
for M in 10000 100000 1000000 10000000
do 
    #Output progress to stdout
    echo M=$M

    #Run experiments
    RESULT=`./bloomfilt data/inserts data/queries $M`

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
    echo "$NUM_INSERTS,$NUM_QUERIES,$PAGE_COUNT,$R_SECONDS,$H_SECONDS" >> $OUTPUT_FILE

done