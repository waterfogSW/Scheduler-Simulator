# Scheduler-Simulator
Rough implementation of scheduler simulator - fcfs, spn, rr, mlfq, lottery

## Usage
```
$ git clone https://github.com/waterfogSW/Scheduler-Simulator.git
$ cd Scheduler-Simulator
$ make
$ ./sched
```

## Implementation

- Workload - `input.txt`
- FCFS : first come first serve
- SPN : shortest process next
- RR   : round robin
- MLFQ : multi level feedback queue (q = 1)
- MLFQ : multi lesvel feedback queue (q = 2^i)
- Lottery
