# ---- config ----
CXX      := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -O3
LDFLAGS  :=
LDLIBS   :=

TARGET := backward_chaining
SRCS   := main.cpp rules.cpp

.PHONY: all run clean
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRCS) -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)

