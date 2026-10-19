CXX      := g++
CC       := gcc
CXXFLAGS := -std=c++23 -Wall -Wextra -O2 $(shell pkg-config --cflags libnm)
CFLAGS   := -Wall -Wextra -O2
LDFLAGS  :=
LDLIBS   := $(shell pkg-config --libs libnm)

TARGET   := xlog-fetcher
CPP_SRCS := $(wildcard *.cpp)
C_SRCS   := $(wildcard cdotenv/*.c)
OBJS     := $(CPP_SRCS:.cpp=.o) $(C_SRCS:.c=.o)
DEPS     := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

.PHONY: all clean

-include $(DEPS)
