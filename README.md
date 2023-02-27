Liminal
=====

Liminal is a path tracer based on Peter Shirley's [Ray Tracing in One Weekend](https://raytracing.github.io/) series of books. Liminal is currently implementing the first book in its entirety.

![Liminal screenshot](README-RTOWBookCover.png)

### Short term roadmap

While I love the series... the coding style is not for me. I've been updating the original project to match my own standards. This is a work in progress; some of my next steps will be to update:
- `Camera`
- `HitRecord` and `Hitable`
- `Sphere`, including moving it to a shapes directory
- Making `SceneBuilder` more flexible; currently it can only build two scenes
- Moving hardcoded values from Liminal.cpp to a properties class; ideally values would be coming from a config file

### Long term roadmap

- Concurrency
- UI, perhaps with being able to watch Liminal as it renders a scene
