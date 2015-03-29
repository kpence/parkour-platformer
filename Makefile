# Configuration
BIN = bin

# Libraries
LIBS = -lm
LIBS += -lsfml-graphics -lsfml-window -lsfml-system
LIBS += -ljsoncpp

# Other variables
CC = clang++
CFLAGS = -g -Wall -std=c++11

#------------------------------------------------------------------
#
#
# Project source files ---------------------------------/
# /
SRCS = main.cpp Animation.cpp Game.cpp Level.cpp

# components/
SRCS += components/Component.cpp components/AnimationComponent.cpp components/InputComponent.cpp components/PhysicsComponent.cpp components/StateComponent.cpp

# entities/
SRCS += entities/Player.cpp entities/Entity.cpp entities/SolidBlock.cpp

# screens/
SRCS += screens/ScreenManager.cpp screens/Screen.cpp screens/GameScreen.cpp screens/MenuScreen.cpp screens/PauseScreen.cpp

# states/
SRCS += states/State.cpp
SRCS += states/IdleState.cpp states/WalkState.cpp states/RollState.cpp states/RunState.cpp states/WallSlideState.cpp states/SkidState.cpp
SRCS += states/EdgeLeanState.cpp
SRCS += states/FallState.cpp states/JumpState.cpp states/DoubleJumpState.cpp states/DiveState.cpp states/LandState.cpp states/WallJumpState.cpp

# ------------------------------------------------------\
#
#
#------------------------------------------------------------------

OBJS = $(SRCS:.cpp=.o)

.PHONY: all install clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o */*.o $(BIN)

#EOF
