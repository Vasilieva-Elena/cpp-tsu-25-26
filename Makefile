CXX	= g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET	= terminal SRCDIR	= src
SRCS	= $(wildcard $(SRCDIR)/*.cpp) OBJS	= $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
rm -f $(OBJS) $(TARGET)

.PHONY: all clean