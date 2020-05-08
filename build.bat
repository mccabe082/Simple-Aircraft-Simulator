REM Run me on windows to install to ./bin
mkdir build
pushd build
	cmake ..
	cmake --build . --config Debug
	cmake --install . --config Debug
popd