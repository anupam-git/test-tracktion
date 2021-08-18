# Clone and Build
```
git clone --recurse-submodules https://github.com/anupam-git/test-tracktion.git
mkdir build && cd build
cmake ..
make -j$(nproc)
```

# Test CLI
```
cd build # Change into build directory if not already done

./cli ../c4.wav
```

# Test GUI
```
cd build # Change into build directory if not already done

./gui_artefacts/Debug/gui
```