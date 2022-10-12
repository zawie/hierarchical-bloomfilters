echo "# Inserts,# Queries,Size (Pages),Regular Time (s),Hierarchial (s)" >> output.csv
for N in 50000
do
    echo N=$N

    #Generate data
    ./gen data/inserts 8 $N
    ./gen data/queries 8 $N

    #Run experiments
    echo Running timing script...
    RESULT=`./bloomfilt data/inserts data/queries`

    #Parse results
    NUM_INSERTS=`grep -oP 'insert count:\s*\K\d+' <<< "$RESULT"`
    NUM_QUERIES=`grep -oP 'query count:\s*\K\d+' <<< "$RESULT"`

    PAGE_COUNT=`grep -oP 'pages:\s*\K\d+' <<< "$RESULT"`

    R_SECONDS=`grep -oP 'regular seconds:\s*\K\d+' <<< "$RESULT"`
    H_SECONDS=`grep -oP 'hierarchial seconds:\s*\K\d+' <<< "$RESULT"`

    echo "$NUM_INSERTS,$NUM_QUERIES,$PAGE_COUNT,$R_SECONDS,$H_SECONDS" >> output.csv

done