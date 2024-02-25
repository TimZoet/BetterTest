from conan import ConanFile
from conan.tools.files import copy

class BetterTestConan(ConanFile):
    ############################################################################
    ## Package info.                                                          ##
    ############################################################################
    
    name = "bettertest"
    
    description = "C++ testing framework."
    
    url = "https://github.com/TimZoet/BetterTest"

    @property
    def user(self):
        return getattr(self, "_user", "timzoet")
    
    @user.setter
    def user(self, value):
        self._user = value
    
    @property
    def channel(self):
        return getattr(self, "_channel", f"v{self.version}")
    
    @channel.setter
    def channel(self, value):
        self._channel = value

    ############################################################################
    ## Settings.                                                              ##
    ############################################################################

    python_requires = "pyreq/1.0.1@timzoet/v1.0.1"
    
    python_requires_extend = "pyreq.BaseConan"
    
    options = {
        "build_alexandria": [True, False],
        "build_json": [True, False],
        "build_xml": [True, False]
    }
    
    default_options = {
        "build_alexandria": False,
        "build_json": True,
        "build_xml": True,
        "date/*:header_only": True,
        "date/*:use_system_tz_db": True
    }
    
    ############################################################################
    ## Base methods.                                                          ##
    ############################################################################
    
    def set_version(self):
        base = self.python_requires["pyreq"].module.BaseConan
        base.set_version(self, "bettertestVersionString.cmake", "BETTERTEST_VERSION")
    
    def init(self):
        base = self.python_requires["pyreq"].module.BaseConan
        self.settings = base.settings
        self.options.update(base.options, base.default_options)
    
    ############################################################################
    ## Building.                                                              ##
    ############################################################################
    
    def export_sources(self):
        copy(self, "bettertestVersionString.cmake", self.recipe_folder, self.export_sources_folder)
        copy(self, "CMakeLists.txt", self.recipe_folder, self.export_sources_folder)
        copy(self, "license", self.recipe_folder, self.export_sources_folder)
        copy(self, "readme.md", self.recipe_folder, self.export_sources_folder)
        copy(self, "buildtools/*", self.recipe_folder, self.export_sources_folder)
        copy(self, "modules/*", self.recipe_folder, self.export_sources_folder)
    
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
    
    def configure(self):
        pass

    def requirements(self):
        base = self.python_requires["pyreq"].module.BaseConan
        base.requirements(self)
        
        self.requires("common/1.1.0@timzoet/v1.1.0")
        self.requires("date/3.0.1")
        self.requires("parsertongue/1.3.1@timzoet/v1.3.1")
        
        if self.options.build_alexandria:
            self.requires("alexandria/1.0.0@timzoet/stable")
        if self.options.build_json:
            self.requires("nlohmann_json/3.9.1")
        if self.options.build_xml:
            self.requires("pugixml/1.11")
    
    def package_info(self):
        self.cpp_info.components["core"].libs = ["bettertest"]
        self.cpp_info.components["core"].requires = ["cmake-modules::cmake-modules", "common::common", "date::date", "parsertongue::parsertongue"]
        
        if self.options.build_alexandria:
            self.cpp_info.components["alexandria"].libs = ["bettertest_alexandria"]
            self.cpp_info.components["alexandria"].requires = ["core", "alexandria::alexandria"]
            self.cpp_info.components["alexandria"].defines = ["BETTERTEST_BUILD_ALEXANDRIA=ON"]
        
        if self.options.build_json:
            self.cpp_info.components["json"].libs = ["bettertest_json"]
            self.cpp_info.components["json"].requires = ["core", "nlohmann_json::nlohmann_json"]
            self.cpp_info.components["json"].defines = ["BETTERTEST_BUILD_JSON=ON"]
        
        if self.options.build_xml:
            self.cpp_info.components["xml"].libs = ["bettertest_xml"]
            self.cpp_info.components["xml"].requires = ["core", "pugixml::pugixml"]
            self.cpp_info.components["xml"].defines = ["BETTERTEST_BUILD_XML=ON"]
    
    def generate(self):
        base = self.python_requires["pyreq"].module.BaseConan
        
        tc = base.generate_toolchain(self)
        
        if self.options.build_alexandria:
            tc.variables["BETTERTEST_BUILD_ALEXANDRIA"] = True
        if self.options.build_json:
            tc.variables["BETTERTEST_BUILD_JSON"] = True
        if self.options.build_xml:
            tc.variables["BETTERTEST_BUILD_XML"] = True
        
        tc.generate()
        
        deps = base.generate_deps(self)
        deps.generate()
    
    def configure_cmake(self):
        base = self.python_requires["pyreq"].module.BaseConan
        cmake = base.configure_cmake(self)
        return cmake

    def build(self):
        cmake = self.configure_cmake()
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = self.configure_cmake()
        cmake.install()
