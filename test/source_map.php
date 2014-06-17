<?php
function ln($text) {
    echo $text, PHP_EOL;
}

ln('SASS_STYLE_COMPRESSED');
$sassi = new Sassi;
$sassi->setStyle(Sassi::SASS_STYLE_COMPRESSED);
$sassi->setSourceComments(Sassi::SASS_SOURCE_COMMENTS_MAP);
$sassi->setSourceMapFilePath(__DIR__ . '/source_map.json');
$sassi->setOutputPath(__DIR__ . '/source_map.css');
$sassi->setImagePath('img');
echo $sassi->compileFile(__DIR__ . '/main.scss'), PHP_EOL;