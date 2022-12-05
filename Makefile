SRCDIR = ./code/src
TSTDIR = ./code/tst
UNITYDIR = ./code/lib/unity
TEST_EXE_NAME = test.generated.exe
GEN_FILEPATH = ./gen

build:
	gcc -DTYPE=Standard -DINIT=bloomfilter_init -DINSERT=bloomfilter_insert -DQUERY=bloomfilter_check $(SRCDIR)/main.c -o ./standard
	gcc -DTYPE=Hierarchical -DINIT=h_bloomfilter_init -DINSERT=h_bloomfilter_insert -DQUERY=h_bloomfilter_check $(SRCDIR)/main.c -o ./hierarchical
	gcc $(SRCDIR)/generator.c -o $(GEN_FILEPATH)

unit:
	for test_file in $(TSTDIR)/* ; do \
		echo -e "-----------------------\nRunning test" $${test_file} "\n-----------------------"; \
		gcc $${test_file} $(UNITYDIR)/src/unity.c -o $(TEST_EXE_NAME); \
		./$(TEST_EXE_NAME); \
		rm ./$(TEST_EXE_NAME); \
	done

clean:
	rm -f ./core.*
	rm -f ./$(TEST_EXE_NAME)
	rm -f gen
	rm -r hierarchical
	rm -r standard

clean_all:
	make clean
	rm -f experiments/dats/*.dat
	rm -f experiments/logs/*.log
	rm -f data/*
	rm -f plots/*.png

run_fast:
	make clean
	make build
	./experiments/scale_nm.bash		10000 100000 200000 300000 500000 900000 1000000
	./experiments/scale_m.bash		1 5 7 20
	./experiments/fp.bash			2 5 10 15 

run_full:
	make clean
	make build
	./experiments/scale_nm.bash		1000000 5000000 10000000 15000000 20000000 25000000 30000000 40000000 50000000 70000000 90000000 110000000
	./experiments/scale_m.bash		1 2 3 4 5 6 7 8 9 10 15 20 25
	./experiments/fp.bash			2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20