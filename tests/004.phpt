--TEST--
Non-blocking test
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
var_dump( $psem->wait() );
$start = hrtime(TRUE);
var_dump( $psem->trywait() );
$finish = hrtime(TRUE);
$duration = $finish - $start;
if(($duration > 0) && ($duration < 30000)){ var_dump( TRUE ); }
var_dump( $psem->close() );
var_dump( $psem->unlink() );
?>
--EXPECT--
bool(true)
bool(false)
bool(true)
bool(true)
bool(true)
