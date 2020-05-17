--TEST--
Check if psem is loaded
--SKIPIF--
<?php
if (!extension_loaded('psem')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "psem" is available';
?>
--EXPECT--
The extension "psem" is available
