Liminal
=====

Liminal is a path tracer based on Peter Shirley's [Ray Tracing in One Weekend](https://raytracing.github.io/) series of books. Liminal currently implements the first book in its entirety.

![Liminal screenshot](README-RTOWBookCover.png)

### Short term roadmap

While I love the series... the coding style is not for me. I've been updating the original project to match my own standards. This is a work in progress; some of my next steps will be to update:
- `HitRecord` and `Hitable`
- `Sphere`, including moving it to a shapes directory
- Consider splitting the `Material` classes into .h and .cpp files
- Making `SceneBuilder` more flexible; currently it can only build two scenes
- Passing around `std::shared_ptr`; it's possible functionality that creates these pointers can be internalized, such as within `SceneBuilder`
- Moving hardcoded values from Liminal.cpp to a properties class; ideally values would be coming from a config file
- Try and break the dependency between hitable.h and material.h

### Long term roadmap

- Concurrency
- UI, perhaps with being able to watch Liminal as it renders a scene

... or perhaps replacing this version of Liminal with one based on [pbrt](https://github.com/mmp/pbrt-v3) from [Physically Based Rendering](https://www.pbr-book.org/).
