# Logic Flow
An interpreted language designed for **discrete math** purposes.

## Status
Currently in **early** stages of development. 
Thorough documentation will be posted soon...

## Example Code
```
# Returns [1, 2, 3, ... n]
fn range(n) ::
	return { x | x in pZ, x <= n };
;;

let conj = pZ;
for k in range(5)
  conj *= { k*x | x in pZ };
print conj;
```

```
# Returns every subset of the set
fn P(set) ::
  let subsets = {[]};
  for item in set ::
    for subset in subsets
      subsets += {subset ++ item};
    subsets += {[item]};
  ;;
  return subsets;
;;
```
