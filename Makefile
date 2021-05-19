# Matt Champlin
# Date:
# Makefile Template
#


CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11


pong: pong.cpp board.cpp paddle.cpp termfuncs.cpp ball.cpp
	${CXX} ${CXXFLAGS} -o $@ $^

%.o: %.cpp $(shell echo *.h)
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -r pong *.dSYM
