--TEST--
Value test
--SKIPIF--
<?php
if (!extension_loaded('psem')) {
	echo 'skip';
}
?>
--FILE--
<?php
$name = '/'.bin2hex(random_bytes(8));
$psem = new PSEM($name,2);
var_dump( $psem->trywait() );
var_dump( $psem->trywait() );
var_dump( $psem->trywait() );
var_dump( $psem->close() );
var_dump( $psem->unlink() );
?>
--EXPECT--
bool(true)
bool(true)
bool(false)
bool(true)
bool(true)
