# Custom Memory Allocator

High-performance memory management system implementing malloc/free functionality from scratch in C. Features automatic coalescing, comprehensive error detection, and optimized allocation strategies for embedded and systems programming applications.

## Key Features

- **Custom Memory Management**: Complete malloc/free implementation using fixed 4KB memory pool
- **Automatic Coalescing**: Advanced fragmentation prevention through adjacent block merging
- **Comprehensive Error Detection**: Runtime validation for double-free, invalid pointers, and boundary violations
- **Performance Optimization**: Sub-millisecond allocation/deallocation with efficient metadata overhead
- **Debug Integration**: File and line number tracking for memory error diagnostics
- **Zero External Dependencies**: Self-contained implementation requiring no standard library memory functions

## Architecture Overview

### Memory Layout Design

```
[Header][Payload Data...][Header][Payload Data...]
 3 bytes   Variable Size   3 bytes   Variable Size

Header Format:
[Status][Size High][Size Low]
  1 byte    1 byte    1 byte

Status Values:
- 'r': Reserved (allocated)
- 'f': Free (available)
- 0:   Uninitialized
```

### Core Components

**Allocation Engine**
- Best-fit allocation strategy with linear search optimization
- Dynamic block splitting for memory efficiency
- Automatic initialization of memory pool on first use

**Coalescing Algorithm** 
- Bidirectional block merging to prevent fragmentation
- Triggered automatically after each deallocation
- O(n) time complexity with single-pass coalescing

**Error Detection System**
- Invalid pointer validation before deallocation
- Double-free prevention with status tracking
- Boundary checking for allocation requests

## Technical Specifications

- **Language**: C (C99 standard)
- **Memory Pool**: 4096 bytes fixed allocation
- **Metadata Overhead**: 3 bytes per block
- **Maximum Block Size**: 65,535 bytes (16-bit addressing)
- **Alignment**: Byte-aligned allocation
- **Error Reporting**: File/line integration via preprocessor macros

## Implementation Highlights

- **Custom Size Encoding**: 16-bit size storage using base-255 arithmetic for compact metadata
- **Status Management**: Single-byte block status tracking with immediate validation
- **Memory Pool Management**: Self-initializing allocator requiring no setup calls
- **Fragmentation Control**: Aggressive coalescing algorithm maintaining memory efficiency
- **Debug Support**: Comprehensive error messages with source location tracking

## Performance Characteristics

Based on comprehensive benchmarking across multiple allocation patterns:

- **Simple Allocation/Deallocation**: ~0.0001 seconds average
- **Bulk Operations**: ~0.002 seconds for 120 sequential allocations
- **Random Access Patterns**: ~0.00001 seconds average
- **Complex Workloads**: ~0.011 seconds for mixed-size operations
- **Large Block Allocation**: ~0.0001 seconds for 1KB blocks

## Build & Testing

### Prerequisites
```bash
# Required: GCC with C99 support
gcc --version  # Verify GCC installation
```

### Compilation
```bash
make           # Build allocator with comprehensive test suite
```

### Test Execution
```bash
# Run specific test cases
./memgrind 1   # Test invalid free() detection
./memgrind 2   # Test offset pointer free() detection  
./memgrind 3   # Test double-free detection
./memgrind 4   # Performance: 120 alloc/free cycles
./memgrind 5   # Performance: Bulk allocation patterns
./memgrind 6   # Performance: Random allocation/deallocation
./memgrind 7   # Stress test: Complex allocation patterns
./memgrind 8   # Stress test: Large block operations
```

## Error Detection Capabilities

The allocator provides comprehensive runtime validation:

### Memory Safety Violations
- **Invalid Pointer Detection**: Identifies pointers not returned by malloc()
- **Offset Pointer Prevention**: Blocks free() calls on non-aligned addresses
- **Double-Free Protection**: Prevents multiple deallocation of same block
- **Boundary Validation**: Ensures allocation requests fit within memory pool

### Debug Information
```c
// Error output example
ERROR! Trying to free something already freed.
File: test.c, line: 42
```

## Algorithm Details

### Allocation Strategy
1. **Linear Search**: Traverse memory pool for suitable free blocks
2. **Best-Fit Selection**: Choose smallest block that satisfies request
3. **Block Splitting**: Divide oversized blocks to minimize waste
4. **Metadata Installation**: Configure header with size and status information

### Coalescing Algorithm
1. **Forward Merging**: Combine current block with subsequent free blocks
2. **Size Recalculation**: Update metadata to reflect merged block size
3. **Metadata Cleanup**: Remove redundant headers from merged regions
4. **Continuous Processing**: Repeat until no adjacent free blocks remain

## Applications

This memory allocator demonstrates techniques applicable to:

- **Embedded Systems**: Resource-constrained environments requiring predictable allocation
- **Real-Time Systems**: Applications needing deterministic memory management
- **Operating System Development**: Kernel-level memory management implementation
- **Performance-Critical Applications**: Systems requiring minimal allocation overhead
- **Educational Platforms**: Teaching memory management and systems programming concepts

## Code Quality Features

- **Memory Safety**: Comprehensive validation preventing common memory errors
- **Error Handling**: Detailed diagnostics with source location tracking
- **Performance Optimization**: Efficient algorithms minimizing overhead
- **Code Organization**: Clear separation of allocation, deallocation, and utility functions
- **Testing Coverage**: Extensive test suite validating all major functionality

## Getting Started

1. **Clone and build**:
   ```bash
   git clone <repository>
   cd custom-allocator
   make
   ```

2. **Run basic functionality test**:
   ```bash
   ./memgrind 4
   ```

3. **Integrate into your project**:
   ```c
   #include "mymalloc.h"
   
   int main() {
       void *ptr = malloc(100);  // Uses custom allocator
       free(ptr);               // Uses custom deallocator
       return 0;
   }
   ```

## Contributing

Demonstrates production-ready patterns for:
- Low-level memory management
- Algorithm optimization for systems programming
- Comprehensive error detection and debugging
- Performance-critical resource management
