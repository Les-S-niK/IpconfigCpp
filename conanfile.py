from conan import ConanFile
import conan
from os import path
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import load


class mypkgRecipe(ConanFile):
    name = "CpconfigCpp"
    package_type = "application"

    # Optional metadata
    license = "MIT"
    author = "Les-S-niK lessnik343@gmail.com"
    url = "https://github.com/Les-S-niK/IpconfigCpp.git"
    description = "Simple utility that prints main network device properties in readable form. ( Main device is the device that is currently in usage. )"
    topics = ("c++", "network", "appliction")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def set_version(self) -> None:
        VERSION_FILE_NAME: str = "VERSION"
        version_file_path: str = path.join(self.recipe_folder, VERSION_FILE_NAME)
        self.version = load(self, version_file_path)

    def requirements(self) -> None:
        self.require("gtest/1.18.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
