
build:
        @mkdir -p build
        cd build && cmake .. && make

exec:
        ./build/TicTacToeGame

run: build exec

clean:
        @rm -rf build
