# complexity_plotter

A small C command-line tool that empirically measures how a program's runtime scales with input size, and plots the result with `gnuplot`.

Point it at any executable that takes a single integer argument (e.g. an input size `n`), tell it a range of `n` values to try, and it will run that program once per value, time each run with `clock_gettime`, and produce a "Runtime vs Input Size" line plot.

## Requirements

- Linux (uses `fork`/`execvp` and `clock_gettime`)
- [`gnuplot`](http://www.gnuplot.info/) installed and available on your `PATH`, with `qt` terminal support
- A target program you want to benchmark, which accepts the input size as its first command-line argument

## Building

Source files:
- `src/complexity_plotter.c`
- `src/complexity_plotter_test.c`

Compile with your C compiler of choice, e.g.:

```bash
gcc -O2 -o bin/complexity_plotter src/complexity_plotter.c
```

A prebuilt binary is also included at `bin/complexity_plotter`.

## Usage

```bash
./complexity_plotter <program> <min> <max> <step>
```

| Argument  | Description                                                        |
|-----------|---------------------------------------------------------------------|
| `program` | Path to the executable to benchmark                                 |
| `min`     | Starting input size                                                  |
| `max`     | Upper bound on input size (exclusive)                                |
| `step`    | Increment between successive input sizes                            |

For each value of `n` from `min` up to (but not including) `max`, in steps of `step`, `complexity_plotter` will:

1. Fork and run `program n`
2. Measure the wall-clock time the run takes (in milliseconds)
3. Record the `(n, time)` pair

Once all runs finish, it opens a `gnuplot` window showing runtime (ms) on the y-axis against input size (n) on the x-axis, as connected points.

### Example

```bash
./complexity_plotter ./my_sort_benchmark 1000 10000 1000
```

This runs `./my_sort_benchmark 1000`, `./my_sort_benchmark 2000`, ..., `./my_sort_benchmark 9000`, timing each call, then plots the results.

## How it works

- Timing is done with `clock_gettime`, capturing start/end timestamps around a `fork` + `execvp` call to the target program.
- Results are streamed to a `gnuplot -persist` subprocess over a pipe, using an inline data block (`plot '-' with linespoints ...`), so no intermediate data file is written to disk.

## Notes / limitations

- The target program must accept its input size as a plain command-line argument (e.g. `program n`); there's no support for passing additional flags.
- `max` is exclusive — the loop runs `n = min, min+step, ..., n < max`.
- Timing includes process startup/fork/exec overhead in addition to the target program's actual work, so it's best used for comparing relative growth trends rather than measuring microsecond-precision performance.
- If `gnuplot` isn't installed or on your `PATH`, the tool will report `ERROR: COULDN'T OPEN GNUPLOT` and exit.
