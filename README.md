# HW3D. Level 1: triangles

This project is a task on course "Uses and applications of C++ language" by
[K.I.Vladimirov](https://github.com/tilir). The task was to intersect triangles in 3D.

## Requirements

The following applications have to be installed:

- CMake of version 3.15 (or higher)
- Geometry3D (Python library; necessary for [checker.sh](/test/end_to_end/checker.sh))

## How to install

```bash
git clone git@github.com:KetchuppOfficial/Triangles.git
cd Triangles
```

## How to build

### 0) Make sure you are in the root directory of the project (i.e. Triangles/)

### 1) Build the project

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build [--target <tgt>]
```

**tgt** can be **basic_tests**, **algorithm_tests**, **driver** or **generator**. The first two
targets are two groups of unit-tests. The **generator** is a program the generates random triangles
(more on that later). The **driver** is a program that recieves the number of triangles and
coordinates of their points from stdin and prints the numbers of intersecting triangles on stdout.

If --target option is omitted, all targets will be built.

## How to run unit tests

```bash
ctest --test-dir build
```

## How to run end-to-end tests

If you want to run some tests on intersection of random triangles, go to
[test/end_to_end](/test/end_to_end/) directory. There you will find a special script **checker.sh**
provided for such purpose.

Let **N** be the number of triangles you want to intersect, **wH** - halfwidth of the world,
**minH**/**maxH** - minimal/maximal halfwidth of any bounding box containing a triangle, then
command sequence:

```bash
./checker.sh N wH minH maxH
```

generates **N** random triangles which bounding boxes have halfwidths in range [**minH**; **maxH**].
The shapes are saved in file **N.test**. After that this script runs python program on the test,
gets an answer that is supposed to be correct and saves it in file **N.ans**. Then, C++ program does
the same. The results are saved in **N.res**. Finally, files **N.ans** and **N.res** are compared.
If the indexes of intersecting triangles are different, then this test is considered "failed". It is
considered "passed" otherwise.

I wouldn't suggest running tests with **N > 500** as you will wait really long that way.

P.s. **checker.sh** script simply forwards its arguments to **generator**. So, after the meaning of
every argument is explained, it becomes clear what exact triangles are generated.

P.p.s. **driver** measures the time spent on actions such as reading from file, construction of
octree, etc. This information is saved in **time.info** file.

### I want to thank [Dany](https://github.com/BileyHarryCopter) and [Sergey](https://github.com/LegendaryHog) for their contribution to this project at its first stage
