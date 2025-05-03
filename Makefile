c = g++
prom = sudoku
obj = main.o keyboard.o sudoku.o grid.o command.o config.o
deps = *.h
flag = -pthread

$(prom): $(obj)
	$(c) -o $(prom) $(flag) $^

%.o: %.cpp %.h
	$(c) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)

.PHONY: clean