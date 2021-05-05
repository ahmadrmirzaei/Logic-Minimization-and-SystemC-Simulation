all:
	flex -oscanner.cc scanner.l
	bison -oparser.cc parser.y
	g++ driver.cc assign.cc main.cc module.cc parser.cc scanner.cc wire.cc util.cc -o app