<?php

class SassiTest
{
    private $mainPath;
    private $outputPath;
    private $sourceMapPath;

    public function __construct()
    {
        $this->mainPath = __DIR__ . '/scss/main.scss';
        $this->outputPath = __DIR__ . '/compiled.css';
        $this->sourceMapPath = __DIR__ . '/compiled.json';
    }

    public function testStyleNested()
    {
        $this->testStyle(Sassi::SASS_STYLE_NESTED, __DIR__ . '/expected/style_nested.css');
    }

    public function testStyleExpanded()
    {
        $this->testStyle(Sassi::SASS_STYLE_EXPANDED, __DIR__ . '/expected/style_expanded.css');
    }

    public function testStyleCompact()
    {
        $this->testStyle(Sassi::SASS_STYLE_COMPACT, __DIR__ . '/expected/style_compact.css');
    }

    public function testStyleCompressed()
    {
        $this->testStyle(Sassi::SASS_STYLE_COMPRESSED, __DIR__ . '/expected/style_compressed.css');
    }

    private function testStyle($style, $expectedPath)
    {
        $sassi = new Sassi;
        $sassi->setStyle($style);
        $sassi->setOutputPath($this->outputPath);
        $compiledString = $sassi->compileFile($this->mainPath);
        $this->stringSame(file_get_contents($expectedPath), $compiledString);
        $this->fileSame($expectedPath, $this->outputPath);

        $this->cleanUp();
    }

    public function testStyleCompressedSourceMap()
    {
        $sassi = new Sassi;
        $sassi->setStyle(Sassi::SASS_STYLE_COMPRESSED);
        $sassi->setSourceComments(Sassi::SASS_SOURCE_COMMENTS_MAP);
        $sassi->setSourceMapFilePath($this->sourceMapPath);
        $sassi->setOutputPath($this->outputPath);
        $sassi->setImagePath('img');
        $sassi->compileFile($this->mainPath);
    }

    private function stringSame($expectedString, $actualString)
    {
        $expectedString = preg_replace('#/*(.*)*/#', '', $expectedString);
        $actualString = preg_replace('#/*(.*)*/#', '', $actualString);
        if ($expectedString !== $actualString) {
            throw new Exception("Strings are not the same");
        }
    }

    private function fileSame($expectedPath, $actualPath)
    {
        $expected = preg_replace('#/*(.*)*/#', '', file_get_contents($expectedPath));
        $actual = preg_replace('#/*(.*)*/#', '', file_get_contents($actualPath));
        if ($expected !== $actual) {
            throw new Exception("Files are not the same");
        }
    }

    public function cleanUp()
    {
        if (file_exists($this->outputPath)) {
            unlink($this->outputPath);
        }
    }

    public function exec()
    {
        $this->testStyleNested();
        $this->testStyleExpanded();
        $this->testStyleCompact();
        $this->testStyleCompressed();
        //$this->testStyleCompressedSourceMap();
    }
}
$sassiTest = new SassiTest;
try {
    $sassiTest->exec();
    echo "All tests passed", PHP_EOL;
} catch (Exception $e) {
    $sassiTest->cleanUp();
    echo $e->getMessage(), PHP_EOL;
    echo $e->getTraceAsString(), PHP_EOL;
}