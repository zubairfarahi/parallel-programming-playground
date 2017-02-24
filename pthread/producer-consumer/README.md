# BBM 442: Parallel Processing (Fall 2016) - Homework 1
_Disclaimer:_ If you have similar homework, do not copy paste directly. Try to solve yourself.

## Compile & Run
```bash
make
./main <buffer_size> [<producer_count> <consumer_count>]
```

## Parameters
**<buffer_size>** buffer size as unsigned integer

**<producer_count>** producer thread count as unsigned integer (optional, *default: 1*)

**<consumer_count>** consumer thread count as unsigned integer (optional, *default: 1*)

## Clean up
```bash
make clean
```

## Scenarios

- One producer and one consumer (./main <buffer_size>)
- One producer and multiple consumer (./main <buffer_size> 1 <consumer_count>)
- Multiple producer and multiple consumer (./main <buffer_size> <producer_count> <consumer_count>)

## Test

Tested on;
- gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.2) [4 cores / 4 threads] on VirtualBox on my computer
- gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.3) [4 cores / 8 threads] on Cloud9 free plan
- gcc version 4.8.5 20150623 (Red Hat 4.8.5-4) (GCC) [4 cores / 4 threads] on dev.cs
