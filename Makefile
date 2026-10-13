CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2
LDFLAGS  :=
LDLIBS   :=

TARGET   := xlog-fetcher
SRCS     := $(wildcard *.cpp)
OBJS     := $(SRCS:.cpp=.o)
DEPS     := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) $(TARGET).exe

.PHONY: all clean

-include $(DEPS)
