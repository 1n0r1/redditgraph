# Executable names:
EXE = graph
TEST = testgraph

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o Graph.o GraphVisualization.o PriorityQueue.o PhysicSimulation.o FileReader.o

# Generated files
CLEAN_RM = 

# Use the cs225 makefile template:
include cs225/make/cs225.mk


# MP-specific targets

# DSETS_OBJS = testdsets.o
# DSETS_OBJS += dsets.o

# testdsets: $(DSETS_OBJS)
# 	$(LD) $^ $(LDFLAGS) -o $@

# MAZE_OBJS = $(filter-out $(EXE_OBJ), $(OBJS))
# MAZE_OBJS += testsquaremaze.o

# testsquaremaze: $(MAZE_OBJS)
# 	$(LD) $^ $(LDFLAGS) -o $@
