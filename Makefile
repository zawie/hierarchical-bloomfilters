SRCDIR = ./code/src
TSTDIR = ./code/tst
UNITYDIR = ./code/lib/unity
TEST_EXE_NAME = test.generated.exe
MAIN_FILEPATH = ./bloomfilt
GEN_FILEPATH = ./gen

build:
	gcc $(SRCDIR)/main.c -o $(MAIN_FILEPATH)
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
	rm gen
	rm bloomfilt

clean_dats:
	rm experiments/dats/*.dat
	rm experiments/logs/*.log