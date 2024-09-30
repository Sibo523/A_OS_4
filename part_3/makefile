CC = gcc
CFLAGS = -g -Wall -pthread
VALGRIND = valgrind
HELGRIND = $(VALGRIND) --tool=helgrind

all: race 

race: race.c
	$(CC) $(CFLAGS) $< -o $@


run_race: race
	./race


helgrind_race: race
	$(HELGRIND) ./race > detect_race_condition_hellgrind.txt 2>&1


gdb_valgrind_race: race
	@echo "In another terminal, run: gdb ./race"
	@echo "Then in gdb, type: target remote | vgdb"
	$(VALGRIND) --vgdb=yes --vgdb-error=0 ./race


clean:
	rm -f race race_fixed

.PHONY: all run_race run_race_fixed helgrind_race helgrind_race_fixed gdb_valgrind_race gdb_valgrind_race_fixed clean