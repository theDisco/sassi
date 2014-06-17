<?php
function ln($text) {
    echo $text, PHP_EOL;
}

$sassi = new Sassi;
ln('SASS_STYLE_NESTED');
$sassi->setStyle(Sassi::SASS_STYLE_NESTED);
echo $sassi->compileFile(__DIR__ . '/test.scss'), PHP_EOL;

ln('SASS_STYLE_COMPRESSED');
$sassi->setStyle(Sassi::SASS_STYLE_COMPRESSED);
$sassi->setSourceComments(Sassi::SASS_SOURCE_COMMENTS_MAP);
$sassi->setSourceMapFilePath(__DIR__ . '/test.json');
echo $sassi->compileFile(__DIR__ . '/test.scss'), PHP_EOL;

ln('SASS_STYLE_COMPACT');
$sassi->setStyle(Sassi::SASS_STYLE_COMPACT);
echo $sassi->compileFile(__DIR__ . '/test.scss'), PHP_EOL;

ln('SASS_STYLE_COMPRESSED');
$sassi->setStyle(Sassi::SASS_STYLE_COMPRESSED);
echo $sassi->compileFile(__DIR__ . '/test.scss'), PHP_EOL;

ln('Unsupported');
$sassi->setStyle(50);