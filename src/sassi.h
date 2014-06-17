#include "../lib/libsass/sass_interface.h"

#ifndef SASSI_H
#define	SASSI_H

class Sassi : public Php::Base
{
private:
    const int default_sass_style = SASS_STYLE_NESTED;
    int sass_style = -1;
    const int default_source_comments = SASS_SOURCE_COMMENTS_DEFAULT;
    int source_comments = -1;
    string source_map_file_path = "";
    string output_path = "";
    string image_path = "";
    
public:
    void setStyle(Php::Parameters &params);
    int getStyle();
    void setSourceComments(Php::Parameters &params);
    int getSourceComments();
    void setSourceMapFilePath(Php::Parameters &params);
    string getSourceMapFilePath();
    void setOutputPath(Php::Parameters &params);
    string getOutputPath();
    void setImagePath(Php::Parameters &params);
    string getImagePath();
    Php::Value compileFile(Php::Parameters &params);
    void writeToFile(string file_name, char* content);
};

#endif	/* SASSI_H */

