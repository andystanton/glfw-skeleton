.PHONY: all configure build clean run test help debug release regenerate-glad

# Default build type
BUILD_TYPE ?= debug
BUILD_DIR := build/$(BUILD_TYPE)
EXECUTABLE := $(BUILD_DIR)/bin/glfw-skeleton

# Default target
all: build

# Display help information
help:
	@echo "Available targets:"
	@echo "  make [all]          - Build the project (default: debug)"
	@echo "  make configure      - Configure CMake with current BUILD_TYPE"
	@echo "  make build          - Build the project"
	@echo "  make run            - Build and run the application"
	@echo "  make clean          - Remove build artifacts"
	@echo "  make debug          - Configure and build in debug mode"
	@echo "  make release        - Configure and build in release mode"
	@echo "  make regenerate-glad - Regenerate glad OpenGL loader (uses Python venv)"
	@echo "  make help           - Show this help message"
	@echo ""
	@echo "Environment variables:"
	@echo "  BUILD_TYPE          - Set build type (debug|release|relwithdebinfo)"
	@echo ""
	@echo "Examples:"
	@echo "  make debug          - Build debug version"
	@echo "  make release        - Build release version"
	@echo "  make run            - Build and run (debug by default)"
	@echo "  BUILD_TYPE=release make run - Build and run release version"

# Configure CMake using presets
configure:
	@echo "Configuring CMake ($(BUILD_TYPE))..."
	@cmake --preset=$(BUILD_TYPE)

# Build the project
build: configure
	@echo "Building project ($(BUILD_TYPE))..."
	@cmake --build $(BUILD_DIR) --parallel

# Run the application
run: build
	@echo "Running glfw-skeleton..."
	@$(EXECUTABLE)

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf build/

# Convenience targets for different build types
debug:
	@$(MAKE) BUILD_TYPE=debug build

release:
	@$(MAKE) BUILD_TYPE=release build

# Regenerate glad OpenGL loader files (requires Python + jinja2 in .venv)
regenerate-glad:
	@echo "Regenerating glad OpenGL loader..."
	@if [ ! -d ".venv" ]; then \
		echo "Creating Python virtual environment..."; \
		python3 -m venv .venv && .venv/bin/pip install --quiet jinja2; \
	fi
	@if [ ! -d "/tmp/glad-gen" ]; then \
		echo "Cloning glad v2.0.8..."; \
		git clone --depth 1 --branch v2.0.8 https://github.com/Dav1dde/glad.git /tmp/glad-gen; \
	fi
	@echo "Generating glad files for OpenGL 4.1 core..."
	@rm -rf extern/glad
	@cd /tmp/glad-gen && $(CURDIR)/.venv/bin/python -m glad --out-path $(CURDIR)/extern/glad --api gl:core=4.1 --reproducible c
	@echo "Done! glad files regenerated in ./extern/glad/"
