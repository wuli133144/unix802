## About
*

## Features
* 
*
* 
* 
* 
* 

## Installation
Run:
```
git clone https://github.com/wuli133144/unix802.git
```
and copy parson.h and parson.c to you source code tree.

Run ```make test``` to compile and run tests.

## Examples
### Parsing JSON
Here is a function, which prints basic commit info (date, sha and author) from a github repository.  
```c
<>
```
Calling ```<>;``` prints:  
```
D
...
```

### Persistence
In this example 
```c
<>
```

### Serialization
Creating JSON values is very simple thanks to the dot notation. 
Object hierarchy is automatically created when addressing specific fields. 
In the following example I create a simple JSON value containing basic information about a person.
```c


```

Output:
```

```

## Contributing

I will always merge *working* bug fixes. However, if you want to add something new to the API, please create an "issue" on github for this first so we can discuss if it should end up in the library before you start implementing it.
Remember to follow parson's code style and write appropriate tests.

## License
[The MIT License (MIT)](http://opensource.org/licenses/mit-license.php)

