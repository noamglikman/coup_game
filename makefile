C = g++
CFLAGS = -c -Wall -std=c++17 -g -I$(HPP) -I$(CPP)
TARGET = demo
TEST_TARGET = tests
GUI_TARGET = GameGUI

CPP = CPP/
HPP = HPP/
OBJ = OBJ/

header = $(HPP)Baron.hpp $(HPP)General.hpp $(HPP)Governor.hpp $(HPP)Judge.hpp $(HPP)Merchant.hpp $(HPP)Player.hpp $(HPP)Spy.hpp GameGUI.hpp

# קבצי אובייקט לפרויקט הראשי
OBJS = $(OBJ)Demo.o $(OBJ)Baron.o $(OBJ)General.o $(OBJ)Governor.o $(OBJ)Judge.o $(OBJ)Merchant.o $(OBJ)Player.o $(OBJ)Spy.o $(OBJ)Game.o

# קבצי אובייקט לגרסת הבדיקות, כולל test.o
TEST_OBJS = $(OBJ)test.o $(OBJ)Baron.o $(OBJ)General.o $(OBJ)Governor.o $(OBJ)Judge.o $(OBJ)Merchant.o $(OBJ)Player.o $(OBJ)Spy.o $(OBJ)Game.o

# קבצי אובייקט עבור GUI
GUI_OBJS = $(OBJ)GameGUI.o $(OBJ)Game.o $(OBJ)Player.o $(OBJ)Baron.o $(OBJ)General.o $(OBJ)Governor.o $(OBJ)Judge.o $(OBJ)Merchant.o $(OBJ)Spy.o

# יצירת תיקיית OBJ במידת הצורך
$(OBJ):
	mkdir -p $(OBJ)

all: $(TARGET)

# קישור לקובץ הראשי demo
$(TARGET): $(OBJS)
	$(C) -Wall -o $(TARGET) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system

# קישור לקובץ הבדיקות
$(TEST_TARGET): $(TEST_OBJS)
	$(C) -Wall -std=c++17 -g -o $(TEST_TARGET) $(TEST_OBJS) -lsfml-graphics -lsfml-window -lsfml-system

# קישור ל-GUI
$(GUI_TARGET): $(GUI_OBJS)
	$(C) -Wall -o $(GUI_TARGET) $(GUI_OBJS) -lsfml-graphics -lsfml-window -lsfml-system

# קומפילציה של קבצי cpp ל-obj

$(OBJ)Demo.o: Demo.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) Demo.cpp -o $(OBJ)Demo.o

$(OBJ)GameGUI.o: GameGUI.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) GameGUI.cpp -o $(OBJ)GameGUI.o

$(OBJ)test.o: test.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) test.cpp -o $(OBJ)test.o

$(OBJ)Game.o: $(CPP)Game.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)Game.cpp -o $(OBJ)Game.o

$(OBJ)Baron.o: $(CPP)Baron.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)Baron.cpp -o $(OBJ)Baron.o

$(OBJ)General.o: $(CPP)General.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)General.cpp -o $(OBJ)General.o

$(OBJ)Governor.o: $(CPP)Governor.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)Governor.cpp -o $(OBJ)Governor.o

$(OBJ)Judge.o: $(CPP)Judge.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)Judge.cpp -o $(OBJ)Judge.o

$(OBJ)Merchant.o: $(CPP)Merchant.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)Merchant.cpp -o $(OBJ)Merchant.o

$(OBJ)Player.o: $(CPP)Player.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)Player.cpp -o $(OBJ)Player.o

$(OBJ)Spy.o: $(CPP)Spy.cpp $(header) | $(OBJ)
	$(C) $(CFLAGS) $(CPP)Spy.cpp -o $(OBJ)Spy.o

# הפעלת הפרויקטים

Demo: $(TARGET)
	./$(TARGET)

run_gui: $(GUI_TARGET)
	./$(GUI_TARGET)

run_tests: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJ)*.o $(TARGET) $(GUI_TARGET) $(TEST_TARGET)

.PHONY: all clean Demo run_gui run_tests
