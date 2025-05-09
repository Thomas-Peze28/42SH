# Supported Variables and Parameters

This document describes the environment variables and parameters used by the `afl-auto` project. These variables allow you to configure and customize the behavior of the script and associated tools.

## Environment Variables

### `LUNCH_TIME`
- **Description**: Defines the fuzzing execution duration in seconds.
- **Default Value**: `300` (5 minutes)
- **Example Usage**:
    ```bash
    docker run --rm -it -v $(pwd):/src -e LUNCH_TIME=600 myecoria/epitfl:latest # 10 minutes
    ```

### `DELAY`
- **Description**: Sets the timeout delay for tests in milliseconds.
- **Default Value**: `500`
- **Example Usage**:
    ```bash
    docker run --rm -it -v $(pwd):/src -e DELAY=1000 myecoria/epitfl:latest # 1 second
    ```

### `DISPLAY`
- **Description**: Enables the graphical interface for monitoring AFL++ sessions via `tmux`.
- **Default Value**: Undefined (headless mode).
- **Example Usage**:
    ```bash
    docker run --rm -it -v $(pwd):/src -e DISPLAY=:0 -v /tmp/.X11-unix:/tmp/.X11-unix myecoria/epitfl:latest
    ```

## Script Parameters

### `Makefile`
- **Description**: Name of the Makefile used to compile the project.
- **Default Value**: `Makefile`
- **Example Usage**:
    ```bash
    docker run --rm -it -v $(pwd):/src -e MAKEFILE="CustomMakefile" myecoria/epitfl:latest
    ```

### `NB_COEURS`
- **Description**: Number of CPU cores used for fuzzing.
- **Default Value**: 80% of the total CPU cores available on the machine.
- **Example Usage**:
    ```bash
    docker run --rm -it -v $(pwd):/src -e NB_COEURS=4 myecoria/epitfl:latest
    ```

### `INPUT_OPTION`
- **Description**: Specifies additional options for AFL++ input configuration.
- **Default Value**: `-m none -c 0`
- **Example Usage**:
    ```bash
    docker run --rm -it -v $(pwd):/src -e INPUT_OPTION="-m 512 -c 1" myecoria/epitfl:latest
    ```

## Command Examples

### Running in Headless Mode
```bash
docker run --rm -it -v $(pwd):/src -e LUNCH_TIME=600 myecoria/epitfl:latest
```

### Running in Graphical Mode
```bash
docker run --rm -it -v $(pwd):/src -e LUNCH_TIME=600 -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix myecoria/epitfl:latest
```

### Compilation and Fuzzing with Custom Parameters
```bash
docker run --rm -it -v $(pwd):/src -e LUNCH_TIME=1200 -e DELAY=1000 myecoria/epitfl:latest
```

By configuring these variables and parameters, you can tailor the behavior of the `afl-auto` project to your specific needs.
