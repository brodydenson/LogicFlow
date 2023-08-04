# Logic Flow
An interpreted language designed for **discrete math** purposes.

## Status
Currently in **very early** stages of development. 
Thorough documentation will be posted soon...

## Example Code
```
fun range(n) ::
	return { x | x in pZ, x <= n };
;;

var conj = pZ;
for k in range(5) ::
	conj = conj * { k*x | x in pZ };
;;
print conj;
```
