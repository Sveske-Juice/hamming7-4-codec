# IMPORTANT: this is just a shortcut to invoke cmake from build/ directory
default:
	mkdir -p build/ && cd build/ && cmake .. && make
clean:
	rm -rf build/*
