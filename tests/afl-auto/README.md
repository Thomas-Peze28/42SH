# AFL Auto Fuzzer

[![Demo](https://res.cloudinary.com/marcomontalbano/image/upload/v1743882438/video_to_markdown/images/youtube--l4c4SGgAcRk-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://youtu.be/l4c4SGgAcRk "Demo")

`afl-auto` is a tool designed to automate the process of fuzz testing using [AFL++](https://github.com/AFLplusplus/AFLplusplus), a powerful and flexible fuzzing framework. Fuzzing is a software testing technique that involves providing invalid, unexpected, or random data as input to a program to uncover bugs, crashes, or vulnerabilities.

## What is AFL++?

AFL++ (American Fuzzy Lop Plus Plus) is an advanced fork of the original AFL fuzzer. It is widely used in the security and software development communities for its ability to discover subtle bugs and security vulnerabilities in software. AFL++ uses instrumentation to monitor program execution and generate test cases that maximize code coverage, making it highly effective for fuzz testing.

### Key Features of AFL++:
- **Instrumentation**: AFL++ instruments the target program to track code coverage and guide the fuzzing process.
- **Parallel Fuzzing**: It supports multi-core and distributed fuzzing to speed up the testing process.
- **Custom Mutators**: Users can define custom mutation strategies to tailor the fuzzing process to specific needs.
- **Crash Analysis**: AFL++ identifies and categorizes crashes, helping developers prioritize and fix critical issues.

## Why Use Fuzzing?

Fuzzing is an essential technique for improving software quality and security. It helps developers:
- **Discover Bugs**: Identify edge cases and unexpected behaviors that traditional testing might miss.
- **Enhance Security**: Uncover vulnerabilities that could be exploited by attackers.
- **Improve Code Coverage**: Ensure that more parts of the codebase are tested.
- **Automate Testing**: Reduce manual effort by automating the generation of test cases.

By integrating AFL++ into your development workflow, you can proactively identify and address issues, resulting in more robust and secure software.

## Usage

To use `afl-auto`, you can run it with or without a graphical interface, depending on your needs.

### Without a Graphical Interface

Run the following command to start fuzzing in a headless mode:

```bash
docker run --rm -it -v $(pwd):/src -e LUNCH_TIME=30 myecoria/epitfl:latest
```

This command mounts your current working directory (`$(pwd)`) into the container, sets the fuzzing duration to 30 minutes (`LUNCH_TIME=30`), and starts the fuzzing process.

### With a Graphical Interface

If you want to use a graphical interface to monitor the fuzzing process, ensure that your system supports X11 forwarding and run the following command:

```bash
docker run --rm -it -v $(pwd):/src -e LUNCH_TIME=30 -e DISPLAY=$DISPLAY myecoria/epitfl:latest
```

This command additionally forwards the X11 display (`DISPLAY=$DISPLAY`) and mounts the X11 socket (`/tmp/.X11-unix`) to enable GUI support.

### Notes

- Replace `LUNCH_TIME=30` with your desired fuzzing duration in minutes.
- Ensure that your Docker environment has the necessary permissions to access the X11 display if using the graphical interface.
- For best results, make sure your project is properly instrumented with AFL++ before running these commands.
- Check the container logs for fuzzing progress and results.
- Documentation for generating tests can be found in the `TESTS.md` file.