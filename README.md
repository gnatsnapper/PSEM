[![Build Status](https://travis-ci.org/gnatsnapper/PosixSemaphore.svg?branch=master)](https://travis-ci.org/gnatsnapper/PosixSemaphore)

PSEM
======

PSEM is a php extension for interacting with posix semaphores.  Posix semaphores are updated alternatives for sysv semaphores, i.e. low-latency kernel-based interprocess communication. Tested on PHP7.4 on linux and bsd.

## Install

```
$ phpize
$ ./configure
$ make && make install
```

## Usage

### Create Semaphore

```php
$psem = new PosixSemaphore("/mysemaphore");
```
PSEM with only a semaphore name will attempt to create a new or join an existing semaphore.  As per the standard, queue names must begin with a single forward slash (/) and be less than 255 characters.

PSEM's uses O flags formatting:
* ```PSEM_CREAT``` - (```O_CREAT```) create
* ```PSEM_EXCL``` - (```O_EXCL```) exclusive (do not create if file exists)

Semaphore permissions can be set in umask format, and an initial value given:

```php
$psem = new PosixSemaphore("/mysemaphore", PSEM_CREAT, 0600, 1);
```

### Wait
PosixSemaphore::wait() will attempt decrement the semaphore or block until it can.

```php
$psem->wait();
```

A timeout can be added to  PosixSemaphore::wait(), and will return false if that timeout is reached.

```php
$psem->wait(5);
```
PosixSemaphore::trywait() will not block, but will decrement the semaphore if it can, returning true, or return false.

```php
$psem->trywait();
```
### Post

PosixSemaphore::post() increments the semaphore (locking)

```php
$psem->post();
```

### Delete Semaphore

```php
$psem->unlink();
```
Semaphores not deleted will persist until computer is restarted, so always delete if not needed by another process.

## Troubleshooting

### Bad file descriptor
This occurs where attempting to send to a queue with only read access, or vice versa.
