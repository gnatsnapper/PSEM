--TEST--
Two Objects One Semaphore
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
try {
$psem2 = new PSEM($name);
} catch (Exception $e)
{
    echo $e->getMessage();
}
var_dump( $psem->close() );
var_dump( $psem->unlink() );
?>
--EXPECT--
bool(true)
bool(true)
