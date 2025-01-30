
CXX := g++

CXXFLAGS := -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

SRC_DIR := src
TEST_DIR := gtest
SRCS := $(SRC_DIR)/sorted_list.cpp \
        $(SRC_DIR)/main.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := hw3
GTEST_SRCS := $(TEST_DIR)/hw_gtests.cpp
GTEST_OBJS := $(GTEST_SRCS:.cpp=.o)
GTEST_TARGET := run_tests
LDFLAGS := -lgtest -lgtest_main -pthread

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(GTEST_OBJS) $(SRC_DIR)/sorted_list.o
	$(CXX) $(CXXFLAGS) -o $(GTEST_TARGET) $(GTEST_SRCS) $(SRC_DIR)/sorted_list.cpp $(LDFLAGS)
	./$(GTEST_TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET) $(GTEST_TARGET)
