SRCDIR = ./code/src
TSTDIR = ./code/tst
UNITYDIR = ./code/lib/unity
TEST_EXE_NAME = Test_DELETE_ME.exe
unit:
	for test_file in $(TSTDIR)/* ; do \
		echo -e "-----------------------\nRunning test" $${test_file} "\n-----------------------"; \
		gcc $${test_file} ./code/src/bitarr.c $(UNITYDIR)/src/unity.c -o $(TEST_EXE_NAME); \
		./$(TEST_EXE_NAME); \
		rm ./$(TEST_EXE_NAME); \
	done