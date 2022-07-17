C_COMPILER ?= clang
CXX_COMPILER ?= clang++
GENERATOR ?= Ninja
BUILD_TYPE ?= Debug
BUILD_DIR ?= build

export CC = $(C_COMPILER)
export CXX = $(CXX_COMPILER)

.PHONY: configure
configure:
	cmake -S . -B $(BUILD_DIR) -G "$(GENERATOR)" \
		-D CMAKE_BUILD_TYPE="$(BUILD_TYPE)" \
		-D CMAKE_EXPORT_COMPILE_COMMANDS=ON

.PHONY: build
build: configure
	cmake --build $(BUILD_DIR) --config "$(BUILD_TYPE)" --parallel

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: test
test: BUILD_TESTS = ON
test: build
	ctest --output-on-failure --test-dir $(BUILD_DIR) -C "$(BUILD_TYPE)"

.PHONY: submodules
submodules:
	git submodule update --init --recursive --jobs=4
	git pull --recurse-submodules --jobs=4

.PHONY: update-submodules
update-submodules: reset-submodules
	git submodule foreach git pull

.PHONY: reset-submodules
reset-submodules:
	git submodule foreach --recursive git reset --hard

.PHONY: clang-format
clang-format:
	git ls-files -- '*.cpp' '*.h' | xargs clang-format -i -style=file
	git diff --exit-code --color
