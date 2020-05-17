--TEST--
getValue test
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
var_dump( $psem->getValue() );
$psem->wait();
var_dump( $psem->getValue() );
$psem->wait();
var_dump( $psem->getValue() );
var_dump( $psem->close() );
var_dump( $psem->unlink() );
?>
--EXPECT--
int(2)
int(1)
int(0)
bool(true)
bool(true)
