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
$psem1 = new PSEM($name,PSEM_CREAT,0111);
try { $psem2 = new PSEM($name); }
catch (Exception $e) {

    var_dump( $e->getMessage() );

}

var_dump( $psem1->close() );
var_dump( $psem1->unlink() );
?>
--EXPECT--
string(17) "Permission denied"
bool(true)
bool(true)
