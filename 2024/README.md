# Directories

Three directories are needed to run:
- Repository
    - Source code for the solutions.
- Cases
    - Puzzle inputs and expected outputs.
- Build
    - Where the project is built and tests run.

The repository directory is part of the GitHub repository.
The cases directory is not added to GitHub becase the Advent of Code license doesn't allow that data to be redistributed.
The build directory only contain temporary files and can be created and recreated at will.
Preferably keep the build directory away from the repository and backed up directories.


# Steps

To run:
- Create a build directory somewhere.
- Run `cmake` from the build directory.
- Run the test script, passing in the day to test for, and optionally other flags as well.

```shell
/advent-of-code/build
➤ cmake /advent-of-code/repository/2024/
➤ /advent-of-code/repository/2024/run_tests.bash -td 1
```
