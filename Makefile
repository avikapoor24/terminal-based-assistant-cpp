# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I include -I /opt/homebrew/opt/openssl@3/include
LDFLAGS = -L /opt/homebrew/opt/openssl@3/lib -lssl -lcrypto

# Source and Object Files
SRC = src/TaskManager.cpp src/MarksTracker.cpp src/Timetable.cpp src/Admin.cpp src/Attendance.cpp
OBJ = $(SRC:.cpp=.o)

# Executable Name
EXEC = assistant

# Build Target
all: $(EXEC)

$(EXEC): main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) main.cpp $(OBJ) $(LDFLAGS)

# Compile Object Files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean Build Files
clean:
	rm -f $(OBJ) $(EXEC)
