--TEST--
Basic test of object instantiation
--SKIPIF--
<?php
if (!extension_loaded('psem')) {
	echo 'skip';
}
?>
--FILE--
<?php
$name = '/'.bin2hex(random_bytes(8));
$psem = new PSEM($name);
var_dump( $psem->close() );
var_dump( $psem->unlink() );
?>
--EXPECT--
bool(true)
bool(true)
