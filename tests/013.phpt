--TEST--
Fork Test
--SKIPIF--
<?php
if (!extension_loaded('pmq')) {
	echo 'skip';
}
if (!extension_loaded('pcntl')) {
	echo 'skip';
}

?>
--FILE--
<?php
$name = '/'.bin2hex(random_bytes(8));
$psem = new PSEM($name);

    $pid = pcntl_fork();
    if ($pid == -1) {
     echo 'skip';
} else if ($pid) {

    pcntl_wait($status);

    var_dump( $psem->post() ) ;

    var_dump( $psem->unlink() ) ;



} else {

    var_dump( $psem->wait() );
    exit(0);

}



?>
--EXPECT--
bool(true)
bool(true)
bool(true)
