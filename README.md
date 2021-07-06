# simul8

- [simul8](#simul8)
  - [Description](#description)
  - [Build process](#build-process)
    - [Dependency list](#dependency-list)
    - [Resolving dependencies](#resolving-dependencies)
    - [Building the project](#building-the-project)
    - [Running the project](#running-the-project)
  - [Resources](#resources)

## Description

`simul8` is an OpenGL engine meant to showcase various fundamental computer graphics concepts. Features are in progress, and the end goal is to have a working physics simulator that allows you to play with 3D shapes in a sandbox environment.

## Build process

### Dependency list

This project depends on the following libraries:

- glad ([latest version](https://github.com/Dav1dde/glad))
- glfw ([3.3.4](https://github.com/glfw/glfw/releases/tag/3.3.4))
- glm ([0.9.9.8](https://github.com/g-truc/glm/releases/tag/0.9.9.8))

### Resolving dependencies

The `simul8` project relies on `glad`, `glfw`, and `glm` to build and work properly. These libraries have been included as submodules to the project, and the right version of each library can be downloaded automatically when cloning the project for the first time. To do so, all you need to do is add the `--recurse-submodules` flag:

```bash
git clone --recurse-submodules https://github.com/cristian-aldea/simul8.git
```

or, if you already cloned the repository and didn't resolve the submodules, just run the following equivalent command:

```bash
git submodule update --init --recursive
```

With the project dependencies downloaded, you're now all set to build and run the project!

### Building the project

First, load the cmake project:

```bash
cmake -DCMAKE_BUILD_TYPE=<type> -S . -B build
```

where `<type>` is either `Release` or `Debug`, depending on your needs

Then, run the `install` target:

```bash
cmake --build build --target install
```

### Running the project

If you run the Release build, you should see a `dist/` folder pop up with the project files ready to go. Simply run the binary:

```bash
cd dist
./simul8
```

## Resources

- http://www.opengl-tutorial.org/
