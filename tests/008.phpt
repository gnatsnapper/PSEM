--TEST--
Mode test
--SKIPIF--
<?php
if (!extension_loaded('psem')) {
	echo 'skip';
}
?>
--FILE--
<?php
$name = '/'.bin2hex(random_bytes(8));
$psem1 = new PSEM($name,0,0111);
try { $psem2 = new PSEM($name); }
catch (Exception $e) {

    echo $e->getMessage() . PHP_EOL;

}

var_dump( $psem1->close() );
var_dump( $psem1->unlink() );
?>
--EXPECT--
Permission denied
bool(true)
bool(true)
