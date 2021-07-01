# simul8

- [simul8](#simul8)
  - [Description](#description)
  - [Build Process](#build-process)
    - [Dependency List](#dependency-list)
    - [Resolving Dependencies](#resolving-dependencies)
    - [Building the project](#building-the-project)
  - [Resources](#resources)

## Description

simul8 is an OpenGL engine meant to showcase various fundamental computer graphics concepts. Various features are in progress, and the end goal is to have a working physics simulator that allows you to play with various 3D shapes in a sandbox environment.

## Build Process

### Dependency List

This project depends on the following libraries:

- glew (version [2.2.0](https://github.com/nigels-com/glew/releases/tag/glew-2.2.0))
- glfw (version [3.3.4](https://github.com/glfw/glfw/releases/tag/3.3.4))
- glm (version [0.9.9.8](https://github.com/g-truc/glm/releases/tag/0.9.9.8))

### Resolving Dependencies

`glfw` and `glm` have been included as git submodules to simplify the fetching process. All you need to do is add the `--recurse-submodules` flag when cloning the repository:

```bash
git clone --recurse-submodules https://github.com/cristian-aldea/simul8.git
```

or, if you already cloned the repository and didn't resolve the submodules, just run the following equivalent command:

```bash
git submodule update --init --recursive
```

However, glew requires building from a zip release, which will need to be downloaded manually (for now). Please download the glew release zip using the link given in the above [Dependency List](#dependency-list) section, and place the content of the zip under `external/glew`.

### Building the project

First, load the cmake project:

```bash
cmake -DCMAKE_BUILD_TYPE=<type> -S . -B build
```

where `<type>` is either `Release` or `Debug` depending on your needs

Then, run the `install` target:

```bash
cmake --build build --target install
```

## Resources

- http://www.opengl-tutorial.org/
