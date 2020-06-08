--TEST--
Semaphore test with timeout
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
var_dump( $psem->wait());
$start = hrtime(TRUE);
var_dump( $psem->wait(1) );
$finish = hrtime(TRUE);
$duration = $finish - $start;
if(($duration > 1000000000) && ($duration < 3000000000)){ echo "ok".PHP_EOL; }
var_dump( $psem->close() );
var_dump( $psem->unlink() );
?>
--EXPECT--
bool(true)
bool(false)
ok
bool(true)
bool(true)
