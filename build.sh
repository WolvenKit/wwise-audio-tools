# Build for macOS
rm -rf build obj && mkdir build && mkdir obj && cmake -DCMAKE_BUILD_TYPE=Release -S . -B build && \
	cmake --build build -- -j`sysctl -n hw.logicalcpu`
