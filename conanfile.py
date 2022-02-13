from conans import ConanFile

class BetterTestConan(ConanFile):
    ############################################################################
    ## Package info.                                                          ##
    ############################################################################
    
    name = "bettertest"
    
    description = "C++ testing framework."
    
    url = "https://github.com/TimZoet/BetterTest"

    ############################################################################
    ## Settings.                                                              ##
    ############################################################################

    python_requires = "pyreq/1.0.0@timzoet/stable"
    
    python_requires_extend = "pyreq.BaseConan"
    
    options = {
        "build_json": [True, False],
        "build_xml": [True, False]
    }
    
    default_options = {
        "build_json": True,
        "build_xml": True
    }
    
    ############################################################################
    ## Base methods.                                                          ##
    ############################################################################
    
    def set_version(self):
        base = self.python_requires["pyreq"].module.BaseConan
        base.set_version(self, "modules/bettertest/bettertestVersionString.cmake", "BETTERTEST_VERSION")
    
    def init(self):
        base = self.python_requires["pyreq"].module.BaseConan
        self.generators = base.generators + self.generators
        self.settings = base.settings + self.settings
        self.options = {**base.options, **self.options}
        self.default_options = {**base.default_options, **self.default_options}
    
    ############################################################################
    ## Building.                                                              ##
    ############################################################################
    
    def export_sources(self):
        self.copy("CMakeLists.txt")
        self.copy("license")
        self.copy("readme.md")
        self.copy("cmake/*")
        self.copy("modules/CMakeLists.txt")
        self.copy("modules/*")
    
    def config_options(self):
        base = self.python_requires["pyreq"].module.BaseConan
        if self.settings.os == "Windows":
            del self.options.fPIC
    
    def requirements(self):
        base = self.python_requires["pyreq"].module.BaseConan
        base.requirements(self)
        
        self.requires("common/1.0.0@timzoet/stable")
        self.requires("date/3.0.1")
        self.requires("parsertongue/1.1.0@timzoet/stable")
        
        if self.options.build_json:
            self.requires("nlohmann_json/3.9.1")
        if self.options.build_xml:
            self.requires("pugixml/1.11")
    
    def package_info(self):
        self.cpp_info.components["core"].libs = ["bettertest"]
        self.cpp_info.components["core"].requires = ["common::common", "date::date", "parsertongue::parsertongue"]
        
        if self.options.build_json:
            self.cpp_info.components["json"].libs = ["bettertest_json"]
            self.cpp_info.components["json"].requires = ["core", "nlohmann_json::nlohmann_json"]
            self.cpp_info.components["json"].defines = ["BETTERTEST_BUILD_JSON"]
        
        if self.options.build_xml:
            self.cpp_info.components["xml"].libs = ["bettertest_xml"]
            self.cpp_info.components["xml"].requires = ["core", "pugixml::pugixml"]
            self.cpp_info.components["xml"].defines = ["BETTERTEST_BUILD_XML"]
    
    def generate(self):
        base = self.python_requires["pyreq"].module.BaseConan
        
        tc = base.generate_toolchain(self)
        tc.generate()
        
        deps = base.generate_deps(self)
        deps.generate()
    
    def configure_cmake(self):
        base = self.python_requires["pyreq"].module.BaseConan
        cmake = base.configure_cmake(self)
        
        if self.options.build_json:
            cmake.definitions["BETTERTEST_BUILD_JSON"] = True
        
        if self.options.build_xml:
            cmake.definitions["BETTERTEST_BUILD_XML"] = True
        
        return cmake

    def build(self):
        cmake = self.configure_cmake()
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = self.configure_cmake()
        cmake.install()
