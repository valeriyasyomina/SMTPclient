.ONESHELL:
report:
	cd ../src
	doxygen main.c	
	cd ../report	

	rm -rf ./doxygen/latex
	cp -avr ../src/latex ./doxygen/latex

	rm -rf ../src/latex
	rm -rf ../src/html
	

	rm ./includes/cflow.txt
	cflow ../src/*.c | sed -e 's/\s*<.*>\s*//' >> ./includes/cflow.txt
		
	rm ./includes/UnitTests.txt
	make -C ../tests/UnitTests
	../tests/UnitTests/UnitTests >> ./includes/UnitTests.txt

	rm ./includes/valgrind_UnitTests.txt
	valgrind  --log-file="./includes/valgrind_UnitTests.txt" --leak-check=full --show-leak-kinds=all ../tests/UnitTests/UnitTests 

	rm ./includes/client_fsm.pdf
	python ./utils/defToGraph.py ./includes/client.def ./includes/client_fsm

	rm ./includes/SystemTests.txt
	cp ../tests/SystemTests/SystemTests.txt ./includes/SystemTests.txt

	rm ./includes/valgrind_SystemTests.txt
	cp ../tests/SystemTests/maildir/valgrind_SystemTests.txt ./includes/valgrind_SystemTests.txt
	
	pdflatex report.tex

clean:
	rm -f report.out report.toc report.aux report.pdf report.log
	rm -rf ./doxygen/latex
	rm -rf ./doxygen/html

.PHONY: clean
