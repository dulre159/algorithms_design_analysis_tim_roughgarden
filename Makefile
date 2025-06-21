subprj0 := integers_multiplication
subprj1 := sorting
subprj2 := inversions_counter
subprj3 := closest_pair
subprjcom := commons
out_dir := out

all: $(out_dir) $(subprj0) $(subprj1) $(subprj2) $(subprj3)

$(out_dir):
	mkdir $(out_dir)

$(subprj0): $(out_dir) ./$(subprj0)/$(subprj0) 

./$(subprj0)/$(subprj0): ./$(subprj0)/main.cpp
	mkdir ./$(subprj0)/$(out_dir)
	$(CXX) ./$(subprj0)/main.cpp -o ./$(subprj0)/$(out_dir)/$(subprj0)
	cp ./$(subprj0)/$(out_dir)/$(subprj0) ./$(out_dir)

$(subprj1): $(out_dir) ./$(subprj1)/$(subprj1)

./$(subprj1)/$(subprj1): ./$(subprj1)/main.cpp ./$(subprjcom)/vector_utils.cpp
	mkdir ./$(subprj1)/$(out_dir)
	$(CXX) ./$(subprj1)/main.cpp ./$(subprjcom)/vector_utils.cpp -o ./$(subprj1)/$(out_dir)/$(subprj1)
	cp ./$(subprj1)/$(out_dir)/$(subprj1) ./$(out_dir)

$(subprj2): $(out_dir) ./$(subprj2)/$(subprj2)

./$(subprj2)/$(subprj2): ./$(subprj2)/main.cpp ./$(subprjcom)/vector_utils.cpp
	mkdir ./$(subprj2)/$(out_dir)
	$(CXX) ./$(subprj2)/main.cpp ./$(subprjcom)/vector_utils.cpp -o ./$(subprj2)/$(out_dir)/$(subprj2)
	cp ./$(subprj2)/$(out_dir)/$(subprj2) ./$(out_dir)

$(subprj3): $(out_dir) ./$(subprj3)/$(subprj3)

./$(subprj3)/$(subprj3): ./$(subprj3)/main.cpp ./$(subprjcom)/vector_utils.cpp
	mkdir ./$(subprj3)/$(out_dir)
	$(CXX) ./$(subprj3)/main.cpp ./$(subprjcom)/vector_utils.cpp -o ./$(subprj3)/$(out_dir)/$(subprj3)
	cp ./$(subprj3)/$(out_dir)/$(subprj3) ./$(out_dir)

clean:
	rm -rf ./$(subprj0)/$(out_dir)
	rm -rf ./$(subprj1)/$(out_dir)
	rm -rf ./$(subprj2)/$(out_dir)
	rm -rf ./$(subprj3)/$(out_dir)
	rm -rf ./$(out_dir)
