#include <phpcpp.h>
#include <string>
#include "sassi.h"

extern "C" {
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("sassi", "0.1");
        
        Php::Class<Sassi> sassi("Sassi");
        sassi.property("SASS_STYLE_NESTED", SASS_STYLE_NESTED, Php::Const);
        sassi.property("SASS_STYLE_EXPANDED", SASS_STYLE_EXPANDED, Php::Const);
        sassi.property("SASS_STYLE_COMPACT", SASS_STYLE_COMPACT, Php::Const);
        sassi.property("SASS_STYLE_COMPRESSED", SASS_STYLE_COMPRESSED, Php::Const);
        sassi.property("SASS_SOURCE_COMMENTS_NONE", SASS_SOURCE_COMMENTS_NONE, Php::Const);
        sassi.property("SASS_SOURCE_COMMENTS_DEFAULT", SASS_SOURCE_COMMENTS_DEFAULT, Php::Const);
        sassi.property("SASS_SOURCE_COMMENTS_MAP", SASS_SOURCE_COMMENTS_MAP, Php::Const);
        sassi.method("setStyle", &Sassi::setStyle, {
            Php::ByVal("style", Php::Type::Numeric)
        });
        sassi.method("setSourceComments", &Sassi::setSourceComments, {
            Php::ByVal("sourceComment", Php::Type::Numeric)
        });
        sassi.method("setSourceMapFilePath", &Sassi::setSourceMapFilePath, {
            Php::ByVal("sourceMapFilePath", Php::Type::Numeric)
        });
        sassi.method("setOutputPath", &Sassi::setOutputPath, {
            Php::ByVal("outputPath", Php::Type::String)
        });
        sassi.method("setImagePath", &Sassi::setImagePath, {
            Php::ByVal("imagePath", Php::Type::String)
        });
        sassi.method("compileFile", &Sassi::compileFile, {
            Php::ByVal("filePath", Php::Type::String)
        });
        extension.add(std::move(sassi));
        return extension;
    }
}