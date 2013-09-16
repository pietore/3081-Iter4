CXX_DIR = ../lib/cxxtest
CXXTEST = $(CXX_DIR)/cxxtestgen.pl
CXXFLAGS = --error-printer --abort-on-fail --have-eh

FLAGS = -Wall -g

translator: readInput.o regex.o scanner.o Parser.cpp Parser.h \
		ParseResult.h ExtToken.o Parser.o ParseResult.o \
		translator.cpp
	g++ $(FLAGS) translator.cpp -o translator readInput.o regex.o \
		scanner.o Parser.o ParseResult.o ExtToken.o
	

# Program files.
readInput.o:	readInput.cpp readInput.h
	g++ $(FLAGS) -c readInput.cpp 

regex.o:	regex.cpp regex.h
	g++ $(FLAGS) -c regex.cpp 

scanner.o:	scanner.cpp scanner.h regex.h
	g++ $(FLAGS) -c scanner.cpp


# Testing files and targets.
run-tests:	regex_tests scanner_tests eve_of_destruction_tests i1_assessment_tests parser_tests ast_tests i2_assessment_tests i3_assessment_tests i4_assessment_tests
	./regex_tests
	./scanner_tests
	./i1_assessment_tests
	./eve_of_destruction_tests
	./parser_tests
	./ast_tests
	./i2_assessment_tests
	./i3_assessment_tests
	./i4_assessment_tests

regex_tests:	regex_tests.cpp regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -o regex_tests regex.o regex_tests.cpp

regex_tests.cpp:	regex.h regex_tests.h
	$(CXXTEST) $(CXXFLAGS) -o regex_tests.cpp regex_tests.h

scanner_tests:	scanner_tests.cpp scanner.o regex.o readInput.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o scanner_tests \
		scanner.o regex.o readInput.o scanner_tests.cpp

scanner_tests.cpp:	scanner.o scanner_tests.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o scanner_tests.cpp scanner_tests.h
	
i1_assessment_tests:	i1_assessment_tests.cpp scanner.o regex.o readInput.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o i1_assessment_tests \
		scanner.o regex.o readInput.o i1_assessment_tests.cpp i1_assessment_tests.h

i1_assessment_tests.cpp:	scanner.o i1_assessment_tests.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o i1_assessment_tests.cpp i1_assessment_tests.h
	
eve_of_destruction_tests:	 eve_tests.cpp scanner.o regex.o readInput.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o eve_of_destruction_tests \
		scanner.o regex.o readInput.o eve_tests.cpp eve_of_destruction_tests.h
		
eve_tests.cpp:	scanner.o eve_of_destruction_tests.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o eve_tests.cpp eve_of_destruction_tests.h

parser_tests: parser_tests.h Parser.h Parser.cpp Parser.o \
			ParseResult.h ParseResult.cpp ParseResult.o\
			ExtToken.h ExtToken.cpp ExtToken.o parser_tests.cpp\
			regex.o readInput.o scanner.o
	g++ $(FLAGS) -I$(CXX_DIR) -o parser_tests ExtToken.o ParseResult.o \
			Parser.o parser_tests.h parser_tests.cpp regex.o \
			readInput.o scanner.o
			
ast_tests:	ast_tests.h Parser.h Parser.cpp Parser.o \
			ParseResult.h ParseResult.cpp ParseResult.o\
			ExtToken.h ExtToken.cpp ExtToken.o ast_tests.cpp\
			regex.o readInput.o scanner.o
	g++ $(FLAGS) -I$(CXX_DIR) -o ast_tests ExtToken.o ParseResult.o \
			Parser.o ast_tests.h ast_tests.cpp regex.o \
			readInput.o scanner.o -g
			
i4_assessment_tests:	i4_assessment_tests.h Parser.h Parser.cpp Parser.o \
			ParseResult.h ParseResult.cpp ParseResult.o\
			ExtToken.h ExtToken.cpp ExtToken.o i4_assessment_tests.cpp\
			regex.o readInput.o scanner.o
	g++ $(FLAGS) -I$(CXX_DIR) -o i4_assessment_tests ExtToken.o ParseResult.o \
			Parser.o ast_tests.h i4_assessment_tests.cpp regex.o \
			readInput.o scanner.o -g
			
i3_assessment_tests:	i3_assessment_tests.h Parser.h Parser.cpp Parser.o \
			ParseResult.h ParseResult.cpp ParseResult.o\
			ExtToken.h ExtToken.cpp ExtToken.o i3_assessment_tests.cpp\
			regex.o readInput.o scanner.o
	g++ $(FLAGS) -I$(CXX_DIR) -o i3_assessment_tests ExtToken.o ParseResult.o \
			Parser.o ast_tests.h i3_assessment_tests.cpp regex.o \
			readInput.o scanner.o -g
			
i2_assessment_tests:	i2_assessment_tests.h Parser.h Parser.cpp Parser.o \
			ParseResult.h ParseResult.cpp ParseResult.o\
			ExtToken.h ExtToken.cpp ExtToken.o i2_assessment_tests.cpp\
			regex.o readInput.o scanner.o
	g++ $(FLAGS) -I$(CXX_DIR) -o i2_assessment_tests ExtToken.o ParseResult.o \
			Parser.o ast_tests.h i2_assessment_tests.cpp regex.o \
			readInput.o scanner.o -g

Parser.o: Parser.cpp Parser.h ParseResult.h ExtToken.o
	g++ $(FLAGS) -c Parser.cpp Parser.h

ParseResult.o: ParseResult.h ParseResult.cpp
	g++ $(FLAGS) -c ParseResult.h ParseResult.cpp

ExtToken.o: ExtToken.cpp ExtToken.cpp
	g++ $(FLAGS) -c ExtToken.cpp ExtToken.h

parser_tests.cpp: parser_tests.h Parser.o ParseResult.o ExtToken.o
	$(CXXTEST) $(CXXFLAGS) -o parser_tests.cpp parser_tests.h ExtToken.o ParseResult.o Parser.o

ast_tests.cpp: ast_tests.h Parser.o ParseResult.o ExtToken.o
	$(CXXTEST) $(CXXFLAGS) -o ast_tests.cpp ast_tests.h ExtToken.o ParseResult.o Parser.o 

i4_assessment_tests.cpp: i4_assessment_tests.h Parser.o ParseResult.o ExtToken.o
	$(CXXTEST) $(CXXFLAGS) -o i4_assessment_tests.cpp i4_assessment_tests.h ExtToken.o ParseResult.o Parser.o 
	
i3_assessment_tests.cpp: i3_assessment_tests.h Parser.o ParseResult.o ExtToken.o
	$(CXXTEST) $(CXXFLAGS) -o i3_assessment_tests.cpp i3_assessment_tests.h ExtToken.o ParseResult.o Parser.o 
	
i2_assessment_tests.cpp: i2_assessment_tests.h Parser.o ParseResult.o ExtToken.o
	$(CXXTEST) $(CXXFLAGS) -o i2_assessment_tests.cpp i2_assessment_tests.h ExtToken.o ParseResult.o Parser.o 

clean:
	rm -Rf *.o \
		regex_tests regex_tests.cpp i1_assessment_tests\
		i2_assessment_tests i3_assessment_tests \
		scanner_tests scanner_tests.cpp \
		translator parser_tests ast_tests\
		eve_of_destruction i4_assessment_tests\
		
