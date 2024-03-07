all:
	@ cd src/lex && flex -o lex.yy.cc lex.l
	@[ -d build/ ] || mkdir build/ && cd build/ && cmake .. && make -j8 -s

run:
	@[ -f build/src/Parser ] || echo "executable not build yet; 'make' first"
	@./build/src/Parser

runtest:
	@[ -f build/test/ParserTest ] || echo "executable not built yet; 'make' first"
	@./build/test/ParserTest

valgrind:
	@[ -f build/src/Parser ] || echo "executable not built yet; 'make' first"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./build/src/Parser

clean:
	@rm -rf build/