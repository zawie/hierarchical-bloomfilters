SRCDIR = ./code/src
TSTDIR = ./code/tst
UNITYDIR = ./code/lib/unity
TEST_EXE_NAME = test.generated.exe
EXE_FILEPATH = ./bloomfilt

build:
	gcc $(SRCDIR)/main.c -o $(EXE_FILEPATH)
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