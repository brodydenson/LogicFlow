# Logic Flow
An interpreted language designed for **discrete math** purposes.

## Status
Currently in **very early** stages of development. 
Thorough documentation will be posted soon...

## Example Code
```
fun range(n) ::
	return { x | x in uZ, x <= n };
;;

var conj = uZ;
for k in range(5) ::
	conj = conj * { k*x | x in uZ };
;;
print conj;
```
