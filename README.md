The repository is under development and some updates are not currently showed, as the objective is to get an optimized version of what we see here.
```bash
edge-cv-lib/
├── CMakeLists.txt              # The root build configuration file
├── README.md                   # Project overview, build instructions, and benchmarks
├── .gitignore                  # Ignore build/, bin/, and lib/ directories
│
├── include/                    # PUBLIC headers (Your modular APIs)
│   └── edgecv/                 # Always namespace your includes!
│       ├── core.hpp            # Base types and memory allocation definitions
│       ├── linalg.hpp          # Your optimized linear algebra APIs
│       ├── prob.hpp            # Probabilistic primitives interfaces
│       └── vision.hpp          # Computer vision pipeline interfaces
│
├── src/                        # PRIVATE source code and private headers
│   ├── CMakeLists.txt          # Tells CMake how to build the library itself
│   ├── core/                   # Memory pool implementations, etc.
│   ├── linalg/                 # Highly optimized math implementations (.cpp)
│   ├── prob/                   # Implementation of probabilistic models
│   └── vision/                 # OpenCV wrapper logic / anomaly detection logic
│
├── tests/                      # Unit tests (Crucial for math and algorithms)
│   ├── CMakeLists.txt          # Tells CMake how to build the tests
│   ├── test_linalg.cpp         # Verifies your math primitives are accurate
│   └── test_vision.cpp         # Verifies CV pipelines work
│
├── benchmarks/                 # Performance tracking (Crucial for your resume claims)
│   └── latency_tests.cpp       # Code to measure execution time and memory footprint
│
└── examples/                   # Example applications (Proof of concept)
    └── pi_camera_demo.cpp      # Demo showing how to use the library on a Raspberry Pi
```