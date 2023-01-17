from conans import ConanFile, CMake, tools


class SnookerConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def requirements(self):
        self.requires("opengl/system")
        self.requires("freeglut/3.2.2")
        self.requires("boost/1.81.0")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
