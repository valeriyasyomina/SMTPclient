CLIENT_NAME := client
LOGGER_NAME := logger

SystemTests: make_sources

.ONESHELL:
make_sources:
	cd ../../src
	make client
	make logger
	rm ../tests/SystemTests/client
	rm ../tests/SystemTests/logger
	cp $(CLIENT_NAME) ../tests/SystemTests
	cp $(LOGGER_NAME) ../tests/SystemTests
	cd ../tests/SystemTests
	
clean:
	rm client logger SystemTests.txt valgrind_SystemTests.txt
		
.PHONY: clean make_sources
	
