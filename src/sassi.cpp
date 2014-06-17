#include <phpcpp.h>
#include <string>
#include <fstream>
#include "sassi.h"

using namespace std;

void Sassi::setStyle(Php::Parameters &params)
{
    sass_style = (int) params[0];
    if (sass_style < 0 || sass_style > 4) {
        throw Php::Exception("Unsupported sass style");
    }
}
    
int Sassi::getStyle()
{
    if (sass_style < 0) {
        return default_sass_style;
    }
    return sass_style;
}
    
void Sassi::setSourceComments(Php::Parameters &params)
{
    source_comments = (int) params[0];
    if (source_comments < 0 || source_comments > 3) {
        throw Php::Exception("Unsupported source comments");
    }
}
    
int Sassi::getSourceComments()
{
    int current_source_comments = default_source_comments;
    if (source_comments >= 0) {
        current_source_comments = source_comments;
    }
    return current_source_comments;
}
    
void Sassi::setSourceMapFilePath(Php::Parameters &params)
{
    source_map_file_path = params[0].stringValue();
}
    
string Sassi::getSourceMapFilePath()
{
    if (source_map_file_path == "") {
        throw Php::Exception("Source map file path not set.");
    }
    char* empty = const_cast<char *>("");
    writeToFile(source_map_file_path, empty);
    return source_map_file_path;
}

void Sassi::setOutputPath(Php::Parameters &params)
{
    output_path = params[0].stringValue();
}

string Sassi::getOutputPath()
{
    if (output_path == "") {
        throw Php::Exception("Output path not set.");
    }
    char* empty = const_cast<char *>("");
    writeToFile(output_path, empty);
    return output_path;
}

void Sassi::setImagePath(Php::Parameters& params)
{
    image_path = params[0].stringValue();
}

string Sassi::getImagePath()
{
    return image_path;
}
    
Php::Value Sassi::compileFile(Php::Parameters &params)
{
    struct sass_file_context* context = sass_new_file_context();
    context->options.include_paths = "";
    context->options.output_style = getStyle();
    int source_comments = getSourceComments();
    context->options.source_comments = source_comments;
    context->options.image_path = getImagePath().c_str();
    if (source_comments == SASS_SOURCE_COMMENTS_MAP) {
        context->output_path = getOutputPath().c_str();
        context->source_map_file = getSourceMapFilePath().c_str();
    }
    context->input_path = params[0].stringValue().c_str();

    sass_compile_file(context);

    if (context->error_status) {
        throw Php::Exception(context->error_message);
    }
    
    writeToFile(getOutputPath(), context->output_string);
    if (source_comments == SASS_SOURCE_COMMENTS_MAP) {
        writeToFile(getSourceMapFilePath(), context->source_map_string);
    }
    
    Php::Value output_string(context->output_string);
    sass_free_file_context(context);

    return output_string;
}

void Sassi::writeToFile(string file_name, char* content)
{
    ofstream file;
    file.open(file_name.c_str());
    file << content;
    file.close();
}